# Tool Learning Log

## Tool: **Arduino C++**

## Project: **Smart Alarm Clock**

---

### 9/18/2025:
#### Challenge: API directs to null
* Maybe http goes to https
  * Use https immediately -- Didn’t work
* if (httpCode > 0) -- Didn’t work
* SSL verification -- Didn’t work
* Check HTTPCode first -- Worked
  * 429, meaning too many requests. Turned out I accidentally used it once while forgetting to set a delay. Just changed the API


### 9/20/2025:
#### Challenege: Get just time from JSON data
* Issue: currentDateTime: "2025-09-18T19:32-04:00"
  * I want just the time
* Look for a regular expression library -- Didn't work
  * Not lightweight. Working on microcontroller
* Pointers -- Didn't work-ish
  * Mini-Crashout session (very hard)
  * [I figured it out LATER but I had already found a fix (which is below)]
* String Methods -- Worked
  * String::indexOf()
  * String::substring()

### 11/12/25:
#### Challenge: Screen doesn’t fit in breadboard
* Tried two breadboards together
  * Pin gap made it not work
* Tried to turn a wire around the pin
  * Too loose and dangerous for V pins
* Bought F-F jumper wires
  * Worked.

### 11/21/25:
#### Challenge: Get screen to display correctly
* Issue: Pure gray
* When tried to change background or add text, gray will just flicker instead.
* Fixes:
  * Tried to rematch pins (failed)
  * Tried to use a different library (failed)
  * Tried to manually adjust libraries (failed)
  * Tried to write code in pure C++ (semi-pass, got better stripes * * updates, colors were still gray sided)
  * Tried a different screen with pure C++ and externs of C (passed!)





<!--
* Links you used today (websites, videos, etc)
* Things you tried, progress you made, etc
* Challenges, a-ha moments, etc
* Questions you still have
* What you're going to try next
-->
