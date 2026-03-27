#include <SoftwareSerial.h>

#define TRIG 7
#define ECHO 6
#define TILT_PIN 5
#define LDR_PIN A0
#define LED1_PIN 8
#define LED2_PIN 9
#define LED3_PIN 13

SoftwareSerial espSerial(10, 11);

String readESP() {
  String response = "";
  long timeout = millis() + 5000;
  while (millis() < timeout) {
    while (espSerial.available()) {
      response += (char)espSerial.read();
    }
  }
  return response;
}

void connectWifi() {
  espSerial.println("AT+CWMODE=1");
  readESP();
  espSerial.println("AT+CWJAP=\"Elie\",\"12345679\"");
  Serial.println("Connecting to WiFi...");
  delay(8000);
  Serial.println("Connected!");
}

void sendToAPI(int id, float value) {
  String host = "172.20.10.2";
  String url = "/sensor?id=" + String(id) + "&value=" + String(value) + "&key=epitech2026";
  String request = "GET " + url + " HTTP/1.0\r\nHost: " + host + "\r\n\r\n";
  espSerial.println("AT+CIPSTART=\"TCP\",\"172.20.10.2\",3000");
  delay(2000);
  espSerial.println("AT+CIPSEND=" + String(request.length()));
  delay(1000);
  espSerial.print(request);
  delay(2000);
  espSerial.println("AT+CIPCLOSE");
  delay(500);
}

long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duration = pulseIn(ECHO, HIGH);
  return duration * 0.034 / 2;
}

String getCan1State(long distance) {
  if (distance > 15) return "empty";
  if (distance > 5) return "half_full";
  return "full";
}

String getCan2State() {
  int tiltValue = digitalRead(TILT_PIN);
  if (tiltValue == HIGH) return "normal";
  unsigned long startTime = millis();
  while (digitalRead(TILT_PIN) == LOW) {
    if (millis() - startTime > 10000) return "fallen";
  }
  return "tilted";
}

String getCan3State(int value) {
  if (value < 90) return "closed";
  if (value < 240) return "half_open";
  return "open";
}

void blinkLED(int pin, int interval) {
  digitalWrite(pin, HIGH); delay(interval);
  digitalWrite(pin, LOW); delay(interval);
}

void updateLEDs(String can1, String can2, String can3) {
 
  if (can1 == "empty") {
    digitalWrite(LED1_PIN, LOW);
  } else if (can1 == "half_full") {
    blinkLED(LED1_PIN, 500);
  } else {
    blinkLED(LED1_PIN, 200);
  }

  if (can2 == "normal") {
    digitalWrite(LED2_PIN, LOW);
  } else if (can2 == "tilted") {
    blinkLED(LED2_PIN, 500);
  } else {
    blinkLED(LED2_PIN, 200);
  }

  if (can3 == "closed") {
    digitalWrite(LED3_PIN, LOW);
  } else if (can3 == "half_open") {
    blinkLED(LED3_PIN, 500);
  } else {
    blinkLED(LED3_PIN, 200);
  }
}

void setup() {
  Serial.begin(9600);
  espSerial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TILT_PIN, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  delay(2000);
  connectWifi();
}

void loop() {
  long distance = getDistance();
  String can1 = getCan1State(distance);
  String can2 = getCan2State();
  int ldrValue = analogRead(LDR_PIN);
  String can3 = getCan3State(ldrValue);

  Serial.println("Can1: " + can1 + " | Can2: " + can2 + " | Can3: " + can3);

  updateLEDs(can1, can2, can3);

  static unsigned long lastSend = 0;
  if (millis() - lastSend > 5000) {
    sendToAPI(1, distance);
    sendToAPI(2, can2 == "normal" ? 0 : can2 == "tilted" ? 1 : 2);
    sendToAPI(3, ldrValue);
    lastSend = millis();
  }
}