void setup() {
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(9, 255);
  analogWrite(10, 255);
}
