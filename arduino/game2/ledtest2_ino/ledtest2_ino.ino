void setup() {
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  // fade LED1 up
  for (int i = 0; i <= 255; i++) {
    analogWrite(11, i);
    delay(5);
  }
  // fade LED1 down
  for (int i = 255; i >= 0; i--) {
    analogWrite(11, i);
    delay(5);
  }
  for (int i = 0; i <= 255; i++) {
    analogWrite(10, i);
    delay(5);
  }
  // fade LED1 down
  for (int i = 255; i >= 0; i--) {
    analogWrite(10, i);
    delay(5);
  }
  for (int i = 0; i <= 255; i++) {
    analogWrite(9, i);
    delay(5);
  }
  // fade LED1 down
  for (int i = 255; i >= 0; i--) {
    analogWrite(9, i);
    delay(5);
  }
  // repeat for LED2 and LED3...
}