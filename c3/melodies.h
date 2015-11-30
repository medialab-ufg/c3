#ifndef MELODIES_H
#define MELODIES_H

#include <avr/pgmspace.h>
#include <inttypes.h>
#include "irc_notes.h"
#include "pitches.h"

static char const _NOTE[][3] PROGMEM = {"C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B"};


// notes in the melody: http://forum.cifraclub.com.br/forum/1/104542/
// Greensleeves to a ground : http://www.cifraclub.com.br/rei-henrique-viii/greensleeves/
//                            http://www.ciframelodica.com.br/musicas/361
//int melody[][2] = {{NOTE_C4, 4}, {NOTE_G3, 8}, {NOTE_G3, 8}, {NOTE_A3, 4}, 
//  {NOTE_G3, 4} , {0,4} , {NOTE_B3, 4}, {NOTE_C4, 4}};
static float const melody[][2] PROGMEM = {
  {NOTE_A6, 4}, {NOTE_C6, 2}, 
  {NOTE_D6, 4}, {NOTE_E6, 2.66666}, {NOTE_FS6, 8}, {NOTE_E6, 4}, {NOTE_D6, 2}, 
  {NOTE_B6, 4}, {NOTE_G6, 2.66666}, {NOTE_A6, 8}, {NOTE_B6, 4}, {NOTE_C6, 2},
  {NOTE_A6, 4}, {NOTE_A6, 2.66666}, {NOTE_GS6, 8}, {NOTE_A6, 4}, {NOTE_B6, 2},
  {NOTE_GS6, 4}, {NOTE_E6, 1.33333}, 
  {0,1},
  {NOTE_A6, 4}, {NOTE_C6, 2}, 
  {NOTE_D6, 4}, {NOTE_E6, 2.66666}, {NOTE_FS6, 8}, {NOTE_E6, 4}, {NOTE_D6, 2}, 
  {NOTE_B6, 4}, {NOTE_G6, 2.66666}, {NOTE_A6, 8}, {NOTE_B6, 4}, {NOTE_C6, 2.66666}, {NOTE_B6, 8}, {NOTE_A6, 4}, {NOTE_GS6, 2.66666}, {NOTE_FS6, 8}, {NOTE_GS6, 4},{NOTE_A6, 1.33333},
  {0,1},
  {NOTE_G6, 1.33333}, {NOTE_G6, 2.66666}, {NOTE_FS6, 8}, {NOTE_E6, 4}, {NOTE_D6, 2}, 
  {NOTE_B6, 4}, {NOTE_G6, 2.66666}, {NOTE_A6, 8}, {NOTE_B6, 4}, {NOTE_C6, 2},
  {NOTE_A6, 4}, {NOTE_A6, 2.66666}, {NOTE_GS6, 8}, {NOTE_A6, 4}, {NOTE_B6, 2},
  {NOTE_GS6, 4}, {NOTE_E6, 1.33333}, 
  {0,1},
  {NOTE_G6, 1.33333}, {NOTE_G6, 2.66666}, {NOTE_FS6, 8}, {NOTE_E6, 4}, {NOTE_D6, 2}, 
  {NOTE_B6, 4}, {NOTE_G6, 2.66666}, {NOTE_A6, 8}, {NOTE_B6, 4}, {NOTE_C6, 4}, {NOTE_B6, 4}, {NOTE_A6, 4}, {NOTE_GS6, 2.66666}, {NOTE_FS6, 8}, {NOTE_GS6, 4},{NOTE_A6, 1.33333},
  {0,1}
};

