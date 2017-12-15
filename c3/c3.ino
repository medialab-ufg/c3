// C3
// Projeto MediaLab - UFG
// Descricao: Este software implementa os controles e comportamentos
//    dos cubos C3
// Autores: Prof. Hugo Nascimento
//          Prof. Cleomar Rocha
//          Luma de Oliveira
//          Hugo Cabral Tannus
// Data: 20/out/2015

#include <Arduino.h>

//#define DEBUG_RF_REC
//#define DEBUG_RF_SND
//#define DEBUG_AC
#define DEBUG_SM
#define DEBUG_LED
#define DEBUG_BZ

#include "sm_declare.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>
#include <util/delay_basic.h>
/** LED Libraries **/
#include <SPI.h>
#include <Adafruit_WS2801.h>
/** C3 Libraries **/
#include "melodies.h"
#include "c3utils.c"
#include "pitches.h"
/*  Dados Necessarios para o Acelerometro/Giroscopio */
#include <Wire.h>  // Suporte ao Giroscopio MPU6050
 // Dados Necessarios para o Equipamento de RF
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

// Dados necessários para o time do receiver
unsigned int speed = 2000;
#define rxPin 6
#define txPin 10   // Any ways to avoid setting txPin?
#define pttPin 5  // Any ways to avoid setting pttPin?
#define pttInverse false
RH_ASK driver(speed, rxPin, txPin, pttPin, pttInverse);


#include "movimento.h"

// Dados necessários para a fita de LED
#define pinoDadosSDI     7
#define pinoRelogioCKI   8
#define quantidadeLED    60

Adafruit_WS2801 fitaLED = Adafruit_WS2801(quantidadeLED, pinoDadosSDI, pinoRelogioCKI);


/*
  Dados de Uso Geral
*/

int CuboID_outro1=(CuboID+1)%3; // Os IDs dos demais cubos sao automaticamente gerados
int CuboID_outro2=(CuboID+2)%3;
unsigned long c_CubosAtivosUltimaVez[4]={999999999,999999999,999999999,999999999};  // Guarda o valor de c da ultima vez que detectou os cubos

boolean RF_on = 0; // Indica se o RF est on/off

#define maxmatrizcores 24

uint8_t matrizcores[maxmatrizcores][3]={
  {255,0,0}, // 0 red
  {0,255,0}, // 1 lime
  {0,0,255}, // 2 blue
  {0,128,0}, // 3 green
  {0,254,255}, // 4 cyan
  {0,128,255}, // 5 white blue darks
  {0,128,128}, // 6 teal
  {0,255,128}, // 7
  {128,255,0}, // 8
  {255,255,0}, // 9 yellow
  {255,128,0}, // 10
  {255,165,0}, // 11 orange
  {255,215,0}, // 12 gold
  {255,192,203}, // 13 pink
  {250,128,114}, // 14 salmon
  {128,128,0},  // 15 olive // maroon
  {128,128,65}, // 16
  {128,65,128}, // 17
  {128,0,128}, // 18 purple
  {128,0,255}, // 19
  {254,0,255}, // 20 magenta
  {255,0,128}, // 21
  {128,128,128},  // 22 cyan
  {135,206,235} // 23 lightblue
};


int palheta_pos = -1;
uint32_t cores[4];  // Guarda as cores dos cubos
uint32_t ultima_cor, cor_apagada;

union {
 float flt;
 long lng;
} both;

/*
 Definition for controling state changes
*/


unsigned long c=0;                          // Contador de iteracao e usado para sincronizar os arduinos
//unsigned int cinter=300;                  // Intervalo de espera (em iteracoes) para enviar uma mensagem por RF. Pode ser mudado aleatoriamente
unsigned int c_notreceived=0;               // Contagem de iteracoes desde a ultima vez que recebeu mensagem de um dos cubos.
                                            // XX Possvivel melhoria aqui para checar a contagem de checagem de cada cubo
