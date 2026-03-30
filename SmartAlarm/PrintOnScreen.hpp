#pragma once

#include <TFT_eSPI.h>
#include <set>
#include <Arduino.h>

class PrintOnScreen {
  private:
    TFT_eSPI& tft; // reference to TFT object

  public:
    // Constructor takes a reference to the TFT object
    PrintOnScreen(TFT_eSPI& tftObj);

    void printBackground();
    void printTime(String time);
    void printAlarms(bool isAlarm, std::set<String> alarms);
};
