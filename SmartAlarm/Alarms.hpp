#pragma once

#include <set>
#include <Arduino.h>
#include "PrintOnScreen.hpp"

class Alarms {
  private:
    std::set<String> alarmSet;

  public:
    // Constructor
    Alarms();

    // Add / remove alarms
    void addAlarm(const String& time);
    void removeAlarm(const String& time);

    // Check if a time matches an alarm
    bool checkAlarm(const String& time);

    // Display alarms on the screen
    void handleScreenForAlarms(PrintOnScreen& screenPrinting);
};
