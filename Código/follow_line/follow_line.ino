int ir[2];
int branco = 500;
int motorEsq1 = 5, motorEsq2 = 6, motorDir1 = 9, motorDir2 = 10;  //valor base do motor

void frente(byte velo){
  analogWrite(motorEsq1, velo);
  analogWrite(motorEsq2, 0);
  analogWrite(motorDir1, velo);
  analogWrite(motorDir2, 0);
}

void tras(byte velo){
  analogWrite(motorDir1, 0);
  analogWrite(motorDir2, velo);
  analogWrite(motorEsq1, 0);
  analogWrite(motorEsq2, velo);
}
void curvaEsq(byte velo, byte dif){
  if(velo - dif < 0){
    parar();
    return;
  }
  analogWrite(motorEsq1, velo);
  analogWrite(motorEsq2, 0);
  analogWrite(motorDir1, velo - dif);
  analogWrite(motorDir2, 0);
}
void curvaDir(byte velo, byte dif){
  if(velo - dif < 0){
    parar();
    return;
  }
  analogWrite(motorEsq1, velo - dif);
  analogWrite(motorEsq2, 0);
  analogWrite(motorDir1, velo);
  analogWrite(motorDir2, 0);
}

void parar(){
  analogWrite(motorDir1, 0);
  analogWrite(motorDir2, 0);
  analogWrite(motorEsq1, 0);
  analogWrite(motorEsq2, 0);
}

void setup() {
  //put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(motorEsq1, OUTPUT);
  pinMode(motorEsq2, OUTPUT);
  pinMode(motorDir1, OUTPUT);
  pinMode(motorDir2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ir[0] = analogRead(A0);
  ir[1] = analogRead(A1);
  bool ir_bool[2];
  ir_bool[0] = ir[0] >= 600;
  ir_bool[1] = ir[1] >= 600;
  
  if(ir_bool[0] && ir_bool[1]){
    frente(60);
  }else if(ir_bool[0]){
    curvaDir(60, 50);
  }else if(ir_bool[1]){
    curvaEsq(60, 50);
  }else{
    frente(60);
  }
  delay(10);
}