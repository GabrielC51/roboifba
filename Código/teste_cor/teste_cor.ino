int ledverm = 4;
int ledverd = 7;
int ledazul = 3;
int ldr = A2;

byte rgb[3], verd[3] = {30, 40, 40}, cinza[3] = {35, 50, 35}, preto[3] = {20, 20, 20};

void lerCor(){
  unsigned int time = 100;
  digitalWrite(ledverm, HIGH);
  digitalWrite(ledverd, LOW);
  digitalWrite(ledazul, LOW);
  delay(time);
  rgb[0] = map(analogRead(ldr), 0, 1023, 0, 255);
  digitalWrite(ledverm, LOW);
  digitalWrite(ledverd, HIGH);
  delay(time);
  rgb[1] = map(analogRead(ldr), 0, 1023, 0, 255);
  digitalWrite(ledverd, LOW);
  digitalWrite(ledazul, HIGH);
  delay(time);
  rgb[2] = map(analogRead(ldr), 0, 1023, 0, 255);
  digitalWrite(ledazul, LOW);
}

void setup(){
  Serial.begin(9600);
  pinMode(ledverm, OUTPUT);
  pinMode(ledverd, OUTPUT);
  pinMode(ledazul, OUTPUT);
  pinMode(ldr, INPUT);
}

void loop(){
  lerCor();

  String cor;
  if(rgb[0] <= verd[0] && rgb[1] >= verd[1] && rgb[2] <= verd[2]){
    cor = "verde";
  }else if(rgb[0] >= cinza[0] && rgb[1] >= cinza[1] && rgb[2] >= cinza[2]){
    if(rgb[0] > 100 && rgb[1] > 100 && rgb[2] > 100){
      cor = "branco";
    }else{
      cor = "cinza";
    }
  }else if (rgb[0] <= preto[0] && rgb[1] <= preto[1] && rgb[2] <= preto[2]){
    cor = "preto";
  }else{
    cor = "outra cor";
  }
  
  Serial.print(cor);
  Serial.print(": (");
  Serial.print(rgb[0]);
  Serial.print(",");
  Serial.print(rgb[1]);
  Serial.print(",");
  Serial.print(rgb[2]);
  Serial.println(")");
  delay(1000);
}