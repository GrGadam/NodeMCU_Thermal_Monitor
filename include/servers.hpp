#ifndef SERVERS_H
#define SERVERS_H

#include "ESPAsyncWebServer.h"
#include <LittleFS.h>
#include "header.hpp"

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

#endif //SERVERS_H