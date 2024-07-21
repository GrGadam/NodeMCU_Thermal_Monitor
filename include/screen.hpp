#ifndef SCREEN_H
#define SCREEN_H

#include "TFT_eSPI.h"
#include "images.hpp"
#include "sensor.hpp"

extern TFT_eSPI tft;

extern void prepare_screen();
extern void update_screen();

#endif //SCREEN_H