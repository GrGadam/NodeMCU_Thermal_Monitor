#ifndef NODEMCU_THERMAL_MONITOR_SENSOR_H
#define NODEMCU_THERMAL_MONITOR_SENSOR_H

#include <Arduino.h>
#include "DHT.h"

extern char *timestring;
extern char *str;
extern uint32_t s;
extern DHT dht;
extern int32_t temperature, humidity;

extern void update_vars();

#endif //NODEMCU_THERMAL_MONITOR_SENSOR_H