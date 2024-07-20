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



//##########################VARS#############################
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
//###########################################################



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

//TASKS
Task screen_update_task(1000, TASK_FOREVER, &update_screen);
Task vars_update_task(1000, TASK_FOREVER, &update_vars);
Task wifi_tasks(1000, TASK_ONCE, &handle_wifi_tasks);
Task connect_wifi_task(1000, TASK_ONCE, &connect_to_wifi);

void setup() {
    //init screen and sensor
    tft.begin();
    dht.begin();
    LittleFS.begin();
    prepare_screen();

    //Register Tasks
    ts.addTask(vars_update_task);
    ts.addTask(screen_update_task);
    ts.addTask(wifi_tasks);
    ts.addTask(connect_wifi_task);

    //Start Tasks
    vars_update_task.enable();
    screen_update_task.enable();
    wifi_tasks.enable();
}

void loop() {
    ts.execute();
}