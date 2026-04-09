#include "TimeAPI.hpp"

void initTime() {
    // Sync clock once at startup. -18000 = EST (UTC-5), 3600 = DST
    configTime(-18000, 3600, "pool.ntp.org");
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo)) {
        delay(500);
    }
}

String getCurrentTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) return "";
    char buf[6];
    strftime(buf, sizeof(buf), "%H:%M", &timeinfo);
    Serial.println(String(buf));
    return String(buf);
}

// String getCurrentTime() {
//     // Alternate between two APIs
//     static bool useFirstAPI = true;
//     const char* firstAPI = "http://worldclockapi.com/api/json/est/now";
//     const char* secondAPI = "https://worldtimeapi.org/api/timezone/America/New_York.json";

//     const char* apiURL = useFirstAPI ? firstAPI : secondAPI;
//     useFirstAPI = !useFirstAPI; // flip for next call

//     HTTPClient http;
//     http.begin(apiURL);
//     int httpCode = http.GET();

//     if (httpCode == HTTP_CODE_OK) {
//         String payload = http.getString();
//         StaticJsonDocument<1024> doc;
//         deserializeJson(doc, payload);

//         String timeStr;
//         if (apiURL == firstAPI) {
//             // Format: 2025-09-20T11:59-04:00
//             String dateAndTime = doc["currentDateTime"];
//             int tIndex = dateAndTime.indexOf('T');
//             timeStr = dateAndTime.substring(tIndex + 1);
//             int tzIndex = timeStr.indexOf('+');
//             if (tzIndex == -1) tzIndex = timeStr.indexOf('-');
//             timeStr = timeStr.substring(0, tzIndex);
//         } else {
//             // Format: 2025-10-13T10:08:19.366299-04:00
//             String dateAndTime = doc["datetime"];
//             int tIndex = dateAndTime.indexOf('T');
//             timeStr = dateAndTime.substring(tIndex + 1, tIndex + 6); // hh:mm
//         }

//         Serial.println(timeStr);
//         http.end();
//         return timeStr;
//     } else {
//         Serial.println("Issue with Time HTTP");
//         Serial.println(httpCode);
//         Serial.println(apiURL); // Added to figure out which API is broken for later
//         http.end();
//         return "";
//     }
// }
