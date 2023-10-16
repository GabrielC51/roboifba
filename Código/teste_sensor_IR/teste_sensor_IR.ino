int ir[2];
int branco = 600;

void setup() {
  //put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ir[0] = analogRead(A0);
  ir[1] = analogRead(A1);
  bool ir_bool[0];
  ir_bool[0] = ir[0] >= 600;
  ir_bool[1] = ir[1] >= 600;
  Serial.print(ir[0]);
  Serial.print("|");
  Serial.println(ir[1]);
  delay(500);
}