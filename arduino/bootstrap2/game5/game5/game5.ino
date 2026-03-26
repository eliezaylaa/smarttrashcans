#include <SoftwareSerial.h>

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

void setup() {
  Serial.begin(9600);
  espSerial.begin(115200);
  delay(2000);

  espSerial.println("AT+CWMODE=1");
  readESP();
  espSerial.println("AT+CWJAP=\"Elie\",\"12345679\"");
  Serial.println("Connecting to WiFi...");
  delay(8000);
  Serial.println("Done!");


  String host = "172.20.10.2";
  String url = "/sensor?id=1&value=3.0&key=epitech2026";
  String request = "GET " + url + " HTTP/1.0\r\nHost: " + host + "\r\n\r\n";

  espSerial.println("AT+CIPSTART=\"TCP\",\"172.20.10.2\",3000");

 
  Serial.println("TCP: " + readESP());
  espSerial.println("AT+CIPSEND=" + String(request.length()));
  Serial.println("CIPSEND: " + readESP());

  espSerial.print(request);
  Serial.println("RESPONSE: " + readESP());
}

void loop() {}