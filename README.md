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
![image](https://github.com/JJB9922/SunscreenAlert/assets/105116192/1f4451a3-7ef3-404b-b0fa-cde4c90b9f64)

- ESP32 makes api connection to openweatherapi
![image](https://github.com/JJB9922/SunscreenAlert/assets/105116192/1b5af5a8-e10d-435a-8b70-199d76177fdb)


- Parse JSON data to find UV index for today
![image](https://github.com/JJB9922/SunscreenAlert/assets/105116192/485b91eb-e586-4be5-bbd8-326f19e841d6)


Needs 2 be done:
  
- Correspond animation with UV index reading