const unsigned int max_c_received = 3000;    // Indica a quantidade de iteracoes sem comunicacao a partir da qual o sistema assume
                                             // que um dos cubos esta ja fora de alcance

int estado[4]={-1,-1,-1,-1};                 // Estado do cubo atual
int return_State=0;                        // Estado de retorno, em caso de um GoSub
int pinLED = 13;

unsigned long tempomarcado;
uint32_t tempoparado;

#define SAVE_BATERY_STATE 10000

/*
 Sound
*/


volatile int pinSom=9,                   // Pino para conexao ao dispositivo de som
    bip=500;               // Nota do bip

volatile int contador_musica = 0;
volatile int finalizoumusica = 1;
volatile int max_contador_musica = 0;



/*
  Setup e Loop gerais
*/

void setup(){
  Serial.begin(9600); // Debugging only
  c=0;
  estado[CuboID]=0; /// XX mudar para =0
  setup_RF();
  //setup_timer();
  //InitBuzzer();
  setup_Acl();
  setup_LED();
  pinMode(pinSom,OUTPUT);
  pinMode(pinLED,OUTPUT);  // Pino de som
  digitalWrite(pinSom,LOW);
  digitalWrite(pinLED,LOW);
  tempoparado = millis();
}


void loop(){
  c++;
  loop_RF();
  if (c%4==0) loop_Acl();
  if (c%4==0) loop_StateMachine();
  delay(1);
}


/*
   Codigo do Sender e Receiver de RF
*/

void setup_RF()
{
    if (!driver.init())
       Serial.println("init failed");
    pinMode(6,INPUT); // Ensure high impedance at D9
    //pinMode(9,INPUT); // Ensure high impedance at D9
    pinMode(10,INPUT); // Ensure high impedance at D10
    setRFon();
}

void setup_timer (){
 // initialize Timer1
    finalizoumusica=1;
    cli();         // disable global interrupts
    TCCR1A = 0;    // set entire TCCR1A register to 0
    TCCR1B = 0;    // set entire TCCR1B register to 0
 // enable Timer1 overflow interrupt:
    TIMSK1 |= (1 << TOIE1); //Atmega8 has no TIMSK1 but a TIMSK register
// Set CS10 bit so timer runs at clock speed: (no prescaling)
    TCCR1B |= (1 << CS10) ; // Sets bit CS10 in TCCR1B
    sei();
}

uint16_t InitBuzzer( void ) {
    cli();
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) ; // phase and frequency correct mode. NON-inverted mode
    //TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1A0) | _BV(COM1B0) ;
    //phase/frequency correct mode. SELECT THIS FOR INVERTED OUTPUTS.
    //TCCR1B = _BV(WGM13) | _BV(CS11);
    //Select mode 8 and select divide by 8 on main clock.
    TCCR1B = _BV(WGM13) | _BV(CS11);
    sei();
}


/*ISR(TIMER1_OVF_vect)
{
   cli();
   if (!finalizoumusica) {
          tone(pinSom,500);
        int tempo, tam=(sizeof(melody)/sizeof(melody[0]));
        for (int i = 0; i < tam; i++) {
          //if ((melody[i][0]!=0)&&(melody[i][1]==2)) preencheCor(cores[CuboID]);
          //else preencheCor(cores[CuboID]);
          tone(pinSom, melody[i][0],tempo=1000/(melody[i][1]));
          delay(tempo*1.30);
          noTone(8);
          //preencheCor(cor_apagada);
        }
        finalizoumusica = 1;
   }
   //preencheCor(cor_apagada);
   sei();
// or use: PORTB ^= _BV(PB5);// PB5 =pin 19 is digitalpin 13
}*/

