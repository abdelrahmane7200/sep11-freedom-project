#pragma once
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>

class Weather {
private:
    DynamicJsonDocument organizedWeatherData;
    int currentHourIndex;

    String deriveCondition(float rain, float showers);

public:
    Weather();

    void fetchWeatherData();
    void updateCurrentHourIndex(const String& currentTime);

    // Getters for screen rendering
    float getTemp(int offset = 0);          // offset from current hour
    String getHourLabel(int offset = 0);    // e.g. "3PM"
    String getCurrentCondition();
    float getCurrentTemp();

    // Legacy serial debug
    void printNext24Hours();
};