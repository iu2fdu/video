void setup() {
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  int v = digitalRead(4);
  digitalWrite(5, v);

}