void loop_RF()
{
    if (RF_on == 0) return ;

    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    //Serial.println("Teste de recepcao");

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
       #ifdef DEBUG_RF_REC
         Serial.println("Recebeu");
       #endif
       int cubo=((int)buf[0]);  // Obtem ID do cubo que enviou a mensagem
       if ((cubo>=0)&&(cubo<3)) {
         face[cubo]=((int)buf[1]);  // Obtem face do cubo que enviou a mensagem
         unsigned long valor=((unsigned long)buf[2]<<24)+((unsigned long)buf[3]<<16)+((unsigned long)buf[4]<<8)+((unsigned long)buf[5]);
         cores[cubo]=((unsigned long)buf[6]<<24)+((unsigned long)buf[7]<<16)+((unsigned long)buf[8]<<8)+((unsigned long)buf[9]);
         estado[cubo]=buf[10];
         #ifdef DEBUG_RF_REC
           Serial.print("\t\t\tCubo= "); Serial.println(cubo);
           Serial.print("\t\t\tFace= "); Serial.println(face[cubo]);
           Serial.print("\t\t\tC= "); Serial.println(valor);
           Serial.print("\t\t\tCor= "); Serial.println(cores[cubo]);
           Serial.println(c);
         #endif
         c=(c+valor)/2;
         #ifdef DEBUG_RF_REC
           Serial.println(c);
         #endif
         // Atualizar aqui a contagem da ultima vez que o cubo enviou mensagem
         c_CubosAtivosUltimaVez[cubo]=millis();
         //c_notreceived=0;
       }
    } //else
    {
      /* c_notreceived++;
      if (c_notreceived>(max_c_received)) {
        cinter=300+random(1,10); // XXXX possivelmente reduzir o valor maximo de cinter
        c_notreceived=0;
      }*/
     if ((millis()/200)%3==CuboID) {
       //if (c_notreceived<10)
       {  // XXXX melhorar aqui enviando mais vezes 0 <= c % inter <= 10
         char msg[12];        // Monta mensagem para enviar
         msg[0]= CuboID; // Comeca com o ID do cubo: A=0, B=1 ou C=2
         msg[1]= face[CuboID]; // Adiciona a face do cubo atual
         msg[2]= (c&0xFF000000) >> 24; // Adiciona o contador c do cubo atual
         msg[3]= (c&0x00FF0000) >> 16;
         msg[4]= (c&0x0000FF00) >> 8;
         msg[5]= c&0x000000FF;
         msg[6]= (cores[CuboID]&0xFF000000) >> 24; // Adiciona a cor do cubo atual
         msg[7]= (cores[CuboID]&0x00FF0000) >> 16;
         msg[8]= (cores[CuboID]&0x0000FF00) >> 8;
         msg[9]= cores[CuboID]&0x000000FF;
         msg[10]=estado[CuboID];
         msg[11]=0;
         //for (int i=0; i<3; i++)  {
          driver.send((uint8_t *)msg, 12);
          driver.waitPacketSent();
         //}
         c_notreceived++;
         #ifdef DEBUG_RF_SND
           Serial.print("Enviou  ");
           Serial.println(c);
         #endif
       }
    } else c_notreceived = 0;
   }
}

void setRFon() { RF_on=1; }

void setRFoff() { RF_on=0; }


/*
  Codigo da Fita de Led
*/

void setup_LED()
{
  setDefaultColor();
  cor_apagada=0;
  ultima_cor=cor_apagada;
  //inicializando a biblioteca para comunicação com a Fita de LED
  fitaLED.begin();
  //atualiza a cor exibida na Fita de LED.
  fitaLED.show();
}

void preencheCor(uint32_t cor)
{
  int i;    //criando um contador.

 if (cor==ultima_cor) return; else ultima_cor=cor;

 fitaLED.setPixelColor(0, cor);
 fitaLED.show();
 //Serial.println("AQUI2");

 /*for (i=0; i < fitaLED.numPixels(); i++)
  {
      fitaLED.setPixelColor(i, cor);

  }
  fitaLED.show(); */
}

void setDefaultColor() {
  cores[CuboID]=Color(matrizcores[CuboID][0], matrizcores[CuboID][1], matrizcores[CuboID][2]);
  cores[CuboID_outro1]=Color(matrizcores[CuboID_outro1][0], matrizcores[CuboID_outro1][1], matrizcores[CuboID_outro1][2]);
  cores[CuboID_outro2]=Color(matrizcores[CuboID_outro2][0], matrizcores[CuboID_outro2][1], matrizcores[CuboID_outro2][2]);
}

