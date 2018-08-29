/*
  // Example Teste: cubo acende ao ser solto e apaga ao ser segurado
  case 0:
     luzligada();
     if(segurando) estado[CuboID] = 1;
     break;

  case 1:
     luzdesligada();
     if(!segurando) estado[CuboID] = 0;
     break;
*/

/*
 * 
 * 
  switch(face[CuboID]){
    case 1: 
      definirCorPalheta(2);//Azul();
      luzligada();
      break;
    case 2:
      definirCorPalheta(9);//Amarelo();
      luzligada();
      break;
    case 3: 
      definirCorPalheta(0);//Vermelho();
      luzligada();
      break;
    case 4: 
      definirCorPalheta(3);//Verde();
      luzligada();
      break;
    case 5: 
      definirCorPalheta(11);//Laranja();
      luzligada();
      break;
    case 6: 
      definirCorPalheta(20);//Magenta();
      luzligada();
      break;
  }
  break;
*/

/*

//6 cores, 6 face, mesma cor para todos os cubos

case 0:

  switch(face[CuboID]){
    case 1: estado[CuboID] = 1; break;
    case 2: estado[CuboID] = 2; break;
    case 3: estado[CuboID] = 3; break;
    case 4: estado[CuboID] = 4; break;
    case 5: estado[CuboID] = 5; break;
    case 6: estado[CuboID] = 6; break;
  }
  break;

case 1: //AZUL
  definirCorPalheta(2);
  luzligada();
  estado[CuboID] = 0;
  break;
  
case 2: //AMARELO
  definirCorPalheta(9);
  luzligada();
  estado[CuboID] = 0;
  break;

case 3: //VERMELHO
  definirCorPalheta(0);
  luzligada();
  estado[CuboID] = 0;
  break;

case 4: //VERDE
  definirCorPalheta(3);
  luzligada();
  estado[CuboID] = 0;
  break;

case 5: //LARANJA
  definirCorPalheta(11);
  luzligada();
  estado[CuboID] = 0;
  break;

case 6: //MAGENTA
  definirCorPalheta(20);
  luzligada();
  estado[CuboID] = 0;
  break;
*/


/*
 * 
 * 12 Cores, 6 por cubo, cubos 1 e 2
case 0:

  switch(face[CuboID]){
    case 1:
      if(CuboID == 1) estado[CuboID] = 1; 
      else if(CuboID == 2) estado[CuboID] = 7; 
      break;
    case 2:
      if(CuboID == 1) estado[CuboID] = 2; 
      else if(CuboID == 2) estado[CuboID] = 8; 
      break;
    case 3:
      if(CuboID == 1) estado[CuboID] = 3; 
      else if(CuboID == 2) estado[CuboID] = 9; 
      break;
    case 4:
      if(CuboID == 1) estado[CuboID] = 4; 
      else if(CuboID == 2) estado[CuboID] = 10; 
      break;
    case 5:
      if(CuboID == 1) estado[CuboID] = 5; 
      else if(CuboID == 2) estado[CuboID] = 11; 
      break;
    case 6:  
      if(CuboID == 1) estado[CuboID] = 6;
      else if(CuboID == 2) estado[CuboID] = 12; 
      break;
  }
  break;

//CUBO1...
case 1: //AZUL
  definirCorPalheta(2);
  luzligada();
  estado[CuboID] = 0;
  break;
  
case 2: //AMARELO
  definirCorPalheta(9);
  luzligada();
  estado[CuboID] = 0;
  break;

case 3: //VERMELHO
  definirCorPalheta(0);
  luzligada();
  estado[CuboID] = 0;
  break;

case 4: //VERDE
  definirCorPalheta(3);
  luzligada();
  estado[CuboID] = 0;
  break;

case 5: //LARANJA
  definirCorPalheta(11);
  luzligada();
  estado[CuboID] = 0;
  break;

case 6: //MAGENTA
  definirCorPalheta(20);
  luzligada();
  estado[CuboID] = 0;
  break;
//...fim CUBO1

//CUBO2...
case 7: //Purple
  definirCorPalheta(18);
  luzligada();
  estado[CuboID] = 0;
  break;
case 8: //Cyan
  definirCorPalheta(4);
  luzligada();
  estado[CuboID] = 0;
  break;
case 9: //teal
  definirCorPalheta(6);
  luzligada();
  estado[CuboID] = 0;
  break;
case 10: //Pink
  definirCorPalheta(13);
  luzligada();
  estado[CuboID] = 0;
  break;
case 11: //Lightblue
  definirCorPalheta(23);
  luzligada();
  estado[CuboID] = 0;
  break;
case 12: //salmao
  definirCorPalheta(14);
  luzligada();
  estado[CuboID] = 0;
  break;
//...fim CUBO2

*/


