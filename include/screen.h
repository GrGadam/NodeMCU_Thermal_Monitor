#ifndef NODEMCU_THERMAL_MONITOR_SCREEN_H
#define NODEMCU_THERMAL_MONITOR_SCREEN_H

#include "TFT_eSPI.h"
#include "images.h"
#include "sensor.h"

extern TFT_eSPI tft;

extern void prepare_screen();
extern void update_screen();

#endif //NODEMCU_THERMAL_MONITOR_SCREEN_H