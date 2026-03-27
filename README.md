# Smart Trash Cans - Cleaning Gotham City

> Epitech MSc IoT Project - Smart waste management system combining
> Arduino sensors, ESP8266 WiFi, Node.js REST API and Unity AR.

## Project Overview

Smart Trash Cans monitors 3 physical trashcans in real time.
Each trashcan has a sensor detecting its state.
An Arduino reads all sensors and sends data to a REST API via ESP-01 WiFi.
A Unity AR app reads the API and dispatches a virtual garbage truck
to collect abnormal trashcans using BFS pathfinding on a road map.

## System Architecture

```
Sensors → Arduino → ESP-01 → WiFi → API → Unity AR
```

## Trashcans

| Can | Color  | Sensor        | Normal | Abnormal        |
| --- | ------ | ------------- | ------ | --------------- |
| 1   | Green  | HC-SR04       | Empty  | Half Full, Full |
| 2   | Blue   | SW-520D Tilt  | Normal | Tilted, Fallen  |
| 3   | Yellow | Photoresistor | Closed | Half Open, Open |

## LED System

| State          | LED Behavior       |
| -------------- | ------------------ |
| Normal         | OFF                |
| Half abnormal  | Slow blink (300ms) |
| Fully abnormal | Fast blink (100ms) |

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
    ├── wiring_setup.md
    ├── trashcan_sensors.md
    └── bfs_pathfinding.md
```

## API Setup

```bash
cd api
npm install
node server.js
```

## API Endpoints

| Endpoint                                          | Description                   |
| ------------------------------------------------- | ----------------------------- |
| GET /sensors?id1=15&id2=0&id3=777&key=epitech2026 | Arduino sends all sensor data |
| GET /status?id=1                                  | Get single trashcan state     |
| GET /status_all                                   | Get all trashcan states       |

## Arduino Setup

1. Install Arduino IDE
2. Connect Arduino Uno R3 via USB
3. Upload final_project.ino
4. Open Serial Monitor at 9600 baud

## Unity AR

- Built with Unity 6 LTS
- AR Foundation + ARCore (Android)
- Grey road detection for truck spawning
- BFS pathfinding to nearest abnormal trashcan
- Real-time API polling every 2 seconds

## Team

- Elie Zaylaa

## School

Epitech MSc International - IoT Module (I-IOT-801-INT-8-1)
