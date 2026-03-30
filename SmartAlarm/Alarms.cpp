#include "Alarms.hpp"
#include <Arduino.h>

Alarms::Alarms() { }

void Alarms::addAlarm(const String& time) {
    auto result = alarmSet.insert(time);
    if (result.second) {
        Serial.println("Successfully added alarm at " + time);
    } else {
        Serial.println("Already exists");
    }
}

void Alarms::removeAlarm(const String& time) {
    auto erased = alarmSet.erase(time);
    if (erased == 1) {
        Serial.println("Alarm erased");
    } else {
        Serial.println("Alarm not found!");
    }
}

bool Alarms::checkAlarm(const String& time) {
    return alarmSet.find(time) != alarmSet.end();
}

void Alarms::handleScreenForAlarms(PrintOnScreen& screenPrinting) {
    int count = 0;
    std::set<String> returnedAlarms;
    for (const auto& alarmTime : alarmSet) {
        returnedAlarms.insert(alarmTime);
        count++;
        if (count == 3) break;
    }

    if (returnedAlarms.empty()) {
        screenPrinting.printAlarms(false, returnedAlarms);
    } else {
        screenPrinting.printAlarms(true, returnedAlarms);
    }
}
