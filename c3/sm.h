/* Put the you state machine code here. it must contain one or more case <i> clauses of a 
switch command. The expect value of <i> for the first case clause is i=0. The follow commands 
and functions are allowed:

  estado[CuboID]=<value>;  // where <value> is the number of the next state for jumping to 


  cores[CuboID]=<color>;  // This changes the default internal color of the cube to <color>. Example:
                          //  <color>=Color(128, 255, 12); The light of the cube will not be changes until they are
                          // turned on again
  
  setDefaultColor();      // This function sets the internal light color to its default, according to the cube ID. 
                             This only has effect when the light of the cube is turned on again  

  
  definirCorPalheta(<pos>);  // Change the light of the cube to the color in the position <pos> of a color vector. 
                               The light is automatically turned on 
  definirCorPalhetaProx();  // Change the light of the cube to the next color of a preset position of a color vector. 
                               The light is automatically turned on
  configCorAleatoria();    // Change the light of the cube to the color in a random position of a color vector. 
                               The light is automatically turned on
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
  
  SetRFon();               // sets the radio fequency equipment on
  SetRFoof();              // sets the radio fequency equipment off


Variables and data structures:

  segurando   --  boolean variable that indicates whether the cubes is been held  
  balancando  --  boolean variable that indicates whether the cubes is been shaken
  presente_cubo_outro1  --  boolean variable that indicates whether the next cube is close or not  
  presente_cubo_outro2  --  boolean variable that indicates whether the second next cube is close or not
  soma_cubos_presentes  --  the number of cubes close to the current one 
      
  matrizcores[<cnumber>][<p>]  -- contains the R, G or B value of a vector of RGB colors. 
                                <cnumber> goes from 0 to 17 and <p>=0(R), 1(G) or 2(B)
                         
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

/* Example 1: cubo muda de cor de acordo com a face  */
  case 0: 
     tempomarcado=millis(); // guarda tempo atual
     estado[CuboID] = 1;
  case 1: {  
       int cor_pos=-1;
       switch (face[CuboID]) {
         case 1: cor_pos = 2; break;
         case 2: cor_pos = 1; break;
         case 3: cor_pos = 0; break;
         case 4: cor_pos = 3; break;
         case 5: cor_pos = 8; break;
         case 6: cor_pos = 15; break;
        } 
        if (cor_pos>=0) definirCorPalheta(cor_pos); else luzdesligada();
     }  
     if (segurando) tempomarcado=millis();
     else if ((tempoatual - tempomarcado) > 5000) estado[CuboID] = 2; 
     break;
  case 2: 
     luzdesligada(); 
     somligado(500, 250);
     estado[CuboID] = 3;
  case 3:
     if (segurando) estado[CuboID]=0;
     break;
     
     
     


