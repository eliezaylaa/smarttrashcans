#define TILT_PIN 5

void setup() {
  Serial.begin(9600);
  pinMode(TILT_PIN, INPUT_PULLUP);
}

String getCan2State() {
  int tiltValue = digitalRead(TILT_PIN);
  if (tiltValue == HIGH) return "normal";
  
  unsigned long startTime = millis();
  while (digitalRead(TILT_PIN) == LOW) {
    if (millis() - startTime > 5000) return "fallen";
  }
  return "tilted";
}

void loop() {
  String state = getCan2State();
  Serial.println("Tilt state: " + state);
  delay(500);
}