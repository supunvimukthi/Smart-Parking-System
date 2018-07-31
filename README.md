# Smart-Parking-System
Arduino code for a smart parking system demo.

***This repository contains arduino codes which were used to run on ESP8266-01 and also arduino uno board.***

## Hardware required

- Arduino Uno - to get sensor data and send to ESP-8266-01 through serial transmission.
- ESP8266-01 - to get data from arduino serially and update the firebase through firebase-arduino API
- 4 IR sensor modules - to detect whether parking spot is occupied or not
- Ultranic sensor -  to check for incoming cars to the parking area
- Stepper motor- to control the opening and closing mechnanism of the gate
- I2C LCD display - to display data (parking spots availability and vehicle at the gate)

## Mobile app

- parking slot availability is sent to firebase every 5 seconds
- mobile app retrieves the data and show the availabilty of the parking
- if available you can book the parking slot through the app

**Demo [Video](https://drive.google.com/file/d/1mLEruIdStBPUkekNvVo1nH_hTavGq4-L/view?usp=sharing)

