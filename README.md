# Smart Trash Cans - Cleaning Gotham City

> Epitech MSc IoT Project - Smart waste management system using Arduino, ESP8266, Node.js API and Unity AR.

## Project Overview

Smart Trash Cans is an IoT system that monitors 3 physical trashcans in real time. Each trashcan has sensors that detect its state and sends data to an API. A Unity AR app reads the API and dispatches a virtual garbage truck to collect abnormal trashcans using BFS pathfinding.

## System Architecture

```
Sensors → Arduino → ESP-01 → WiFi → API → Unity AR
```

## Trashcans

| Trashcan | Color  | Sensor             | Normal State | Abnormal States |
| -------- | ------ | ------------------ | ------------ | --------------- |
| Can 1    | Green  | HC-SR04 Ultrasonic | Empty        | Half Full, Full |
| Can 2    | Blue   | SW-520D Tilt       | Normal       | Tilted, Fallen  |
| Can 3    | Yellow | Photoresistor      | Closed       | Half Open, Open |

## Hardware Components

- Arduino Uno R3
- ESP-01 WiFi Module
- HC-SR04 Ultrasonic Sensor
- SW-520D Tilt Sensor
- Photoresistor (LDR)
- 1x LED
- 1x LCD Module
- Resistors, Breadboard, Jumper Wires

## LED Behavior

```
All normal       → LED OFF
Any half abnormal → LED slow blink
Any fully abnormal → LED fast blink
All abnormal     → LED very fast blink → truck dispatched!
```

## LCD Display

Shows current trashcan state when truck arrives:

```
Line 1: Truck at Can 1
Line 2: State: FULL
```

## Project Structure

```
smarttrashcans/
├── arduino/
│   ├── game1_blink/
│   ├── game2_leds/
│   ├── game3_buttons/
│   ├── bootstrap2/
│   └── final_project/
├── unity/
├── api/
│   ├── server.js
│   ├── package.json
│   └── data/
│       └── state.json
└── docs/
    ├── README.md
    └── arduinobasics.md
```

## API Setup

```bash
cd api
npm install
node server.js
```

API runs on `http://localhost:3000`

### Endpoints

| Method | Endpoint                              | Description               |
| ------ | ------------------------------------- | ------------------------- |
| GET    | /sensor?id=1&value=15&key=epitech2026 | Arduino sends sensor data |
| GET    | /status?id=1                          | Get single trashcan state |
| GET    | /status_all                           | Get all trashcan states   |

### Sensor Values

**Trashcan 1 (HC-SR04):**

```
value > 15cm = empty
value 5-15cm = half_full
value < 5cm  = full
```

**Trashcan 2 (Tilt sensor):**

```
value = 0 = normal
value = 1 = tilted
value = 2 = fallen
```

**Trashcan 3 (Photoresistor):**

```
value > 800 = closed
value 400-800 = half_open
value < 400 = open
```

## Arduino Setup

1. Install Arduino IDE
2. Connect Arduino Uno R3 via USB
3. Install SoftwareSerial library
4. Upload final_project.ino
5. Open Serial Monitor at 9600 baud

## ESP-01 WiFi Setup

```
ESP-01 3V3  → Arduino 3.3V
ESP-01 GND  → Arduino GND
ESP-01 EN   → Arduino 3.3V
ESP-01 TX   → Arduino Pin 10
ESP-01 RX   → Voltage divider → Arduino Pin 11
```

Voltage divider:

```
Arduino Pin 11 → 1K resistor → ESP-01 RX
                               + 2K resistor → GND
```

## Unity AR App

- Built with Unity 6 LTS
- AR Foundation + ARKit (iOS) / ARCore (Android)
- Detects grey road on drawn map
- Spawns garbage truck on random road point
- BFS pathfinding to nearest abnormal trashcan
- Truck waits until trashcan returns to normal
- LCD updates when truck arrives at each trashcan

## Testing Without Unity

```bash
# Start API
node server.js

# Simulate sensor data
curl "http://localhost:3000/sensor?id=1&value=3&key=epitech2026"

# Check states
curl "http://localhost:3000/status_all"
```

## Team

- Elie Zaylaa
- Nour Afaqi
- Muhammad Daniyal Hijaz

## School

Epitech MSc International - IoT Module
