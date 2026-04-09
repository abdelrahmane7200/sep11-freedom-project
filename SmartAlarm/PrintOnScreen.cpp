#include "PrintOnScreen.hpp"

PrintOnScreen::PrintOnScreen(TFT_eSPI& tftObj) : tft(tftObj) {}

uint16_t PrintOnScreen::hex(uint32_t c) {
    uint8_t r = (c >> 16) & 0xFF;
    uint8_t g = (c >> 8)  & 0xFF;
    uint8_t b =  c        & 0xFF;
    return tft.color565(r, g, b);
}

void PrintOnScreen::drawHLine(int x1, int x2, int y) {
    tft.drawFastHLine(x1, y, x2 - x1, hex(COL_DIVIDER));
}

void PrintOnScreen::drawVLine(int x, int y1, int y2) {
    tft.drawFastVLine(x, y1, y2 - y1, hex(COL_DIVIDER));
}

void PrintOnScreen::printBackground() {
    tft.fillScreen(hex(BG_DARK));

    // Dividers
    drawVLine(DIVIDER_X, 10, STATUS_BAR_Y);
    drawHLine(LEFT_X, DIVIDER_X, DIVIDER1_Y);
    drawHLine(LEFT_X, DIVIDER_X, DIVIDER2_Y);

    // Status bar background
    tft.fillRect(0, STATUS_BAR_Y, SCREEN_W, SCREEN_H - STATUS_BAR_Y, hex(BG_STATUS));
    drawHLine(0, SCREEN_W, STATUS_BAR_Y);
}

void PrintOnScreen::printTime(const String& time) {
    tft.setTextColor(TFT_WHITE, hex(BG_DARK));
    tft.setTextSize(1);
    tft.setFreeFont(NULL);
    // Use size 6 for big time display
    tft.setTextSize(6);
    tft.setCursor(LEFT_X, TIME_Y - 40); // size 6 = 8px*6=48px tall, anchor at top
    tft.print(time);
}

void PrintOnScreen::printDate(const String& date) {
    tft.setTextColor(hex(COL_MUTED), hex(BG_DARK));
    tft.setTextSize(2);
    tft.setCursor(LEFT_X, DATE_Y - 14);
    tft.print(date);
}

void PrintOnScreen::printWeather(float tempC, const String& condition, const String& location) {
    // Label
    tft.setTextColor(hex(COL_MUTED), hex(BG_DARK));
    tft.setTextSize(1);
    tft.setCursor(LEFT_X, WEATHER_LABEL_Y - 7);
    tft.print("WEATHER");

    // Temperature
    tft.setTextColor(TFT_WHITE, hex(BG_DARK));
    tft.setTextSize(4);
    tft.setCursor(LEFT_X, TEMP_Y - 28);
    tft.print((int)tempC);
    tft.print("C");

    // Location
    tft.setTextColor(hex(COL_MUTED), hex(BG_DARK));
    tft.setTextSize(2);
    tft.setCursor(LEFT_X, LOCATION_Y - 14);
    tft.print(location);

    // Condition
    tft.setCursor(LEFT_X, CONDITION_Y - 14);
    tft.print(condition);
}

void PrintOnScreen::printForecast(float temps[6], String hours[6]) {
    // Label
    tft.setTextColor(hex(COL_MUTED), hex(BG_DARK));
    tft.setTextSize(1);
    tft.setCursor(LEFT_X, FORECAST_LABEL_Y - 7);
    tft.print("NEXT 6 HOURS");

    // Column centers, shifted ~10px left from mockup
    // Spread 6 columns across x=10 to x=225
    const int colCenters[6] = { 20, 57, 94, 131, 168, 205 };

    for (int i = 0; i < 6; i++) {
        int cx = colCenters[i];

        // Hour label
        tft.setTextColor(hex(COL_MUTED), hex(BG_DARK));
        tft.setTextSize(1);
        // Center text manually: each char is 6px wide at size 1
        int labelLen = hours[i].length();
        int labelX = cx - (labelLen * 6) / 2;
        tft.setCursor(labelX, FORECAST_TIME_Y - 7);
        tft.print(hours[i]);

        // Temp
        tft.setTextColor(TFT_WHITE, hex(BG_DARK));
        char tempBuf[6];
        snprintf(tempBuf, sizeof(tempBuf), "%dC", (int)temps[i]);
        int tempLen = strlen(tempBuf);
        int tempX = cx - (tempLen * 6) / 2;
        tft.setCursor(tempX, FORECAST_TEMP_Y - 7);
        tft.print(tempBuf);
    }
}

