#include <Arduino.h>
#include <DHT.h>
#include <TFT_eSPI.h>
#include "images.h"
#include <FS.h>
#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <TaskScheduler.h>

//SCHEDULER
Scheduler ts;

//DISPLAY
TFT_eSPI tft = TFT_eSPI(80, 160);

//VALUES
char timestring[18];
char str[3];
uint32_t s = 0;

//SENSOR
DHT dht(5, DHT11);
int32_t temperature, humidity = 0;

//WEBSERVER
String ssid, password;
AsyncWebServer server(80);


void update_vars() {
    temperature = static_cast<int>(dht.readTemperature(false, true));
    humidity = static_cast<int>(dht.readHumidity());
}

void prepare_screen() {
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    //images
    tft.drawBitmap(16, 10, img_thermometer_map, 18, 36, TFT_WHITE);
    tft.drawBitmap(87, 10, img_water_drop_map, 25, 36, TFT_WHITE);
}

void update_screen() {
    //clear screen
    tft.fillRect(0, 0, 128, 8, TFT_BLACK); //timer
    tft.fillRect(0, 52, 128, 12, TFT_BLACK); //vars

    //uptime
    s = millis() / 1000;
    snprintf(timestring, 18, "%id %ih %im %is", s / 86400, s / 3600 % 24, s / 60 % 60, s % 60);
    tft.drawCentreString(timestring, 64, 0, 1);

    //temp and humid values
    sprintf(str, "%i", temperature);
    tft.drawCentreString(str, 26, 52, 1);

    sprintf(str, "%i", humidity);
    tft.drawCentreString(str, 100, 52, 1);
}


//Webserver Functions
void postaction(AsyncWebServerRequest *request) {
    Serial.println("POST recieved!");
    int params = request->params();
    for (int i = 0; i < params; i++) {
        AsyncWebParameter *p = request->getParam(i);
        Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
    }
    //request->send_P(200, "text/html", index_html);
    //server.end();
    //start normal server task
}

void handle_wifi_tasks() {
    File file = LittleFS.open("/settings.txt", "r");
    IPAddress ip(192, 168, 0, 1);
    IPAddress gateway(192, 168, 0, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig(ip, gateway, subnet);
    WiFi.softAP("NodeMCU Hotspot", "123456789");

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/site/index.html", "text/html");
    });

    server.on("/", HTTP_POST, postaction);

    server.serveStatic("/", LittleFS, "/site/");

    server.begin();

    /*
     while (file.available()) {
        ssid = file.readStringUntil('\n');
        password = file.readString();
    }
    file.close();
    WiFi.begin(ssid, password);
     */

}


Task screen_update(1000, TASK_FOREVER, &update_screen);
Task vars_update(1000, TASK_FOREVER, &update_vars);
Task wifi_tasks(1000, TASK_ONCE, &handle_wifi_tasks);

void setup() {
    //init screen and sensor
    tft.begin();
    dht.begin();
    LittleFS.begin();
    prepare_screen();

    //start Wifi (with the saved SSID and passwd if exists on the filesystem)
    //if wifi hasnt been found within 10 sencs -> start hotsport with default values and the wifi finder html page
    //else start the normal online page


    ts.addTask(vars_update);
    vars_update.enable();
    ts.addTask(screen_update);
    screen_update.enable();
    ts.addTask(wifi_tasks);
    wifi_tasks.enableDelayed(1000);
}

void loop() {
    ts.execute();
}
