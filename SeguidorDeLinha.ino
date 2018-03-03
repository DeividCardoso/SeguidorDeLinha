//inclusão das bibliotecas
#include <AFMotor.h>

//Definição dos sensores
#define S_Esq 5
#define S_Meio 4
#define S_Dir 3

//Definição dos motores
AF_DCMotor Motor_Esquerda(4);
AF_DCMotor Motor_Direita(1);

//Variaveis Globais
  int Esquerda;
  int Meio;
  int Direita;
  int UltimaLeitura;
  int Contador;
  
void setup() {
  Serial.begin(9600);
  //Desliga os motores ao iniciar
  Motor_Esquerda.run(RELEASE);
  Motor_Direita.run(RELEASE);
  UltimaLeitura = 0;
  Contador = 0;
}

void TudoParaEsquerda(){
  Motor_Direita.setSpeed(100);    //Define velocidade máxima para o motor da direita
  Motor_Direita.run(FORWARD);     //Gira o motor no sentido horário
  Motor_Esquerda.run(RELEASE);    //Desliga o motor da esquerda
}

void TudoParaDireita(){
  Motor_Esquerda.setSpeed(100);   //Define velocidade máxima para o motor da esquerda
  Motor_Esquerda.run(FORWARD);    //Gira o motor no sentido horário
  Motor_Direita.run(RELEASE);     //Desliga o motor da direita
}

void ViraParaEsquerda(int dir, int esq){
  int dif = (dir - esq)/2;
  Motor_Esquerda.setSpeed(100);
  Motor_Direita.setSpeed(100 - dif);
  Motor_Esquerda.run(FORWARD);
  Motor_Direita.run(FORWARD);
}

void ViraParaDireita(int esq, int dir){
  int dif = (esq - dir)/2;
  Motor_Esquerda.setSpeed(100 - dif);
  Motor_Direita.setSpeed(100);
  Motor_Esquerda.run(FORWARD);
  Motor_Direita.run(FORWARD);
}

void ProcuraLinha(){
  Contador = 0;
  if(UltimaLeitura == 1){
    do{
      Motor_Direita.setSpeed(100);
      Motor_Esquerda.setSpeed(100);
      Motor_Direita.run(FORWARD);
      Motor_Esquerda.run(BACKWARD);
      if(S_Esq > 500 || S_Meio > 500 || S_Dir > 500){
        break;
      }
      Contador++;
    }while(Contador <= 10000);
  }
  else if(UltimaLeitura == -1){
    do{
      Motor_Direita.setSpeed(100);
      Motor_Esquerda.setSpeed(100);
      Motor_Direita.run(BACKWARD);
      Motor_Esquerda.run(FORWARD);
      if(S_Esq > 500 || S_Meio > 500 || S_Dir > 500){
        break;
      }
      Contador++;
    }while(Contador <= 10000);
  }
  else{
    do{
      Motor_Direita.setSpeed(100);
      Motor_Esquerda.setSpeed(100);
      Motor_Direita.run(BACKWARD);
      Motor_Esquerda.run(FORWARD);
      if(S_Esq > 500 || S_Meio > 500 || S_Dir > 500){
        break;
      }
      Contador++;
    }while(Contador <= 10000);
  }
}

void loop() {
  Esquerda = analogRead(S_Esq);
  Meio = analogRead(S_Meio);
  Direita = analogRead(S_Dir);
  Serial.print("Esq: ");
  Serial.print(Esquerda);
  Serial.print("  - Meio: ");
  Serial.print(Meio);
  Serial.print("  - Dir: ");
  Serial.println(Direita);

  if(Meio > Direita * 3 && Meio > Esquerda * 3){
    UltimaLeitura = 0;
    Motor_Esquerda.setSpeed(100);
    Motor_Direita.setSpeed(100);
    Motor_Esquerda.run(FORWARD);
    Motor_Direita.run(FORWARD);
  }
  else if(Meio * 2 < Direita){
    UltimaLeitura = 1;
    TudoParaDireita();
  }
  else if(Meio * 2 < Esquerda){
    UltimaLeitura = -1;
    TudoParaEsquerda();
  }
  else if(Direita > Esquerda * 2){
     UltimaLeitura = -1;
     ViraParaEsquerda(Direita, Esquerda);
  }
  else if(Esquerda > Direita * 2){  
    UltimaLeitura = 1;
    ViraParaDireita(Esquerda, Direita);
  }
  else if (Meio < 500){
    //Caso o robô se perca
    //Motor_Esquerda.run(RELEASE);
    //Motor_Direita.run(RELEASE);
    //ProcuraLinha();
  }
  delay(10);
}