void PrintOnScreen::printAlarms(bool hasAlarms, const std::set<String>& alarms) {
    // Label
    tft.setTextColor(hex(COL_MUTED), hex(BG_DARK));
    tft.setTextSize(1);
    tft.setCursor(RIGHT_X, ALARM_LABEL_Y - 7);
    tft.print("ALARMS");

    int row = 0;
    int rowY = ALARM_START_Y;

    if (hasAlarms) {
        for (const auto& alarmTime : alarms) {
            if (row >= MAX_ALARMS) break;

            // Row background
            tft.fillRoundRect(ALARM_LEFT, rowY, ALARM_W, ALARM_ROW_H - 4, 4, hex(BG_PANEL));

            // Time centered in row
            tft.setTextColor(TFT_WHITE, hex(BG_PANEL));
            tft.setTextSize(3);
            // 5 chars "HH:MM", each char ~18px wide at size 3
            int timeX = ALARM_LEFT + (ALARM_W / 2) - (5 * 18) / 2 - 20;
            int timeY = rowY + (ALARM_ROW_H - 4) / 2 - 12;
            tft.setCursor(timeX, timeY);
            tft.print(alarmTime);

            // ON badge
            int badgeX = ALARM_LEFT + ALARM_W - 42;
            int badgeY = rowY + (ALARM_ROW_H - 4) / 2 - 9;
            tft.fillRoundRect(badgeX, badgeY, 30, 18, 3, hex(BG_ON_BADGE));
            tft.setTextColor(hex(COL_GREEN), hex(BG_ON_BADGE));
            tft.setTextSize(1);
            tft.setCursor(badgeX + 6, badgeY + 5);
            tft.print("ON");

            row++;
            rowY += ALARM_ROW_H;
        }
    }

    // Fill remaining slots as empty
    for (int i = row; i < MAX_ALARMS; i++) {
        tft.fillRoundRect(ALARM_LEFT, rowY, ALARM_W, ALARM_ROW_H - 4, 4, hex(BG_EMPTY));
        tft.setTextColor(hex(COL_EMPTY), hex(BG_EMPTY));
        tft.setTextSize(1);
        int emptyX = ALARM_LEFT + ALARM_W / 2 - 30;
        int emptyY = rowY + (ALARM_ROW_H - 4) / 2 - 4;
        tft.setCursor(emptyX, emptyY);
        tft.print("-- empty --");
        rowY += ALARM_ROW_H;
    }
}

void PrintOnScreen::printStatusBar(bool wifiConnected, bool ntpSynced) {
    int barY = STATUS_BAR_Y + 9;

    // Left: version
    tft.setTextColor(hex(COL_EMPTY), hex(BG_STATUS));
    tft.setTextSize(1);
    tft.setCursor(16, barY);
    tft.print("SmartAlarm v1.0");

    // Center: WiFi
    tft.setTextColor(wifiConnected ? hex(COL_GREEN) : TFT_RED, hex(BG_STATUS));
    tft.setCursor(185, barY);
    tft.print(wifiConnected ? "WiFi connected" : "WiFi off");

    // Right: NTP
    tft.setTextColor(ntpSynced ? hex(COL_GREEN) : hex(COL_MUTED), hex(BG_STATUS));
    tft.setCursor(370, barY);
    tft.print(ntpSynced ? "NTP OK" : "NTP --");
}