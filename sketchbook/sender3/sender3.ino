// Ventos Uivantes -- Estacao Meteorologica
// Projeto MediaLab - UFG
// Descricao:
// Este programa recebe, por meio de radio frequencia,
// dados vindo de uma estacao meteorologica, processa-os 
// e controla uma sistema luminoso. 
// Configuracao das portas:
//    Digital  2 -- circuito de botao acionado pelo anemometro 
//    Digital 10 -- Envio de sinal por Radio Frequencia
//    Analogica A0 -- Leitura do potenciometro controlado pelo 
//                    medidor de direcao do vento
//
// Autores: Profa. Laurita Salles (UFRN)
//          Prof. Hugo Nascimento (UFG)
//            ...
// Data: maio de 2015

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
//#include <inttypes.h>

uint16_t speed = 2000;
uint8_t rxPin = 6; // Any ways to avoid setting rxPin?
uint8_t txPin = 10;
uint8_t pttPin = 7; // Any ways to avoid setting pttPin?
boolean pttInverse = false;
RH_ASK driver(speed, rxPin, txPin, pttPin,pttInverse);

long int c=0;  // contador de iteracao - incrementado toda vez que a funcao Loop eh executada
long int cl=0;
long int high=-1;

float dir=0;

void setup()
{
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    pinMode(13,OUTPUT); // saida de luz a cada transmissao
   // Obtencao dos dados do vento
   pinMode(2, INPUT);
}

void loop()
{ 
   int estado = digitalRead(2);  // Ler sinal do medido de velocidade do vento (HIGH = passou pelo ponto de referncia)
   int v = analogRead(0)/10;     // Ler resistencia do medidor de direcao do vento
   dir = dir*0.99+v*0.01;        // Computa media dos valores da resistencia, para evitar grande oscilacao 
   
   c++; // contador de iteracao
   
   // processa dado do anemometro
   if (estado == HIGH) {
      if ((high==-1)||(high==1)) { // primeira configuracao da contagem
        high=1; cl=0;
      } else
      if (high==2) { // finalizou uma contagem. Pode agora processa-la e envia-la por radio frequencia
        String str;
        char msg1[10], msg[20]="V";
        // Monta mensagem para enviar com o tempo de giro
        str=String(cl);
        str.toCharArray(msg1, 10);
        strcat(msg, msg1);
        // Envia mensagem
        //Serial.println(msg);
        driver.send((uint8_t *)msg, strlen(msg));
        driver.waitPacketSent();
        digitalWrite(13,HIGH);
        delay(200); 
        digitalWrite(13,LOW);
        delay(200);
        high=-1;
      }
   } else {
     if (high==1) { cl++; high=2;}
     else if (high==2) {cl++;}
   }    
   
   // processo dado do controle de direcao
   if ((c % 2000) == 0) { // envia mensagem sobre a direcao do tempo a cada 5000 segundos
        String str;
        char msg1[10], msg[20]="D";
        // Monta mensagem para enviar com o tempo de giro
        str=String((int) dir);
        str.toCharArray(msg1, 10);
        strcat(msg, msg1);
        // Envia mensagem
        Serial.println(msg);
        driver.send((uint8_t *)msg, strlen(msg));
        driver.waitPacketSent();
        digitalWrite(13,HIGH);
        delay(200); 
        digitalWrite(13,LOW);
        delay(200); 
   }  
   delay(1);
}

