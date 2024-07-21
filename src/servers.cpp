#include "servers.h"

String ssid, password;
WiFiClient client;
AsyncWebParameter *awp;
AsyncWebServer server(80);
u_int8_t retries = 0;

//start WIFI (with the saved SSID and passwd if exists on the filesystem)
//if WIFI hasn't been found within 10 sencs -> start hotsport with default values and the wifi finder html page
//else start the normal online page

void connect_to_wifi() {

}

void handle_wifi_tasks() {
    File file = LittleFS.open("/wifi_credentials.txt", "r");
    ssid = file.readStringUntil('\n');
    password = file.readString();

    connect_wifi_task.enable();



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

void postaction(AsyncWebServerRequest *request) {
    Serial.println("POST recieved!");
    int params = request->params();
    for (int i = 0; i < params; i++) {
        awp = request->getParam(i);
        Serial.printf("POST[%s]: %s\n", awp->name().c_str(), awp->value().c_str());
    }
    //request->send_P(200, "text/html", index_html);
    //server.end();
    //start normal server task
}

void start_wifi_page() {

}

void start_main_page() {

}
