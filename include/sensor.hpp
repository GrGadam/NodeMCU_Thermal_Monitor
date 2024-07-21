#ifndef SENSOR_H
#define SENSOR_H

#include "DHT.h"

extern char *timestring;
extern char *str;
extern uint32_t s;
extern DHT dht;
extern int32_t temperature, humidity;

extern void update_vars();

#endif //SENSOR_H