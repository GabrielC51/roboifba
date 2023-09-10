#include <PID_v1.h>

int verm = 2, verde = 4, azul = 7;
int RGB[3][3]; //[n° do sensor][R, G e B]
int corDir = A0, corEsq = A1, corGarra = A2;

//variaveis do PID
double SP, in, out;
int kp = 1, ki = 0, kd = 0;
PID PID(&in, &out, &sp, kp, ki, kd, DIRECT);

void lerlinha(){
  digitalWrite(verm, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(azul, LOW);
  delay(10);

  //lê vermelho
  digitalWrite(verm, HIGH);
  delay(100);
  RGB[0][0] = analogRead(corDir);
  RGB[1][0] = analogRead(corEsq);
  RGB[2][0] = analogRead(corGarra);
  digitalWrite(verm, LOW);

  //lê verde
  digitalWrite(verde, HIGH);
  delay(100);
  RGB[0][1] = analogRead(corDir);
  RGB[1][1] = analogRead(corEsq);
  RGB[2][1] = analogRead(corGarra);
  digitalWrite(verde, LOW);

  //lê azul
  digitalWrite(azul, HIGH);
  delay(100);
  RGB[0][2] = analogRead(corDir);
  RGB[1][2] = analogRead(corEsq);
  RGB[2][2] = analogRead(corGarra);
  digitalWrite(azul, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(corDir, INPUT);
  pinMode(corEsq, INPUT);
  pinMode(corGarra, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);

  pinMode(verm, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(azul, OUTPUT);
  
  sp = 511; //valor de "meio" da entrada analogica
  PID.SetMode(AUTOMATIC);
}

void loop() {
  bool IResq, IRdir;
  lerlinha();
  digitalRead();
}