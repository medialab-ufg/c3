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



//Cores associadas a cada face do cubo

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




/*
 * Cubo 0: principal, muda de acordo com as cores dos Cubos 1 e 2;
 * 
 * Exemplo 1: Se ambos possuem a mesma cor, o Cubo 0 tera' a cor dos 2 outros Cubos;
 * 
 * Exemplo 2: Se o Cubo 1 tiver a cor Vermelho e o cubo 2 tiver a cor Verde (por exemplo), o Cubo 0 tera a cor Amarelo
 * 
 * 
 */
 /*  em desenvolvimento
case 0:
  //inicializa desligado
  luzdesligada();
  estado[CuboID] = 1;
  tempomarcado=millis();
  break;

case 1:
  //SaveBattery
  if (tempoatual < tempomarcado) tempomarcado=millis();
  else if ((tempoatual - tempomarcado) > 15000)  {
    somligado(500, 250);
    goToSaveBatteryState(0);
  }
  
  if(CuboID == 1 || CuboID ==2){
    switch(face[CuboID]){
      case 1: 
        definirCorPalheta(2);//corAzul();
        luzligada();
        break;
      case 2:
        definirCorPalheta(9);//corAmarelo();
        luzligada();
        break;
      case 3: 
        definirCorPalheta(0);//corVermelho();
        luzligada();
        break;
      case 4: 
        definirCorPalheta(3);//corVerde();
        luzligada();
        break;
      case 5: 
        definirCorPalheta(11);//corLaranja();
        luzligada();
        break;
      case 6: 
        definirCorPalheta(20);//corMagenta();
        luzligada();
        break;
    }
  }
  if(CuboID == 0){
    estado[CuboID] == 2;
  }
  break;

case 2:

  if(face[1] == face[2]){
    if(face[1] == 1){
      
    }
  }


*/


