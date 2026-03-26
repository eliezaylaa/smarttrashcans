# SmartTrashCans API

## Setup

```bash
npm install
node server.js
```

## Endpoints

- GET /sensor?id=1&value=15&key=epitech2026
- GET /status?id=1
- GET /status_all

## States

- Can 1 (HC-SR04): empty / half_full / full
- Can 2 (Tilt): normal / tilted / fallen
- Can 3 (Photoresistor): closed / half_open / open