static uint16_t const greensleeves[][2] PROGMEM= {
  {_A4, 2}, {_C5, 4}, 
  {_D5, 2}, {_E5, 3}, {_Gb5, 1}, {_E5, 2}, {_D5, 4}, 
  {_B4, 2}, {_G4, 3}, {_A4, 1}, {_B4, 2}, {_C5, 4},
  {_A4, 2}, {_A4, 3}, {_Ab4, 1}, {_A4, 2}, {_B4, 4},
  {_Ab4, 2}, {_E4, 6}, 
  {_FER,8},
  {_A4, 2}, {_C5, 4}, 
  {_D5, 2}, {_E5, 3}, {_Gb5, 1}, {_E5, 2}, {_D5, 4}, 
  {_B4, 2}, {_G4, 3}, {_A4, 1}, {_B4, 2}, {_C5, 3}, {_B4, 1}, {_A4, 2}, {_Ab4, 3}, {_Gb4, 1}, {_Ab4, 2},{_A4, 6},
  {_FER,8},
  {_G5, 6}, {_G5, 3}, {_Gb5, 1}, {_E5, 2}, {_D5, 4}, 
  {_B4, 2}, {_G4, 3}, {_A4, 1}, {_B4, 2}, {_C5, 4},
  {_A4, 2}, {_A4, 3}, {_Ab4, 1}, {_A4, 2}, {_B4, 4},
  {_Ab4, 2}, {_E4, 6}, 
  {_FER,8},
  {_G5, 6}, {_G5, 3}, {_Gb5, 1}, {_E5, 2}, {_D5, 4}, 
  {_B4, 2}, {_G4, 3}, {_A4, 1}, {_B4, 2}, {_C5, 2}, {_B4, 2}, {_A4, 2}, {_Ab4, 3},
  {_Gb4, 1}, {_Ab4, 2},{_A4, 6},
  {_FER,8}
};

static uint16_t const lepolepo[][2] PROGMEM = { 
//	
	{_C5,1}, {_FER,1}, {_C5,1}, {_FER,1}, {_C5,1}, {_FER,1}, {_C5,1}, {_FER,1}, {_B4,1},
//	
	{_FER,1}, {_B4,1}, {_FER,1}, {_B4,1}, {_A4,1}, {_B4,1}, {_A4,1}, {_C5,2},
//	
	{_A4,2}, {_FER,2}, {_F5,1}, {_F5,1}, {_G5,1}, {_E5,1}, {_D5,1}, {_C5,1}, {_FER,3}
};

// http://www.docstoc.com/docs/110827106/Ai-Se-Eu-Te-Pego-1
static uint16_t const aiseeutepego[][2] PROGMEM = {
//	Nos		sa			Nos		sa				As	sim		vo		ce	
	{_B4,2}, {_B4,2}, {_FER,4}, {_Bb4,2}, {_Bb4,2}, {_FER,2}, {_Ab4,2}, {_B4,2}, {_Ab4,2}, {_B4,2},
//	me		ma		ta			Ai			   se-eu	  te		pe		go
	{_Ab4,1}, {_B4,2}, {_Ab4,4}, {_FER,1}, {_B4,2}, {_FER,2}, {_B4,2}, {_B4,2},  {_Bb4,2}, {_Bb4,2},
//	Ai		ai	   		 se-eu	  te		pe		go		
	{_Bb4,2}, {_FER,2},  {_B4,2},  {_FER,2},  {_B4,2}, {_Ab4,2}, {_B4,2}, {_Ab4,2}, {_FER,2},
	
//	De		li	   cia			De		li	   cia			As	
	{_B4,2}, {_B4,2}, {_B4,2}, {_FER,2}, {_B4,2}, {_Bb4,2}, {_Bb4,2}, {_FER,2}, {_Ab4,2}, {_B4,2}, {_Ab4,2}, {_B4,2},
//	sim		vo		ce	me		ma		ta			Ai				se-eu
	{_Ab4,1}, {_B4,2}, {_Ab4,4}, {_FER,1}, {_B4,2}, {_FER,2}, {_B4,2}, {_B4,2},  {_Bb4,2}, {_Bb4,2},
//	te		pe		go 		Ai	ai	   			se-eu   te	pe		go		
	{_Bb4,2}, {_FER,2},  {_B4,2},  {_FER,2},  {_B4,2}, {_Ab4,2}, {_B4,2}, {_Ab4,2}, {_FER,4}

};


#endif
