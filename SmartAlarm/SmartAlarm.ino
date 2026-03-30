// Libraries
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <set>
#include <TFT_eSPI.h>

// #include "secrets.h"

#include "PrintOnScreen.hpp"
#include "Weather.hpp"
#include "Alarms.hpp"
#include "TimeAPI.hpp"

const char* SSID = "wifih";
const char* PASSWORD = "hellohello";

TFT_eSPI tft = TFT_eSPI();
PrintOnScreen screenPrinting(tft);
String screenStartText = "Hi, I am Screen!";

// const int LED_PIN = 2;
// const int BUTTON_PIN = 13;
const int BUZZER_PIN = 19;
Weather weather;
Alarms alarms;

void setup() {
  // Baud #
  Serial.begin(115200);

  // pinMode(LED_PIN, OUTPUT);

  // Connect to WiFi and wait till connection
  WiFi.begin(SSID, PASSWORD);
  Serial.println("Connecting..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Provide IP address and verify connection
  Serial.println("Connected!");
  Serial.println("IP Address: ");
  Serial.print(WiFi.localIP());

  // Screen stuff
  Serial.println("Waiting 3 seconds before starting (screen)");

  // Screen initilaization 
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // Screen text popup
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println(screenStartText);

  // Give short time for text before starting
  delay(1500);
  screenPrinting.printBackground();

  // Get started (time takes only 5 seconds so no need)
  weather.fetchWeatherData();
  weather.printNext24Hours();
  
  // use "button" mode for button
  // pinMode(BUTTON_PIN, INPUT_PULLUP);
  // // Initialize buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, HIGH);
}

// Flags
unsigned long lastWeatherUpdate = 0;
const unsigned long weatherInterval = 3600000; // 1 hour in milliseconds

const unsigned int timeInterval = 5000;
unsigned long lastTimeUpdate = 0;

const unsigned int alarmInterval = 5000;
unsigned long lastAlarmUpdate = 0;

const unsigned int backgroundInterval = 4000;
unsigned long lastBackgroundUpdate = 0;

String currentTime = "";

void loop() {
  if (millis() - lastTimeUpdate > timeInterval) {
    currentTime = getCurrentTime();
    Serial.println(currentTime);
    lastTimeUpdate = millis();
  }

  if ((millis() - lastWeatherUpdate) > weatherInterval) {
    weather.fetchWeatherData();
    weather.printNext24Hours();
    lastWeatherUpdate = millis();
  }

  String timeInput = "";
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '|') {
      Serial.println("Please enter time then press enter: ");
      while (true) {
        if (Serial.available() > 0) {
          char t = Serial.read();
          if (t == '\n') break;
          if (t != '\r') timeInput += t;
        }
      }
      alarms.addAlarm(timeInput);
    }
  }

  

  // ALL What's below to be changed !!! 
  
  if (alarms.checkAlarm(currentTime)) {
    // digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Buzzer should be on");
  }

  // int buttonState = digitalRead(BUTTON_PIN);
  // if (buttonState == LOW) {
  //   Serial.println("Button Pressed!");
  //   digitalWrite(BUZZER_PIN, LOW);
  // } else {
  //   digitalWrite(BUZZER_PIN, HIGH);
  // }
  
  if (millis() - lastBackgroundUpdate > backgroundInterval) {
    screenPrinting.printBackground();
    screenPrinting.printTime(currentTime);
    alarms.handleScreenForAlarms(screenPrinting);

    lastBackgroundUpdate = millis();
  }
  
}
