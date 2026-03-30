#include "Weather.hpp"

// API URL
const char* WEATHER_API = "https://api.open-meteo.com/v1/forecast?latitude=40.6501&longitude=-73.9496&hourly=temperature_2m,rain,showers&timezone=America%2FNew_York&forecast_days=3";

Weather::Weather() : organizedWeatherData(9000) {
    // constructor body empty
}

void Weather::fetchWeatherData() {
    HTTPClient http;
    http.begin(WEATHER_API);
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK){
        String stringDataWeather = http.getString();
        deserializeJson(organizedWeatherData, stringDataWeather);
    } else {  
        Serial.println("Issue with Weather HTTP");
        Serial.println(httpCode);
    }
    http.end();
}

void Weather::printNext24Hours() {
    for (int i = 0; i < 24; i++) {
        String hourTime = organizedWeatherData["hourly"]["time"][i];
        float temperature = organizedWeatherData["hourly"]["temperature_2m"][i];
        float rain = organizedWeatherData["hourly"]["rain"][i];
        float showers = organizedWeatherData["hourly"]["showers"][i];

        Serial.println(hourTime);
        Serial.print(" Temp: "); Serial.print(temperature);
        Serial.print(" Rain%: "); Serial.println((rain + showers) * 100);
    }
}
