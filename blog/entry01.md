# Entry 1
##### 11/5/2025

### Context
For this project, I was supposed to pick a JavaScript framework, but my teacher trusted me to take a different path. Since I already have a decent background in JavaScript, I was given the exception to work with C++ on the Arduino IDE, using an ESP32 and an IPS TFT LCD screen to create a **smart alarm clock**.

I picked this because embedded programming seemed like it'd be a challenge for me. I enjoy pushing myself to learn lower-level systems, even if it’s not directly connected to higher-level programming. I also think it’s fun. Like, let’s be honest, it’s always satisfying when hardware actually does what you want it to do.

### Activity One: Tinkering with C++ and Arduino IDE
Before diving into the screen and clock features, I spent time brushing up on some C++ basics and Arduino libraries. I worked with things like:

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> alarms;
alarms.push_back("07:00");
for (auto it = alarms.begin(); it != alarms.end(); ++it) {
    std::cout << *it;
}
```

I also explored Arduino-specific tools like `ArduinoJson` for handling structured data, and `WiFi.h` / `HTTPClient.h` to prepare for potential network connectivity features (like syncing time or weather info).

Even though I haven’t really touched the `eSPI` framework for the LCD yet, I wanted to familiarize myself with the language and libraries first. This way, when I start drawing on the screen or displaying the time, I won’t be completely lost.

### Activity Two: Planning the Smart Alarm Clock
My end goal is to make a fully functional smart alarm clock. Some of the features I’m aiming for:

- Displaying time and date on the IPS TFT LCD
- Setting multiple alarms that are checked efficiently
- Potentially integrating small extras like weather or notifications
- If I have the time and skill, God willing, I'll make a Node server that can make me access the alarms via my phone and a website

The challenge isn’t just in coding, it’s also in understanding how all the hardware pieces interact. This means thinking about memory usage, updating the display efficiently, and making sure my ESP32 doesn’t crash when running multiple tasks.

### Learning Process / EDP
- **Ask / Imagine**: What can my alarm clock do? How can I combine C++ skills with the ESP32 hardware?
- **Plan**: Break down tasks into smaller chunks: get Wi-Fi working first, then the display, then alarms, then my beyond MVP stuff I mentioned before.
- **Create**: Write small test programs (like vectors and JSON handling) to check that I understand the basic functionality.
- **Improve**: Identify what libraries or features will make my life easier, like `ArduinoJson` for storing alarms or HTTP requests for time-syncing.

### Skills Practiced
- Lower-level programming (C++ syntax, data structures, Arduino frameworks, and the labyrinth of pointers)
- Problem-solving for hardware-software integration
- Reading and understanding documentation effectively (cppreference.com, cppshell.com, Arduino Docs)
- Planning and organizing projects with multiple components

### Takeaways
- Challenging yourself in a new environment is worth it. Embedded programming is tough, but it’s improving my overall problem-solving skills, and even though maybe I was stuck on one small issue for hours, multiple times, over the course of multiple days, it's fun.
- Small experiments and tinkering help build confidence before tackling the full project.
- Documentation is key. Videos are nice, but I find that reading official docs or community references sticks better, and it makes me understand them deeper.
- Planning and breaking down a big project into smaller steps makes hardware projects seem much less intimidating.

### Sources
- [C++ Reference](https://www.cppreference.com/)
- [CppShell](https://cppshell.com/)
- [Arduino Documentation](https://docs.arduino.cc/)


[Next](entry02.md)

[Home](../README.md)
