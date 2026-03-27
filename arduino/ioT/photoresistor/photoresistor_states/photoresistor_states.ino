#define LDR_PIN A0

void setup() {
  Serial.begin(9600);
}

String getCan3State(int value) {
  if (value < 90) return "closed";
  if (value < 240) return "half_open";
  return "open";
}

void loop() {
  int value = analogRead(LDR_PIN);
  String state = getCan3State(value);
  Serial.println("Light: " + String(value) + " → " + state);
  delay(500);
}