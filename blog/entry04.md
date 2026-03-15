# Entry 4
##### 3/15/2026

### Overview
Since the last entry, my main focus shifted toward getting real data onto the device. More specifically, fetching live weather data and time over WiFi, displaying the time on the TFT screen, and wiring up the active buzzer for alarm triggering. At this point the project feels about 90% of the way to the MVP.

### How I've been learning
I've been learning through a mixture of:
- Reading API documentation to understand how to parse JSON responses (ArduinoJson)
- Trial and error while debugging HTTP response codes and JSON deserialization issues
- Building features incrementally. I first try to get the data I fetch to simply show up on the serial monitor, then worry about the screen and implementation.

One thing that stood out: I learned that relying on a single time API is fragile (API-block), so I built a simple alternating system that flips between two different APIs on each call. This way, if I get blocked or one goes down, the other can cover it.

### Evidence
#### Example One - Fetching weather data and printing to Serial
```cpp
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
        Serial.print(hourTime);
        Serial.print(" Temp: "); Serial.print(temperature);
        Serial.print(" Rain%: "); Serial.println((rain + showers) * 100);
    }
}
```
Weather dats is currently still only printing to the Serial monitor, I will try to get it on the TFT screen in an efficient manner soon.

#### Example Two - Fetching current time with API alternation
```cpp
String getCurrentTime() {
    static bool useFirstAPI = true;
    const char* firstAPI = "http://worldclockapi.com/api/json/est/now";
    const char* secondAPI = "https://worldtimeapi.org/api/timezone/America/New_York.json";
    const char* apiURL = useFirstAPI ? firstAPI : secondAPI;
    useFirstAPI = !useFirstAPI;

    HTTPClient http;
    http.begin(apiURL);
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        StaticJsonDocument<1024> doc;
        deserializeJson(doc, payload);
        String timeStr;
        if (apiURL == firstAPI) {
            String dateAndTime = doc["currentDateTime"]; // e.g. 2025-09-20T11:59-04:00
            int tIndex = dateAndTime.indexOf('T');
            timeStr = dateAndTime.substring(tIndex + 1);
            int tzIndex = timeStr.indexOf('+');
            if (tzIndex == -1) tzIndex = timeStr.indexOf('-');
            timeStr = timeStr.substring(0, tzIndex);
        } else {
            String dateAndTime = doc["datetime"]; // e.g. 2025-10-13T10:08:19.366299-04:00
            int tIndex = dateAndTime.indexOf('T');
            timeStr = dateAndTime.substring(tIndex + 1, tIndex + 6); // hh:mm
        }
        http.end();
        return timeStr;
    } else {
        Serial.println("Issue with Time HTTP");
        http.end();
        return "";
    }
}
```

#### Example Three - Alarm check and buzzer trigger in the main loop
```cpp
// In loop():
if (millis() - lastTimeUpdate > timeInterval) {
    currentTime = getCurrentTime();
    lastTimeUpdate = millis();
}
if ((millis() - lastWeatherUpdate) > weatherInterval) {
    weather.fetchWeatherData();
    weather.printNext24Hours();
    lastWeatherUpdate = millis();
}

// Alarm check:
if (alarms.checkAlarm(currentTime)) {
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Buzzer should be on");
}
```
```cpp
// In Alarms class:
bool Alarms::checkAlarm(const String& time) {
    return alarmSet.find(time) != alarmSet.end();
}
```

### What I plan on doing next
1. Transfer my code from my [main repo](https://github.com/skele6011/Smart-Alarm-Clock/tree/main) to this one
2. Fitting weather data on the TFT screen
   - Optimizing the screen refresh through maybe the use of fillRect()
3. Button to stop the alarm
4. Connecting everything together
  - MVP Testing once all done



[Previous](entry03.md) | [Next](entry05.md)

[Home](../README.md)
