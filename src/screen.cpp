#include "screen.hpp"

TFT_eSPI tft = TFT_eSPI(80, 160);

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