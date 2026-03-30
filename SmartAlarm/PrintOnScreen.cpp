#include "PrintOnScreen.hpp"

PrintOnScreen::PrintOnScreen(TFT_eSPI& tftObj) : tft(tftObj) {
    // constructor body empty
}

void PrintOnScreen::printBackground() {
    tft.fillScreen(TFT_NAVY);
}

void PrintOnScreen::printTime(String time) {
    tft.setTextColor(TFT_WHITE, TFT_NAVY);
    tft.setTextSize(4);
    tft.setCursor(15, 15);
    tft.print("Time: ");
    tft.print(time);
}

void PrintOnScreen::printAlarms(bool isAlarm, std::set<String> alarms) {
    if (!isAlarm) {
        tft.setTextColor(TFT_WHITE, TFT_NAVY);
        tft.setTextSize(2);
        tft.setCursor(330, 15);
        tft.print("Alarms: ");
        tft.setCursor(300, 57);
        tft.print("No alarms set");
    } else {
        tft.setTextColor(TFT_WHITE, TFT_NAVY);
        tft.setTextSize(2);
        tft.setCursor(330, 15);
        tft.print("Alarms: ");

        int count = 0;
        for (const auto& alarm : alarms) {
            tft.setCursor(320, 57 + (count * 22));
            tft.print(alarm);
            if (count == 3) break;
            count++;
        }
    }
}
