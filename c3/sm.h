/* Put the you state machine code here. it must contain one or more case <i> clauses of a 
switch command. The expect value of <i> for the first case clause is i=0. The last is i=9999.
The follow commands and functions are allowed:

  estado[CuboID]=<value>;  // where <value> is the number of the next state for jumping to 
  goToSaveBateryState(int return_state); // Jumps to a code for saving battery. Lights will be switched off as well
                                         // as the radio frequency. The return_state parameter informs to what state
                                         // the system should go back when the user holds the cube. 
                                         // This command should be followed by a break!


  cores[CuboID]=<color>;  // This changes the default internal color of the cube to <color>. Example:
                          //  <color>=Color(128, 255, 12); The light of the cube will not be changes until they are
                          // turned on again
  
  setDefaultColor();      // This function sets the internal light color to its default, according to the cube ID. 
                          // This only has effect when the light of the cube is turned on again  

  
  definirCorPalheta(<pos>);  // Change the light of the cube to the color in the position <pos> of a color vector. 
                             // The light is automatically turned on 
  definirCorPalhetaProx();  // Change the light of the cube to the next color of a preset position of a color vector. 
                            // The light is automatically turned on
  configCorAleatoria();    // Change the light of the cube to the color in a random position of a color vector. 
                           // The light is automatically turned on
  definirCorRGB(<R>, <G>, <B>); // Change the light of the cube to a especific RGB color. The light is automatically turned on
    
  luzligada();             // Switch on the lights using the current internal light color
  luzpiscando(<delay>);    // Switches on/off the lights every <delay> milliseconds
  luzdesligada();          // Switch off the lights 

  corIgualA(<ID>, uint32_t <COR>)               // returns true if the color of cube <ID> is equal to <COR>  
  corIgualA(<ID>, <R>, <G>, <B>)    // returns true if the color of cube <ID> is equal to Color(<R>,<G>,<B>)  
  
  
  somligado(<freq>, <delay>);       // produces a beep at frequency <freq> for <delay> milliseconds
  somintermitente(<freq>, <delay>); // produces a beep at frequency <freq> for <delay> milliseconds, every <delay> milliseconds
  somdesligado();          // switch off the sound
  beep(<freq>);            // Just produces a beep at frequency <beep> for 250 milliseconds

  tempomarcado=millis();   // holds the current time
  
  setRFon();               // sets the radio fequency equipment on
  setRFoff();              // sets the radio fequency equipment off


Variables and data structures:

  segurando   --  boolean variable that indicates whether the cubes is been held  
  balancando  --  boolean variable that indicates whether the cubes is been shaken
  presente_cubo_outro1  --  boolean variable that indicates whether the next cube is close or not  
  presente_cubo_outro2  --  boolean variable that indicates whether the second next cube is close or not
  soma_cubos_presentes  --  the number of cubes close to the current one 
      
  matrizcores[<cnumber>][<p>]  -- contains the R, G or B value of a vector of RGB colors. 
                                <cnumber> goes from 0 to maxmatrizcores-1 and <p> = 0(R), 1(G) or 2(B)
                         
  estado[<ID>]  -- holds the last registered state of cube <ID>    
  face[<ID>]  -- holds the last registered face of cube <ID>     
  cores[<ID>] -- contains the last registered color of cube <ID>   
  tempoatual -- contains the current time in milliseconds

  finalizoumusica -- indicates whether a song that was being played finished.
  
where <ID> = CuboID, CuboID_outro1 or CuboID_outro2


Note: if you need to create a new temporary (local) variable inside the case clause, then put the case commands
inside a block. Eg.: case <i>: { ...block of commands...}. You can also declare globlal variables and other
elements in file sm_declare.h
*/

/*
  // Example 1: cubo muda de cor de acordo com a face    
  case 0: 
     tempomarcado=millis(); // guarda tempo atual
     estado[CuboID] = 1;
  case 1: {  
       int cor_pos=-1;
       switch (face[CuboID]) {
         case 1: cor_pos = 3; break; // =0 3
         case 2: cor_pos = 5; break; // =1 5
         case 3: cor_pos = 6; break; // =2 6 
         case 4: cor_pos = 9; break; // =4 9 10
         case 5: cor_pos = 11; break;// =14 11 13 
         case 6: cor_pos = 20; break; // =18 20 
        } 
        if (cor_pos>=0) definirCorPalheta(cor_pos); //else luzdesligada();
     }  
     if (segurando || tempoatual < tempomarcado) tempomarcado=millis();
     else if ((tempoatual - tempomarcado) > 15000)  {
            somligado(500, 250);
            goToSaveBatteryState(0);
     }
     break;

*/

/*
 // Example 2: cubo muda de cor automaticamente, em sequencia  (consome toda bateria em +- 30min) 
 case 0:
     definirCorPalhetaProx();
     //if (palheta_pos==maxmatrizcores) estado[CuboID] = 2;
     break;
  case 2: 
     luzdesligada(); 
     estado[CuboID] = 3;
  case 3:
     if (segurando) estado[CuboID]=0;
     break;

*/

/*
  Example 3: em desenvolvimento....
  case 0: 
     tempomarcado=millis(); // guarda tempo atual
     estado[CuboID] = 1;
  case 1: {
     //Serial.print("Face = ");
     //Serial.println(face[CuboID]);
     if (face[CuboID]>=0)  
#if CuboID==1// Cubo 0
        definirCorRGB((52*face[CuboID])%256, (104*(face[CuboID]+face[0]))%256, (52*face[0])%256); 
#endif
#if CuboID==2// Cubo 0
        definirCorRGB((52*face[CuboID])%256, (104*(face[CuboID]+face[1]))%256, (52*face[1])%256); 
#endif
        else luzdesligada();
     }  
     if (segurando) tempomarcado=millis();
     else if ((tempoatual - tempomarcado) > 51000) estado[CuboID] = 2; 
     break;
  case 2: 
     luzdesligada(); 
     somligado(500, 250);
     estado[CuboID] = 3;
  case 3:
     if (segurando) estado[CuboID]=0;
     break;
     
*/     



  // Example 4: cubo acende ao ser segurado e  muda de cor e faz beep quando sacudido    
  case 0:   
     luzdesligada();
     somdesligado();
     tempomarcado=millis(); // guarda tempo atual
     estado[CuboID] = 1;
  case 1: 
     if (balancando) estado[CuboID] = 2; 
     else if (segurando) estado[CuboID] = 4; 
     else if (tempoatual < tempomarcado) tempomarcado=millis();
     else if ((tempoatual - tempomarcado) > 15000)  {
        somligado(500, 250);
        goToSaveBatteryState(0);
     }
     break;
     
  case 2: // balancando cubo
      somligado(700, 250);
      definirCorPalhetaProx();
      luzligada();
      estado[CuboID] = 3; 
      break;
      
  case 3: // grita
      somintermitente(700, 250);
      luzpiscando(250);
      if (!balancando) estado[CuboID] = 0;
      break;

  case 4: //
      luzligada();
      estado[CuboID] = 5; 
      break;
   case 5: //
      if (balancando) estado[CuboID] = 2;
      if (!segurando) estado[CuboID] = 0;
      break;
