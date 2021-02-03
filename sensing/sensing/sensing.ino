const int SENSING_PIN = A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int beatValue = analogRead(SENSING_PIN);
  float value = beatValue * 0.0049;
  if (value > 1)
    Serial.println(value);
}