/* Controles nao-interruptiveis de luz e som */

// Configura aleatoriamente uma cor para o cubo
void configCorAleatoria(){
  palheta_pos = random(0,maxmatrizcores);
  cores[CuboID]=Color(matrizcores[palheta_pos][0], matrizcores[palheta_pos][1], matrizcores[palheta_pos][2]);

   // Incluir aqui um código para chamar a linha abaixo apenas se a fita de LED já estiver acesar
  preencheCor(cores[CuboID]);
}


// Configura uma cor da palheta para o cubo
void definirCorPalheta(int pos){  // pos deve ser um numero entre 0 e maxmatrizcores-1 da palheta de cores
  palheta_pos = pos;
  cores[CuboID]=Color(matrizcores[palheta_pos][0], matrizcores[palheta_pos][1], matrizcores[palheta_pos][2]);

  // Incluir aqui um código para chamar a linha abaixo apenas se a fita de LED já estiver acesar
  preencheCor(cores[CuboID]);
}


// Configura a cor do cubo como sendo a próxima na palheta de cores
void definirCorPalhetaProx(){  // pos deve ser um numero entre 0 e maxmatrizcores-1 da palheta de cores
  palheta_pos = (palheta_pos+1) % maxmatrizcores;
  cores[CuboID]=Color(matrizcores[palheta_pos][0], matrizcores[palheta_pos][1], matrizcores[palheta_pos][2]);

  // Incluir aqui um código para chamar a linha abaixo apenas se a fita de LED já estiver acesar
  preencheCor(cores[CuboID]);
}

void definirCorRGB(int R, int G, int B){  // pos deve ser um numero entre 0 e maxmatrizcores-1 da palheta de cores
  cores[CuboID]=Color(R, G, B);

  // Incluir aqui um código para chamar a linha abaixo apenas se a fita de LED já estiver acesar
  preencheCor(cores[CuboID]);
}


// Desliga luzes
void luzdesligada(){
  preencheCor(cor_apagada);
}

// Pisca luzes
void luzpiscando(int tempo){
  if (((millis()/tempo)%2)==1) preencheCor(cores[CuboID]);
  else preencheCor(cor_apagada);
}

// Liga luzes
void luzligada(){
  preencheCor(cores[CuboID]);
}


// Vericar se a cor de uma cubo é igual a cor informada
boolean corIgualA(int ID, uint32_t COR){
   return cores[ID] == COR;
}


// Vericar se a cor de uma cubo é igual a cor informada
boolean corIgualA(int ID, int R, int G, int B){
   return cores[ID] == Color(R,G,B);
}


// Produz um som no arduino
void somligado(int freq, int tempo){
  if (tempo ==0) tone(pinSom, freq);
  else {
    tone(pinSom, freq, tempo);
    delay(tempo);
    noTone(pinSom);
  }
}

// Desliga som do arduino
void somdesligado(){
  noTone(pinSom);
}

// Som intermitente lento
void somintermitente(int freq, int tempo){
  if (((millis()/tempo)%2)==1) tone(pinSom, freq);
  else noTone(pinSom);
}

//Beep
void beep(int freq){
  tone(pinSom, freq, 250);
  noTone(pinSom);
}


void iniciamusica() {
  contador_musica = 0;
  finalizoumusica = 0;
  max_contador_musica = (sizeof(melody)/sizeof(melody[0]));
}

void finalizamusica(){
  finalizoumusica = 1;
}