/*
 * Cubo 0: principal, muda de acordo com as cores dos Cubos 1 e 2;
 * 
 * Exemplo 1: Se ambos possuem a mesma cor, o Cubo 0 tera' a cor dos 2 outros Cubos;
 * 
 * Exemplo 2: Se o Cubo 1 tiver a cor Vermelho e o cubo 2 tiver a cor Verde (por exemplo), o Cubo 0 tera a cor Amarelo
 * 
 */


case 0:
  //inicializa desligado
  luzdesligada();
  estado[CuboID] = 1;
  tempomarcado=millis();
  break;

case 1:
  //SaveBattery
  if (tempoatual < tempomarcado) tempomarcado=millis();
  else if ((tempoatual - tempomarcado) > 150000)  {
    somligado(500, 250);
    goToSaveBatteryState(0);
  }
 
  if(CuboID == 0){
    estado[CuboID] = 8;
  }
  
  else if(CuboID == 1 || CuboID == 2){
    if(segurando) luzpiscando(200);
    if(balancando) somligado(440.0, 500);
    if(!balancando) somdesligado();
    switch(face[CuboID]){
      case 1: estado[CuboID] = 2; break;
      case 2: estado[CuboID] = 3; break;
      case 3: estado[CuboID] = 4; break;
      case 4: estado[CuboID] = 5; break;
      case 5: estado[CuboID] = 6; break;
      case 6: estado[CuboID] = 7; break; 
    }
  }

  break;

case 2: //AZUL
  definirCorPalheta(2);
  luzligada();
  estado[CuboID] = 1;
  break;
  
case 3: //AMARELO
  definirCorPalheta(9);
  luzligada();
  estado[CuboID] = 1;
  break;

case 4: //VERMELHO
  definirCorPalheta(0);
  luzligada();
  estado[CuboID] = 1;
  break;

case 5: //VERDE
  definirCorPalheta(3);
  luzligada();
  estado[CuboID] = 1;
  break;

case 6: //LARANJA
  definirCorPalheta(11);
  luzligada();
  estado[CuboID] = 1;
  break;

case 7: //MAGENTA
  definirCorPalheta(20);
  luzligada();
  estado[CuboID] = 1;
  break;

case 8:
  //somligado(494.0, 500);
  if(face[CuboID_outro1] == face[CuboID_outro2]){ //Cubos de mesma cor
    if(face[CuboID_outro1] == 1) estado[CuboID] = 2;
    else if(face[CuboID_outro1] == 2) estado[CuboID] = 3;
    else if(face[CuboID_outro1] == 3) estado[CuboID] = 4;
    else if(face[CuboID_outro1] == 4) estado[CuboID] = 5;
    else if(face[CuboID_outro1] == 5) estado[CuboID] = 6;
    else if(face[CuboID_outro1] == 6) estado[CuboID] = 7;
  }

