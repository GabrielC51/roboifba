#include <Wire.h>

int ir[2];
int branco = 500;
int motorEsq1 = 5, motorEsq2 = 6, motorDir1 = 9, motorDir2 = 10;  //portas do motor
int led[3] = {4,7,3};
int ldrEsq = A2, ldrDir = A3;

//Endereco I2C do MPU6050
const int MPU=0x68;

byte rgbEsq[3], rgbDir[3], verd[3] = {30, 40, 40}, cinza[3] = {35, 50, 35}, preto[3] = {20, 20, 20};

void lerCor(){
  unsigned int time = 100;
  for(int i = 0; i <= 2; i++){
    digitalWrite(ledEsq[i], LOW);
    digitalWrite(ledDir[i], LOW);
  }
  for(int i = 0; i <= 2; i++){
    digitalWrite(led[i], HIGH);
    delay(time);
    rgbEsq[i] = map(analogRead(ldrEsq), 0, 1023, 0, 255);
    rgbDir[i] = map(analogRead(ldrDir), 0, 1023, 0, 255);
    digitalWrite(led[i], LOW);
  }
}

int gyro(char eixo){
  //Variaveis para armazenar valores dos sensores
  int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
  Wire.beginTransmission(MPU);
  Wire.write(0x43);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);  
  //Armazena o valor dos sensores nas variaveis correspondentes
  /*
  AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  */
  GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  switch (eixo){
    case 'x':
      return GyX;
    case 'y':
      return GyY;
    case 'z':
      return GyZ;
    default:
      return -32768;
  }
}

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

void giroDir(byte velo, int ang){
  int angAntes = gyro('x');
  while(abs(angAntes - gyro('x')) >= ang){
    analogWrite(motorEsq1, velo);
    analogWrite(motorEsq2, 0);
    analogWrite(motorDir1, 0);
    analogWrite(motorDir2, velo);
  }
}

void giroEsq(byte velo, int ang){
  int angAntes = gyro('x');
  while(abs(angAntes - gyro('x')) >= ang){
    analogWrite(motorEsq1, 0);
    analogWrite(motorEsq2, velo);
    analogWrite(motorDir1, velo);
    analogWrite(motorDir2, 0);
  }
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
  for(int i = 0; i <= 2; i++){
    pinMode(ledEsq[i], INPUT);
    pinMode(ledDir[i], INPUT);
  }
  pinMode(motorEsq1, OUTPUT);
  pinMode(motorEsq2, OUTPUT);
  pinMode(motorDir1, OUTPUT);
  pinMode(motorDir2, OUTPUT);

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);
}

void loop() {
  lerCor();

  if(rgbEsq[0] <= verd[0] && rgbEsq[1] >= verd[1] && rgbEsq[2] <= verd[2] && !(rgbDir[0] <= verd[0] && rgbDir[1] >= verd[1] && rgbDir[2] <= verd[2])){
    giroEsq(60, 90);
  }else if(!(rgbEsq[0] <= verd[0] && rgbEsq[1] >= verd[1] && rgbEsq[2] <= verd[2]) && rgbDir[0] <= verd[0] && rgbDir[1] >= verd[1] && rgbDir[2] <= verd[2]){
    giroDir(60, 90);
  }else if(rgbEsq[0] <= verd[0] && rgbEsq[1] >= verd[1] && rgbEsq[2] <= verd[2] && rgbDir[0] <= verd[0] && rgbDir[1] >= verd[1] && rgbDir[2] <= verd[2]){
    frente(60);
  }else{
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
  }
  delay(10);
}