// Toca musica de acordo com o ID do arduino
void tocamusica(int ID){
  float tempo, nota;
  if ((contador_musica % 2) == 0) preencheCor(cores[CuboID]);
  else preencheCor(cor_apagada);

  both.lng  =        pgm_read_dword(&melody[contador_musica][0]);
  nota      = both.flt;
  both.lng  =        pgm_read_dword(&melody[contador_musica][1]);
  tempo     = both.flt;
  tempo     = 1000 / tempo;
  // Serial.print("nota = "); Serial.println(nota);
  // Serial.print("tempo = "); Serial.println(tempo);
  tone(pinSom, nota, tempo);
  delay(tempo*1.30);
  noTone(8);
  contador_musica++;
  if (contador_musica >= max_contador_musica) {
     finalizoumusica = 1;
     preencheCor(cor_apagada);
  }
}

/* subrotines for improving the state machine fucntionality */

// Set return state
void setReturnState(int state) {
   return_State=state;
}

// Jump to a state for waiting holding
void goToSaveBatteryState(int return_state) {
  return_State=return_state;
  estado[CuboID]=SAVE_BATERY_STATE;
}


/*
  Codigo da Maquina de estados
 */

void  loop_StateMachine() {
  int presente_cubo_outro1, presente_cubo_outro2,  // recebem valor 0 ou 1 caso o outro cubo esteja longo ou perto
      soma_cubos_presentes;
  unsigned long tempoatual = millis();

  // Determina se os outros dois cubos estao proximos
  presente_cubo_outro1=(tempoatual>c_CubosAtivosUltimaVez[CuboID_outro1])&&((tempoatual-c_CubosAtivosUltimaVez[CuboID_outro1])<(max_c_received));
  presente_cubo_outro2=(tempoatual>c_CubosAtivosUltimaVez[CuboID_outro2])&&((tempoatual-c_CubosAtivosUltimaVez[CuboID_outro2])<(max_c_received));
  soma_cubos_presentes=presente_cubo_outro1+presente_cubo_outro2;

  #ifdef DEBUG_SM
    Serial.print("Estado = "); Serial.print(estado[CuboID]); Serial.print(" Face="); Serial.print(face[CuboID]); Serial.print("  Tempo="); Serial.println(tempoatual - tempoparado);
    Serial.print("                                                     Segurando = "); if (segurando) Serial.print("SIM"); else Serial.print("NAO");
    Serial.print(" Balancando = "); if (balancando) Serial.println("SIM"); else Serial.println("NAO");
  #endif
  // Controle da maquina de estados
  switch (estado[CuboID]) {
#include "20171215-color-circle.h"


    // Code for saving batery
    case SAVE_BATERY_STATE: setRFoff();
                            luzdesligada();
                            estado[CuboID]=SAVE_BATERY_STATE+1;
                            break;
    case SAVE_BATERY_STATE+1: if (segurando) estado[CuboID]=SAVE_BATERY_STATE+2;
                              break;
    case SAVE_BATERY_STATE+2: if (segurando) {setRFon(); estado[CuboID]=return_State;}
                              break;

  }
}