/*
 * azul + amarelo = verde
 * azul + vermelho = magenta
 * azul + verde = ciano
 * azul + laranja = amarelo-alaranjado (RGB: 237,118,14)
 * azul + magenta = purple 18
 * 
 * amarelo + vermelho = laranja
 * amarelo + verde = olive 15
 * amarelo + laranja = vermelho
 * amarelo + magenta = laranja
 * 
 * vermelho + verde = amarelo
 * vermelho + laranja = vermelho-alaranjado (RGB: 255, 69, 0)
 * vermelho + magenta = rosa 13
 * 
 * verde + laranja = citrino
 * verde + magenta = ardosia
 * 
 * laranja + magenta = vermelho
 * 
 */
  else if(face[CuboID_outro1] == 1 && face[CuboID_outro2] == 2 || face[CuboID_outro2] == 1 && face[CuboID_outro1] == 2) estado[CuboID] = 5; //azul + ararelo = verde ((CuboID + 1) % 3) e ((CuboID + 2) % 3) ou CuboID_outro1 e CuboID_outro2
  else if(face[CuboID_outro1] == 1 && face[CuboID_outro2] == 3 || face[CuboID_outro2] == 1 && face[CuboID_outro1] == 3) estado[CuboID] = 7; //azul + vermelho = magenta
  else if(face[CuboID_outro1] == 1 && face[CuboID_outro2] == 4 || face[CuboID_outro2] == 1 && face[CuboID_outro1] == 4) estado[CuboID] = 9; //azul + verde = ciano
  else if(face[CuboID_outro1] == 1 && face[CuboID_outro2] == 5 || face[CuboID_outro2] == 1 && face[CuboID_outro1] == 5) estado[CuboID] = 10; //azul + laranja = amarelo-alaranjado
  else if(face[CuboID_outro1] == 1 && face[CuboID_outro2] == 6 || face[CuboID_outro2] == 1 && face[CuboID_outro1] == 6) estado[CuboID] = 11; //azul + magenta = purple

  else if(face[CuboID_outro1] == 2 && face[CuboID_outro2] == 3 || face[CuboID_outro2] == 2 && face[CuboID_outro1] == 3) estado[CuboID] = 6; //amarelo + vermelho = laranja
  else if(face[CuboID_outro1] == 2 && face[CuboID_outro2] == 4 || face[CuboID_outro2] == 2 && face[CuboID_outro1] == 4) estado[CuboID] = 12; //amarelo + verde = olive
  else if(face[CuboID_outro1] == 2 && face[CuboID_outro2] == 5 || face[CuboID_outro2] == 2 && face[CuboID_outro1] == 5) estado[CuboID] = 4; //amarelo + laranja = vermelho
  else if(face[CuboID_outro1] == 2 && face[CuboID_outro2] == 6 || face[CuboID_outro2] == 2 && face[CuboID_outro1] == 6) estado[CuboID] = 6; //amarelo + magenta = laranja

  else if(face[CuboID_outro1] == 3 && face[CuboID_outro2] == 4 || face[CuboID_outro2] == 3 && face[CuboID_outro1] == 4) estado[CuboID] = 3;  //vermelho + verde = amarelo
  else if(face[CuboID_outro1] == 3 && face[CuboID_outro2] == 5 || face[CuboID_outro2] == 3 && face[CuboID_outro1] == 5) estado[CuboID] = 13;  //vermelho + laranja = vermelho-alaranjado
  else if(face[CuboID_outro1] == 3 && face[CuboID_outro2] == 6 || face[CuboID_outro2] == 3 && face[CuboID_outro1] == 6) estado[CuboID] = 14;  //vermelho + magenta = rosa

  else if(face[CuboID_outro1] == 4 && face[CuboID_outro2] == 5 || face[CuboID_outro2] == 4 && face[CuboID_outro1] == 5) estado[CuboID] = 15;  //verde + laranja = citrino
  else if(face[CuboID_outro1] == 4 && face[CuboID_outro2] == 6 || face[CuboID_outro2] == 4 && face[CuboID_outro1] == 6) estado[CuboID] = 16;  //verde + magenta = ardosia
  
  else if(face[CuboID_outro1] == 5 && face[CuboID_outro2] == 6 || face[CuboID_outro2] == 5 && face[CuboID_outro1] == 6) estado[CuboID] = 4; //laranja + magenta = considerei vermelho


  
  break;

case 9://cyan
  definirCorPalheta(4);
  luzligada();
  estado[CuboID] = 1;
  break;

case 10://amarelo-alaranjado 237,118,14  
  definirCorRGB(237,118,14);
  luzligada();
  estado[CuboID] = 1;
  break;

case 11://purple
  definirCorPalheta(18);
  luzligada();
  estado[CuboID] = 1;
  break;

case 12://olive
  definirCorPalheta(15);
  luzligada();
  estado[CuboID] = 1;
  break;
  
case 13://vermelho-alaranjado
  definirCorRGB(255,69,0);
  luzligada();
  estado[CuboID] = 1;
  break;
  
case 14://rosa
  definirCorPalheta(13);
  luzligada();
  estado[CuboID] = 1;
  break;

case 15://citrino
  definirCorRGB(98,91,65);
  luzligada();
  estado[CuboID] = 1;
  break;

case 16://ardosia
  definirCorRGB(123,104,238);
  luzligada();
  estado[CuboID] = 1;
  break;

