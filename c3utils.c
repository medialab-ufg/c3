#include <math.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include "irc_notes.h"
#include "c3utils.h"

/*valores para calibrar a fita de LED*/
#define RED    255
#define GREEN  128 
#define BLUE   180
  

#define AMP_TOP 65536

//char _NOTE[][3] = {"C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B"};

double log_base(double n, double base) {
  return log(n) / log(base);
}

uint32_t note2color(int16_t pinch, uint8_t ID) {
  int32_t _AUX = CLK1*1000000/(2*PRS1); 
  if(!pinch) return 0;

   float a, calc, o, n;
   uint32_t color = 0;
   uint8_t note, octave;
   int8_t x;
   
   a = pinch*CFRQ / _AUX;
   calc = log_base( a, _CONST );
   x = floor(-calc);
   
   octave = x/12;
   note = x%12;
   if(octave%2)
       note = 11 - note;
   
   o = (float)(octave*5 + 0)/100;
   n = (float)(note*8 + 10)/100;

   switch(ID) {
      case 0:
        return Cor(1.0, o, n);
      case 1:
        return Cor(n, 1.0, o);
      case 2:
        return Cor(o, n, 1.0);
      default:
        return color;
   }
}

uint16_t increase_vol(uint16_t amp, uint16_t vol, uint16_t v_max) {
  if (amp + vol < v_max) 
    return amp + vol;
  else
    return v_max;     
}

uint16_t decrease_vol(uint16_t amp, uint16_t vol) {
  if (amp - vol > 0) 
    return amp - vol;
  else
    return 0;     
}

void play_single_note(uint16_t pinch, uint16_t duration, uint16_t amplitude) {
  uint16_t vol;
  //uint16_t freq;
  uint32_t atck, decay, sustain, silent, _release, mark, tmp;
  
  ICR1 = pinch;
  
  tmp = duration;

  mark = millis();
  //Serial.print("Tempo "); Serial.println(mark); 
  atck = (mark + tmp/20);
  decay = (atck + tmp/20);
  sustain = (uint32_t)(decay + (uint32_t)tmp*0.7);
  _release = (sustain + tmp/10);
  silent = (_release + tmp/10);
  
  if(pinch == _FER) vol = 0;
  else vol = amplitude/10;
  
  while((tmp = millis()) < atck) {
    OCR1A = increase_vol(OCR1A, vol, amplitude);
  }
    //Serial.print("Tempo(atck) "); Serial.println(tmp); 
  vol = amplitude/120;
  
  while((tmp = millis()) < decay) {
    OCR1A = decrease_vol(OCR1A, vol);
  }
  //Serial.print("Tempo(decay) "); Serial.println(tmp); 
  vol = 0;
  
  while((tmp = millis()) < sustain) {
    OCR1A = decrease_vol(OCR1A, vol);
     //Serial.print("Tempo(sustain) "); Serial.println(tmp); 
  }
  //Serial.print("Tempo(sustain) "); Serial.println(tmp); 
  vol = amplitude/100;
  
  while((tmp = millis()) < _release) {
    if( OCR1A > ICR1 / 10 )
      decrease_vol(OCR1A, vol);
  } 
  //Serial.print("Tempo(release) "); Serial.println(tmp); 
  ICR1 = _FER;
  OCR1A  = 0;
  
  while((tmp = millis()) < silent); 
}

uint32_t Cor(float r, float g, float b) {
  uint32_t c;
  uint16_t x;
  c = ceil(r * GREEN);
  //Serial.println(c);
  c <<= 8;

  x = ceil(g * RED);
  //Serial.println(x);
  c |= x;
  c <<= 8;

  x = ceil(b * BLUE);
  //Serial.println(x);
  c |= x;

  return c;
}

uint32_t Color(uint8_t r, uint8_t g, uint8_t b)
{
  uint32_t c;
  c = r;      //atribuindo a variável "c" a cor do canal "R"
  c <<= 8;    //realizando um deslocamento de bits à esquerda
  
  c |= g;     //atribuindo a variável "c" a cor do canal "G"
              //através de uma operação lógica OU
  c <<= 8;    //realizando um deslocamento de bits à esquerda
  
  c |= b;     //atribuindo a variável "c" a cor do canal "B"
              //através de uma operação lógica OU
              
  return c;   //retorna o valor resultante da cor para a função preencherCor()
}
