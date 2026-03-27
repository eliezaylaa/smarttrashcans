# Smart Trash Cans - Full Wiring Setup

## Components

- Arduino Uno R3
- ESP-01 WiFi Module
- HC-SR04 Ultrasonic Sensor
- SW-520D Tilt Sensor
- Photoresistor (LDR)
- 3x LEDs (Red, Blue, Green)
- 3x 220ohm resistors (LEDs)
- 1x 10K resistor (Photoresistor)
- 1x 1K resistor (Voltage divider)
- 1x 2K resistor (Voltage divider)
- Breadboard
- Jumper wires

## Step 1 - Power Rails

```
Arduino 5V → red (+) rail
Arduino GND → blue (-) rail
```

## Step 2 - LED 1 (Red - Trashcan 1)

```
Arduino Pin 8 → 220ohm resistor → LED long leg (+)
LED short leg (-) → GND rail
```

## Step 3 - LED 2 (Blue - Trashcan 2)

```
Arduino Pin 9 → 220ohm resistor → LED long leg (+)
LED short leg (-) → GND rail
```

## Step 4 - LED 3 (Green - Trashcan 3)

```
Arduino Pin 13 → 220ohm resistor → LED long leg (+)
LED short leg (-) → GND rail
```

## Step 5 - HC-SR04 Ultrasonic Sensor

```
HC-SR04 VCC  → red (+) rail
HC-SR04 GND  → blue (-) rail
HC-SR04 TRIG → Arduino Pin 7
HC-SR04 ECHO → Arduino Pin 6
```

## Step 6 - Tilt Sensor

```
Tilt Pin 1 → Arduino Pin 5
Tilt Pin 2 → blue (-) rail
```

## Step 7 - Photoresistor

```
Photoresistor leg 1 → red (+) rail
Photoresistor leg 2 → Arduino Pin A0
Photoresistor leg 2 → 10K resistor → GND rail
```

## Step 8 - ESP-01 Voltage Divider

```
Arduino Pin 11 → 1K resistor → junction point
junction point → 2K resistor → GND rail
junction point → ESP-01 RX wire
```

## Step 9 - ESP-01 WiFi Module

```
ESP-01 3V3 → Arduino 3.3V
ESP-01 EN  → Arduino 3.3V
ESP-01 GND → blue (-) rail
ESP-01 TX  → Arduino Pin 10
ESP-01 RX  → voltage divider junction
```

## Pin Summary

| Pin  | Component               |
| ---- | ----------------------- |
| 5    | Tilt sensor             |
| 6    | HC-SR04 ECHO            |
| 7    | HC-SR04 TRIG            |
| 8    | LED 1 (Red)             |
| 9    | LED 2 (Blue)            |
| 10   | ESP-01 TX               |
| 11   | ESP-01 RX (via divider) |
| 13   | LED 3 (Green)           |
| A0   | Photoresistor           |
| 3.3V | ESP-01 3V3 + EN         |
| 5V   | HC-SR04 VCC             |
| GND  | All negatives           |
