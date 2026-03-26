#define TRIG 7
#define ECHO 6

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
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

void loop() {
  long distance = getDistance();
  String state = getCan1State(distance);
  Serial.println("Distance: " + String(distance) + "cm → " + state);
  delay(500);
}