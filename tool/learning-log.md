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



<!-- 
* Links you used today (websites, videos, etc)
* Things you tried, progress you made, etc
* Challenges, a-ha moments, etc
* Questions you still have
* What you're going to try next
-->
