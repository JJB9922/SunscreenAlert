## SunscreenAlert


Simple concept:

ESP32, LED, Button

Press button

If the LED stays solid red for 10s, then put on sunscreen today as the UV index will exceed 2

If it flashes 10 times, don't worry abt it


Done:
- ESP32 C++ Setup via PlatformIO and ESP32IDF
  
- Button & LED Circuit
  
- Button controls LED animation
  
- ESP32 connects to wifi
  
- ESP32 makes api connection to openweatherapi
  

Needs 2 be done:

- Parse JSON data to find UV index for today
  
- Correspond animation with UV index reading
