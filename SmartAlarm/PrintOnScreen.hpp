#pragma once
#include <TFT_eSPI.h>
#include <set>
#include <Arduino.h>

class PrintOnScreen {
public:
    PrintOnScreen(TFT_eSPI& tftObj);

    void printBackground();
    void printTime(const String& time);
    void printDate(const String& date);
    void printWeather(float tempC, const String& condition, const String& location);
    void printForecast(float temps[6], String hours[6]);
    void printAlarms(bool hasAlarms, const std::set<String>& alarms);
    void printStatusBar(bool wifiConnected, bool ntpSynced);

private:
    TFT_eSPI& tft;

    // Layout constants
    static const int SCREEN_W = 480;
    static const int SCREEN_H = 320;
    static const int DIVIDER_X = 242;
    static const int STATUS_BAR_Y = 290;

    // Left panel
    static const int LEFT_X = 20;
    static const int TIME_Y = 58;
    static const int DATE_Y = 80;
    static const int DIVIDER1_Y = 94;
    static const int WEATHER_LABEL_Y = 114;
    static const int TEMP_Y = 148;
    static const int LOCATION_Y = 168;
    static const int CONDITION_Y = 186;
    static const int DIVIDER2_Y = 198;
    static const int FORECAST_LABEL_Y = 216;
    static const int FORECAST_TIME_Y = 238;
    static const int FORECAST_TEMP_Y = 254;

    // Right panel
    static const int RIGHT_X = 260;
    static const int ALARM_LABEL_Y = 30;
    static const int ALARM_START_Y = 38;
    static const int ALARM_ROW_H = 54;
    static const int ALARM_W = 215;
    static const int ALARM_LEFT = 255;
    static const int MAX_ALARMS = 3;

    // Colors
    static const uint32_t BG_DARK     = 0x001a33;
    static const uint32_t BG_PANEL    = 0x002a4d;
    static const uint32_t BG_EMPTY    = 0x001526;
    static const uint32_t BG_STATUS   = 0x00101f;
    static const uint32_t BG_ON_BADGE = 0x0d3d1f;
    static const uint32_t COL_DIVIDER = 0x1e4d7a;
    static const uint32_t COL_MUTED   = 0x6a9fc0;
    static const uint32_t COL_EMPTY   = 0x2a4d66;
    static const uint32_t COL_GREEN   = 0x4caf7d;

    // Helper to convert 24-bit hex color to TFT 16-bit color
    uint16_t hex(uint32_t c);

    void drawHLine(int x1, int x2, int y);
    void drawVLine(int x, int y1, int y2);
};