#include "tasks.h"

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