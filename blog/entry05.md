# Entry 5
##### 4/19/25

### Overview
This entry covers the stretch from where I left off with display work all the way to finishing my MVP. I spent a lot of time dealing with real hardware issues, wiring problems, pin conflicts, logic issues, etc, before I could get everything working together. It was frustrating, but getting there was rewarding, and I'll go in detail later in this entry.

### How I learned
My approach to learning since the beginning stayed consistent, and thankfully, it worked:
- Reading ESP32 datasheets and pinout diagrams to understand which GPIO pins are safe to use
- Experimenting with small isolated tests before integrating features
- Using the serial monitor as my debugging tool
- Going back to the TFT_eSPI docs whenever something didn't work properly.
    - I actually figured out a mini-issue with the library as I worked on it. Feel free to respond, correct, or support my [pull request!](https://github.com/Bodmer/TFT_eSPI/pull/3909)
- Asking myself why something broke instead of just googling the error/fix. This made it easier to go back to my code later.

One thing I really internalized was that the ESP32 is not forgiving about pins. Some are input-only, some are tied to boot behavior, and using the wrong one can break everything without any error message. I learned this the hard way: There is no console that tells you where your code is broken, as this is not code, and it is in the physical world.

### How I finished my MVP
My MVP goal was a working smart alarm clock that displays the time, lets you set alarms, and shows weather data. All visible and displayed on an IPS TFT LCD screen. Getting there required solving a few big problems:
- As hinted at before, wiring. This is where most of my struggle was at. I had the alarm and button working fine, but once I added the screen, everything broke despite being isolated.
- State machine for alarm logic. Once the hardware was sorted, I had to figure out how to structure the logic for the actual alarm. The main issue was that: If the time is the same time as the alarm clock, then ring it. If not, then don't. If the button is pressed, then don't. This sounds clean, but... what if the time is 7:30, the alarm is set to 7:30, and you press the button? While, you're checking all these conditions in isolation, so yes, the button will make the alarm clock stop, but only for that tiny portion of the loop, then it goes back to ringing because it IS 7:30. The way I decided to deal with this is by creating states: `enum AlarmState { IDLE, ALARM_SET, ALARM_RINGING, SNOOZE };`, and use `switch case` instead of independent if statements.
- Example of states usage:
```cpp
enum AlarmState { IDLE, ALARM_SET, ALARM_RINGING, SNOOZE };
AlarmState currentState = IDLE;

void loop() {
  switch (currentState) {
    case IDLE:
      displayManager.drawHomeScreen();
      if (alarmManager.checkAlarm()) currentState = ALARM_RINGING;
      break;
    case ALARM_RINGING:
      buzzer.ring();
      displayManager.drawAlarmScreen();
      if (snoozeBtn.isPressed()) currentState = SNOOZE;
      if (dismissBtn.isPressed()) currentState = IDLE;
      break;
    case SNOOZE:
      delay(300000); // 5 min snooze
      currentState = ALARM_RINGING;
      break;
  }
}
```
- Efficient screen updates. One of the major bugs, not errors, was the screen being very glitchy. This is because the way I drew to it was by replacing the entire frame every update. But this isn't a monitor or a phone, so it was visible the entire refill. I dealt with this by drawing the background in only the region that update would change per time:
```cpp
void DisplayManager::updateTime(String newTime) {
  tft.fillRect(10, 40, 200, 30, TFT_BLACK); // erase only the time region
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(3);
  tft.drawString(newTime, 10, 40);
}
```

### Beyond MVP?
If time permits, I plan on pushing towards my beyond-MVP Goals:
- Node.js server for remote alarm management
- Code cleanup
    - Experiment through lower-level things. Try to not use String or std::string at all.
- Create a PCB for the entire thing to make it more compact and professional

[Previous](entry04.md) | [Next](entry06.md)

[Home](../README.md)
