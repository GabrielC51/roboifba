#include <PID_v1.h> 

//variaveis do sensor de cor
int verm = 2, verde = 4, azul = 7;
int RGB[3][3]; //[n° do sensor][R, G e B]
int corDir = A0, corEsq = A1, corGarra = A2;
const int fita_verde[2][3] = {//[0 = mínimo | 1 = máximo][R, G e B](ajustar valores com teste e se deve mudar o padrão de 1 byte)
  {0, 900, 0}, 
  {300, 1023, 300}
};
const int branco[3] = {900, 900, 900}; //verificar nescessidade disso

//variaveis do PID
double sp, in, out;
float kp = 0.5, ki = 0, kd = 0; //valores ainda a serem realmente definidos
PID PID(&in, &out, &sp, kp, ki, kd, DIRECT);

void lerlinha(){
  int t; //tempo para ldr "acostumar" com brilho
  digitalWrite(verm, LOW); //força desligamento de todos os leds
  digitalWrite(verde, LOW);
  digitalWrite(azul, LOW);
  delay(10); //pequeno dalay

  //lê vermelho
  digitalWrite(verm, HIGH);
  delay(t);
  RGB[0][0] = analogRead(corDir);
  RGB[1][0] = analogRead(corEsq);
  RGB[2][0] = analogRead(corGarra);
  digitalWrite(verm, LOW);

  //lê verde
  digitalWrite(verde, HIGH);
  delay(t);
  RGB[0][1] = analogRead(corDir);
  RGB[1][1] = analogRead(corEsq);
  RGB[2][1] = analogRead(corGarra);
  digitalWrite(verde, LOW);

  //lê azul
  digitalWrite(azul, HIGH);
  delay(t);
  RGB[0][2] = analogRead(corDir);
  RGB[1][2] = analogRead(corEsq);
  RGB[2][2] = analogRead(corGarra);
  digitalWrite(azul, LOW);
}

String comparaCor(byte porta){
  //retorna cor na porta escolhida, por enquanto apenas preto, verde e branco.
  String retorno;
  if(RGB[porta][0] <= fita_verde[1][0] && RGB[porta][2] <= fita_verde[1][2] && RGB[porta][1] >= fita_verde[0][1] && RGB[porta][1] <= fita_verde[1][1]){
    retorno = "verde";
  }else if(RGB[porta][0] >= branco[0] && RGB[porta][1] >= branco[1] && RGB[porta][2] >= branco[2]){
    retorno = "branco";
  }else{
    retorno = "preto";
  }
  return retorno;
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
  PID.SetMode(AUTOMATIC); //seta controlador pid como automático
}

void loop() {
  bool arraylinha[4]; //armazena informações sobre a linha sendo true para branco e false para preto
  int valorbase = 50; //nosso setpoint, mas em porcentagem
  int in_percent; //guarda a porcentagem da entrada, calculo abaixo
  
  lerlinha(); //faz leitura da linha, podemos unir com a função comparaCor(), para ver se isso facilita o trabalho
  //aqui ele verifica se os dois sensores retornam valores equivalentes a verde
  if(comparaCor(0) == "verde"){
    //virar para o lado do sensor 0
  }else if(comparaCor(1) == "verde"){
    //virar para o lado do sensor 1
  }else{
    arraylinha[0] = digitalRead(12);
    arraylinha[1] = comparaCor(0) == "branco";
    arraylinha[2] = comparaCor(1) == "branco";
    arraylinha[3] = digitalRead(13);
    //verifica o valor armazenado de cada sensor e faz uma operação baseado na cor detectada, variando de 0% a 100%
    if(!arraylinha[0]){
      in_percent = valorbase - 50;
    }else if(!arraylinha[1]){
      in_percent = valorbase - 25;
    }else if(!arraylinha[2]){
      in_percent = valorbase + 25;
    }else if(!arraylinha[3]){
      in_percent = valorbase + 50;
    }
    in = map(in_percent, 0, 100, 0, 1023); //mapea do valor da porcentagem para um valor equivalente na escala aceita pela lib do pid
    PID.Compute(); //faz o pid, depois printa para nossos testes, falta ver a melhor de passar isso para os motores
    Serial.print("in: ");
    Serial.print(in);
    Serial.print(" out: ");
    Serial.println(out);
  }
}