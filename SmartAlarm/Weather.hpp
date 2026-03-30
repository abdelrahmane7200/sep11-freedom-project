#pragma once

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>

class Weather {
  private:
    DynamicJsonDocument organizedWeatherData;

  public:
    // Constructor
    Weather();

    // Fetch weather JSON data from API
    void fetchWeatherData();

    // Print the next 24 hours to Serial
    void printNext24Hours();
};
