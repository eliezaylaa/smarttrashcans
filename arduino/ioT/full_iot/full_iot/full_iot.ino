#include <SoftwareSerial.h>

#define TRIG 7
#define ECHO 6
#define TILT_PIN 5
#define LDR_PIN A0
#define LED1_PIN 8
#define LED2_PIN 9
#define LED3_PIN 13

SoftwareSerial espSerial(10, 11);

unsigned long tiltStartTime = 0;
bool isTilted = false;

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

void sendAllToAPI(float val1, int val2, float val3) {
  String host = "172.20.10.2";
  String url = "/sensors?id1=" + String(val1) +
               "&id2=" + String(val2) +
               "&id3=" + String(val3) +
               "&key=epitech2026";
  String request = "GET " + url + " HTTP/1.0\r\nHost: " + host + "\r\n\r\n";
  espSerial.println("AT+CIPSTART=\"TCP\",\"172.20.10.2\",3000");
  delay(800);
  espSerial.println("AT+CIPSEND=" + String(request.length()));
  delay(300);
  espSerial.print(request);
  delay(800);
  espSerial.println("AT+CIPCLOSE");
  delay(200);
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
  if (distance > 6) return "empty";
  if (distance >= 3) return "half_full";
  return "full";
}

String getCan2State() {
  int tiltValue = digitalRead(TILT_PIN);
  if (tiltValue == HIGH) {
    tiltStartTime = 0;
    isTilted = false;
    return "normal";
  }
  if (!isTilted) {
    tiltStartTime = millis();
    isTilted = true;
  }
  if (millis() - tiltStartTime > 10000) return "fallen";
  return "tilted";
}

String getCan3State(int value) {
  if (value < 90) return "closed";
  if (value < 700) return "half_open";
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
    blinkLED(LED1_PIN, 300);
  } else {
    blinkLED(LED1_PIN, 100);
  }

  if (can2 == "normal") {
    digitalWrite(LED2_PIN, LOW);
  } else if (can2 == "tilted") {
    blinkLED(LED2_PIN, 300);
  } else {
    blinkLED(LED2_PIN, 100);
  }

  if (can3 == "closed") {
    digitalWrite(LED3_PIN, LOW);
  } else if (can3 == "half_open") {
    blinkLED(LED3_PIN, 300);
  } else {
    blinkLED(LED3_PIN, 100);
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
  if (millis() - lastSend > 3000) {
    sendAllToAPI(distance, can2 == "normal" ? 0 : can2 == "tilted" ? 1 : 2, ldrValue);
    lastSend = millis();
  }
  
  delay(3000); 
}