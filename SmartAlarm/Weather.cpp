#include "Weather.hpp"

const char* WEATHER_API = "https://api.open-meteo.com/v1/forecast?latitude=40.6501&longitude=-73.9496&hourly=temperature_2m,rain,showers&timezone=America%2FNew_York&forecast_days=3";

Weather::Weather() : organizedWeatherData(9000), currentHourIndex(0) {}

String Weather::deriveCondition(float rain, float showers) {
    float total = rain + showers;
    if (total <= 0.0f)   return "Clear";
    if (total < 1.0f)    return "Light rain";
    if (total < 3.0f)    return "Moderate rain";
    return "Heavy rain";
}

void Weather::fetchWeatherData() {
    HTTPClient http;
    http.begin(WEATHER_API);
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
        String stringDataWeather = http.getString();
        deserializeJson(organizedWeatherData, stringDataWeather);
    } else {
        Serial.println("Issue with Weather HTTP");
        Serial.println(httpCode);
    }
    http.end();
}

void Weather::updateCurrentHourIndex(const String& currentTime) {
    // currentTime is "HH:MM", API time is "YYYY-MM-DDTHH:00"
    // Find the first entry whose hour matches
    for (int i = 0; i < 72; i++) {
        String apiTime = organizedWeatherData["hourly"]["time"][i];
        // Extract HH from "YYYY-MM-DDTHH:00"
        int tIdx = apiTime.indexOf('T');
        if (tIdx == -1) continue;
        String apiHour = apiTime.substring(tIdx + 1, tIdx + 3); // "HH"
        String curHour = currentTime.substring(0, 2);             // "HH"
        if (apiHour == curHour) {
            currentHourIndex = i;
            return;
        }
    }
    currentHourIndex = 0;
}

float Weather::getTemp(int offset) {
    int idx = currentHourIndex + offset;
    return organizedWeatherData["hourly"]["temperature_2m"][idx];
}

String Weather::getHourLabel(int offset) {
    int idx = currentHourIndex + offset;
    String apiTime = organizedWeatherData["hourly"]["time"][idx];
    int tIdx = apiTime.indexOf('T');
    if (tIdx == -1) return "??";

    int hour = apiTime.substring(tIdx + 1, tIdx + 3).toInt();
    if (hour == 0)  return "12AM";
    if (hour < 12)  return String(hour) + "AM";
    if (hour == 12) return "12PM";
    return String(hour - 12) + "PM";
}

String Weather::getCurrentCondition() {
    float rain    = organizedWeatherData["hourly"]["rain"][currentHourIndex];
    float showers = organizedWeatherData["hourly"]["showers"][currentHourIndex];
    return deriveCondition(rain, showers);
}

float Weather::getCurrentTemp() {
    return getTemp(0);
}

void Weather::printNext24Hours() {
    for (int i = 0; i < 24; i++) {
        String hourTime   = organizedWeatherData["hourly"]["time"][i];
        float temperature = organizedWeatherData["hourly"]["temperature_2m"][i];
        float rain        = organizedWeatherData["hourly"]["rain"][i];
        float showers     = organizedWeatherData["hourly"]["showers"][i];
        Serial.println(hourTime);
        Serial.print(" Temp: "); Serial.print(temperature);
        Serial.print(" Rain%: "); Serial.println((rain + showers) * 100);
    }
}