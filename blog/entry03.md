# Entry 3
##### 2/7/2026
### Overview
Over winter break, my main focus was improving my ability to structure the project like a real C++ program instead of keeping everything inside a single .ino file. I also practiced using the TFT_eSPI library to display information on a TFT screen, including text layout, screen updates, and basic UI elements.

### How I've been learning
I’ve been learning through a mix of:
* experimenting with small test sketches (ex: “draw text,” “draw shapes,” “screen refresh test”)
* reading TFT_eSPI examples and documentation
* debugging compile errors while splitting code into .hpp and .cpp files
* gradually building features into my project instead of trying to do everything at once
I also learned that libraries like TFT_eSPI require careful setup (pins, display driver, User_Setup), and that screen drawing works best when I avoid constantly re-drawing everything every loop.
### Evidence
Here are some examples of the work I did:
#### Example 1 — TFT_eSPI initialization + drawing text
```cpp
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString("Smart Alarm Clock", 10, 10);
}
```
#### Example 2 — Basic C++ class structure
**DisplayManager.hpp**
```cpp
#ifndef DISPLAY_MANAGER_HPP
#define DISPLAY_MANAGER_HPP

#include <TFT_eSPI.h>

class DisplayManager {
  public:
    DisplayManager(TFT_eSPI &display);
    void begin();
    void drawHomeScreen();

  private:
    TFT_eSPI &tft;
};
#endif
```
**DisplayManager.cpp**
```cpp
#include "DisplayManager.hpp"

DisplayManager::DisplayManager(TFT_eSPI &display) : tft(display) {}

void DisplayManager::begin() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
}

void DisplayManager::drawHomeScreen() {
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString("Alarm Clock", 10, 10);
}
```
Here, in example two, I learned that #ifndef, define, endif can sometimes be confusing, and it is way easier to simply write `#pragma once` at the top of my code.

### What I plan on doing next
Next, I am planning on:
1. Having efficient screen updating
   * partial redraw techniques
   * using `fillRect()` to erase only a small area
   * minimizing flicker and improving performance
2. Alarm logic + state machine
   * Use clear states such as `idle`. `alarm`, `armed`, `alarm ringing`, & `snooze`
   * organizing the logic so it doesn’t become messy inside `loop()`
3. Buttons / input
   * debouncing physical buttons
   * If I am able to later, make a NodeJs server that makes it easier to set and remove alarms via browser
  




[Previous](entry02.md) | [Next](entry04.md)

[Home](../README.md)
