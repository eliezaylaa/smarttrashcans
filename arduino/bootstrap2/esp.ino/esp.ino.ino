#include <SoftwareSerial.h>

SoftwareSerial espSerial(10, 11);

void setup() {
  Serial.begin(9600);
  espSerial.begin(115200);
  Serial.println("Testing ESP8266...");
  espSerial.println("AT");
}

void loop() {
  if (espSerial.available()) {
    Serial.write(espSerial.read());
  }
  if (Serial.available()) {
    espSerial.write(Serial.read());
  }
}