/*

 case 0: estado[CuboID]=30;
           break;

           // Estado inicial, representando as configuracoes V**, >**, AXX, AXO e AOX
           if(segurando) tempoparado = millis();
           else if(tempoatual - tempoparado >= 3000) {
              returned_State=0; estado[CuboID] = 20;
             break;
           }
           if (face[CuboID]==6) {luzdesligada();setDefaultColor();} // Cubo com face coreta para baixo desliga as luzes e reseta para a cor default
           else if (face[CuboID]!=1) luzpiscando(500); // Cubo com faces laterais para cima fica com luzes piscando
           else {
             luzligada(); // Cubo com face correta para cima liga as luzes
             if (balancando) { // Se o usuario esta balancando o cubo, entao vai para o estado para trocar a cor aleatoriamente
               estado[CuboID]=6;
             }
           }

           ///if (soma_cubos_presentes==1) somintermitente(500, 250); // Apenas um dos outros dois cubos esta perto causa som intermitente
           //else if ((soma_cubos_presentes==2) &&
           //     ((face[CuboID]!=1)||(face[CuboID_outro1]!=1)||(face[CuboID_outro2]!=1))) somintermitente(500, 1000); // Os outros dois cubos estao pertos mas com faces erradas causa som intermitente rapido
           //else somdesligado(); // Os dois outros cubos estao longe implica em som desligado


           if ((face[CuboID]==1)&&(soma_cubos_presentes==2)&&
               (face[CuboID_outro1]==1)&&(face[CuboID_outro2]==1)) { // Todos os cubos estao na configuracao correta, entao deve-se mudar para o estado 1
               somdesligado();
               luzligada();
               tempomarcado=millis();
               estado[CuboID]=2;
            }

           break;

   case 1: // Espera que os demais cubos entrem no estado 01 em ate 5 segundos
           if (tempoatual < tempomarcado) tempomarcado=millis();
           else if ((tempoatual - tempomarcado) > 5000) estado[CuboID]=0;
           else if ((soma_cubos_presentes==2) && (estado[CuboID_outro1]>=1 || estado[CuboID_outro1]<=5) &&
              (estado[CuboID_outro2]>=1 && estado[CuboID_outro2]<=5)) {

                estado[CuboID]=2; // Muda par estado 2 se todos os demais cubos estao em estado 1 ou 2
           }
           break;

   case 2: iniciamusica();
           estado[CuboID]=3;
           break;
           // Nao e' necessario break

   case 3: tocamusica(CuboID);
           if (finalizoumusica) estado[CuboID]=4;
           break;

   case 4: // Estado esperando por configuracao XXX
           somdesligado();
           luzpiscando(100);
           if ((face[CuboID]==6)//&&(soma_cubos_presentes==0)//)
              estado[CuboID]=0;
           break;

  case 5: estado[CuboID]=0; break; // Nao faz anda

  // Muda a cor do cubo
  case 6: {
            beep(500);
            configCorAleatoria();
            tempomarcado=millis();
            estado[CuboID]=7;
          }
          break;

  case 7: if (!balancando) {
            estado[CuboID]=0;
          }
          break;

  // Faz com que os tres cubos troquem cores a cada 2 segundos
  case 10: if (presente_cubo_outro1 &&
             (estado[CuboID_outro1]>=10 && estado[CuboID_outro1]<=11)) {
             uint32_t cor = cores[CuboID];
             cores[CuboID] = cores[CuboID_outro1];
             cores[CuboID_outro1] = cores[CuboID_outro2];
             cores[CuboID_outro2] = cor;
             estado[CuboID]=11;
             luzligada();
           }
           break;
  case 11: if (presente_cubo_outro2 &&
             (estado[CuboID_outro2]>=11 && estado[CuboID_outro1]<=12))
           { tempomarcado=millis(); estado[CuboID]=12;}
           break;
   case 12: if (tempoatual < tempomarcado) tempomarcado=millis();
           else if ((tempoatual - tempomarcado) > 5000) estado[CuboID]=10;
           break;

   //estado de hibernacao - cubos desligam por ficar muito tempo parados
   case 20:
       somdesligado();
       luzdesligada();
       //SetRFoff();
       estado[CuboID] = 21;
       break;
   case 21:
       if(segurando) {
         //SetRFon();
         estado[CuboID] = returned_State;  // 0
       }
       break;

  // cubo muda de cor de acordo com a face
  case 30:
     tempomarcado=millis(); // guarda tempo atual
     estado[CuboID] = 31;
     break;
  case 31:
     int cor=-1;
     switch (face[CuboID]) {
       case 1: cor = 2; break;
       case 2: cor = 1; break;
       case 3: cor = 0; break;
       case 4: cor = 3; break;
       case 5: cor = 8; break;
       case 6: cor = 15; break;
     }

     if (cor>=0) {
       cores[CuboID]=Color(matrizcores[cor][0], matrizcores[cor][1], matrizcores[cor][2]);
       luzligada();
     }
     else {luzdesligada(); beep(500); }
     if ((tempoatual < tempomarcado)|| segurando)  tempomarcado=millis();
     else if ((tempoatual - tempomarcado) > 15000) {returned_State=30; estado[CuboID] = 20;}
     break;
  }

*/
