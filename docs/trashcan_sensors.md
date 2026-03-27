# Smart Trash Cans - Sensors Documentation

## Overview

The system uses 3 physical paper trashcans each equipped with a different sensor.
Each sensor detects a different real-world problem.

---

## Trashcan 1 - Fill Level Detection

**Color:** Green
**Sensor:** HC-SR04 Ultrasonic Sensor
**Pin:** TRIG→7, ECHO→6

### How it works

The HC-SR04 is mounted at the top of the trashcan pointing downward.
It sends ultrasonic pulses and measures the time for the echo to return.
The shorter the distance, the more trash is in the can.

### States

| Distance | State                |
| -------- | -------------------- |
| > 6cm    | Empty (normal)       |
| 3-6cm    | Half Full (abnormal) |
| < 3cm    | Full (abnormal)      |

### LED Behavior

```
Empty → LED OFF
Half Full → LED slow blink (300ms)
Full → LED fast blink (100ms)
```

---

## Trashcan 2 - Tilt Detection

**Color:** Blue
**Sensor:** SW-520D Tilt Sensor
**Pin:** 5

### How it works

The tilt sensor contains a metal ball inside a tube.
When upright the ball touches the contacts (HIGH).
When tilted the ball rolls away (LOW).
A timer tracks how long it has been tilted.

### States

| Condition    | State             |
| ------------ | ----------------- |
| Upright      | Normal (normal)   |
| Tilted < 10s | Tilted (abnormal) |
| Tilted > 10s | Fallen (abnormal) |

### LED Behavior

```
Normal → LED OFF
Tilted → LED slow blink (300ms)
Fallen → LED fast blink (100ms)
```

---

## Trashcan 3 - Lid Detection

**Color:** Yellow
**Sensor:** Photoresistor (LDR)
**Pin:** A0

### How it works

The photoresistor is placed inside the trashcan.
When the lid is closed it is dark inside (low light value).
When the lid opens light enters and the value increases.

### States

| Light Value | State                |
| ----------- | -------------------- |
| < 90        | Closed (normal)      |
| 90-700      | Half Open (abnormal) |
| > 700       | Open (abnormal)      |

### LED Behavior

```
Closed → LED OFF
Half Open → LED slow blink (300ms)
Open → LED fast blink (100ms)
```

---

## Truck Dispatch Rule

```
ANY trashcan in abnormal state → garbage truck dispatched
Normal state → truck skips that trashcan
```
