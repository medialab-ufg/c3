// Ventos Uivantes -- Principal
// Projeto MediaLab - UFG
// Descricao:
// Este programa recebe, por meio de radio frequencia,
// dados vindo de uma estacao meteorologica, processa-os 
// e controla uma sistema luminoso. No
// Autores: Profa. Laurita Salles (UFRN)
//          Prof. Hugo Nascimento (UFG)
//            ...
// Data: maio de 2015

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

unsigned int speed = 2000;
uint8_t rxPin = 10;
uint8_t txPin = 6;   // Any ways to avoid setting txPin?
uint8_t pttPin = 7;  // Any ways to avoid setting pttPin?
bool pttInverse = false;
RH_ASK driver(speed, rxPin, txPin, pttPin,pttInverse);

void setup()
{
    Serial.begin(9600); // Debugging only
    if (!driver.init())
         Serial.println("init failed");;
//    pinMode(8,OUTPUT);
//    digitalWrite(8,LOW);
    pinMode(11,OUTPUT); // Pino do som
    digitalWrite(11,LOW);
    pinMode(13,OUTPUT);; // Pino da luz
    digitalWrite(13,LOW);
    pinMode(9,INPUT); // Ensure high impedance at D9
    pinMode(10,INPUT); // Ensure high impedance at D10

}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
       char op=buf[0];
       
       char t[20];
       long int valor;
       // Message with a good checksum received, dump it.
       strncpy(t, (char *) buf+1, buflen-1);
       t[buflen-1]=char(0);
       valor=strtol(t,NULL,10);
       if (op=='V') {
          Serial.print("Tempo de giro: "); Serial.println(valor);
          //tone(11, 2000-tempo, 500);
       }
       if (op == 'D') {
          Serial.print("Direcao : "); Serial.println(valor);
       }  
       //Serial.println((char *)buf);
       //driver.printBuffer("Got:", buf, buflen);
       digitalWrite(13,HIGH);
       delay(500);
       digitalWrite(13,LOW);
       delay(500);
    }
}



