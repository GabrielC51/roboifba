#include <PID_v1.h>

int ir[2];
int branco = 500, in_perc;
double in, out, sp = 500; //valor do PID
float kp = 0.5, ki = 0, kd = 0; //valores ainda a serem realmente definidos
int vb = 205, motorEsq1 = 5, motorEsq2 = 6, motorDir1 = 9, motorDir2 = 10;  //valor base do motor
PID pid(&in, &out, &sp, kp, ki, kd, DIRECT);


void setup() {
  //put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(motorEsq1, OUTPUT);
  pinMode(motorEsq2, OUTPUT);
  pinMode(motorDir1, OUTPUT);
  pinMode(motorDir2, OUTPUT);
  pid.SetMode(AUTOMATIC);  //seta controlador pid como automático
}

void loop() {
  // put your main code here, to run repeatedly:
  ir[0] = analogRead(A0);
  ir[1] = analogRead(A1);
  bool ir_bool[0];
  ir_bool[0] = (ir[0] >= 600) ? false:true;
  ir_bool[1] = (ir[1] >= 600) ? false:true;
  Serial.print(ir[0]);
  Serial.print("|");
  Serial.println(ir[1]);
  if(ir_bool[0]){
    analogWrite(motorDir1, 50);
    analogWrite(motorEsq1, 0);
    analogWrite(motorDir2, 0);
    analogWrite(motorEsq2, 50);
  }else if(ir_bool[1]){
    analogWrite(motorDir1, 0);
    analogWrite(motorEsq1, 50);
    analogWrite(motorDir2, 50);
    analogWrite(motorEsq2, 0);
  }else{
    analogWrite(motorDir1, 50);
    analogWrite(motorEsq1, 50);
    analogWrite(motorDir2, 0);
    analogWrite(motorEsq2, 0);
  }
  delay(600);
}