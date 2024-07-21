#ifndef NODEMCU_THERMAL_MONITOR_SERVERS_H
#define NODEMCU_THERMAL_MONITOR_SERVERS_H

#include "ESPAsyncWebServer.h"
#include <LittleFS.h>
#include "tasks.h"

extern String ssid, password;
extern WiFiClient client;
extern AsyncWebParameter *awp;
extern AsyncWebServer server;
extern u_int8_t retries;

extern void postaction(AsyncWebServerRequest *request);
extern void handle_wifi_tasks();
extern void connect_to_wifi();
extern void start_wifi_page();
extern void start_main_page();

#endif //NODEMCU_THERMAL_MONITOR_SERVERS_H