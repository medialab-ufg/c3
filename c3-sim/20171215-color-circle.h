case 0:
	definirCorRGB(0, 51, 0);
	somligado(494.0, 500);
	estado[CuboID] = 1;
  tempomarcado=millis(); // guarda tempo atual
	break;
case 1:
	 if (1
		&& (face[CuboID] == 1)
	) {
				estado[CuboID] = 2;
	}
	 if (1
		&& (face[CuboID] == 2)
	) {
				estado[CuboID] = 4;
	}
	 if (1
		&& (face[CuboID] == 3)
	) {
				estado[CuboID] = 6;
	}
	 if (1
		&& (face[CuboID] == 4)
	) {
				estado[CuboID] = 8;
	}
	 if (1
		&& (face[CuboID] == 5)
	) {
				estado[CuboID] = 10;
	}
  if (tempoatual < tempomarcado) tempomarcado=millis();
  else if ((tempoatual - tempomarcado) > 15000)  {
    somligado(500, 250);
    goToSaveBatteryState(0);
  }
	luzpiscando(500);
	break;
case 2:
	definirCorRGB(153, 77, 0);
	somligado(293.0, 500);
	estado[CuboID] = 3;
	break;
case 3:
	 if (1
		&& (face[CuboID] == 2)
	) {
				estado[CuboID] = 4;
	}
	 if (1
		&& (face[CuboID] == 6)
	) {
				estado[CuboID] = 0;
	}
	 if (1
		&& (face[CuboID] == 3)
	) {
				estado[CuboID] = 6;
	}
	 if (1
		&& (face[CuboID] == 4)
	) {
				estado[CuboID] = 8;
	}
	 if (1
		&& (face[CuboID] == 5)
	) {
				estado[CuboID] = 10;
	}
  if (tempoatual < tempomarcado) tempomarcado=millis();
  else if ((tempoatual - tempomarcado) > 15000)  {
    somligado(500, 250);
    goToSaveBatteryState(0);
  }
	luzpiscando(500);
	break;
case 4:
	definirCorRGB(153, 0, 0);
	somligado(329.0, 500);
	estado[CuboID] = 5;
	break;
case 5:
	 if (1
		&& (face[CuboID] == 3)
	) {
				estado[CuboID] = 6;
	}
	 if (1
		&& (face[CuboID] == 1)
	) {
				estado[CuboID] = 2;
	}
	 if (1
		&& (face[CuboID] == 4)
	) {
				estado[CuboID] = 8;
	}
	 if (1
		&& (face[CuboID] == 6)
	) {
				estado[CuboID] = 10;
	}
  if (tempoatual < tempomarcado) tempomarcado=millis();
  else if ((tempoatual - tempomarcado) > 15000)  {
    somligado(500, 250);
    goToSaveBatteryState(0);
  }
	luzpiscando(500);
	break;
case 6:
	definirCorRGB(153, 153, 0);
	somligado(349.0, 500);
	estado[CuboID] = 7;
	break;
case 7:
	 if (1
		&& (face[CuboID] == 4)
	) {
				estado[CuboID] = 8;
	}
	 if (1
		&& (face[CuboID] == 6)
	) {
				estado[CuboID] = 4;
	}
	 if (1
		&& (face[CuboID] == 2)
	) {
				estado[CuboID] = 2;
	}
	 if (1
		&& (face[CuboID] == 5)
	) {
				estado[CuboID] = 10;
	}
	 if (1
		&& (face[CuboID] == 1)
	) {
				estado[CuboID] = 0;
	}
  if (tempoatual < tempomarcado) tempomarcado=millis();
  else if ((tempoatual - tempomarcado) > 15000)  {
    somligado(500, 250);
    goToSaveBatteryState(0);
  }
	luzpiscando(500);
	break;
case 8:
	definirCorRGB(51, 0, 51);
	somligado(392.0, 500);
	estado[CuboID] = 9;
	break;
case 9:
	 if (1
		&& (face[CuboID] == 5)
	) {
				estado[CuboID] = 10;
	}
	 if (1
		&& (face[CuboID] == 1)
	) {
				estado[CuboID] = 0;
	}
	 if (1
		&& (face[CuboID] == 1)
	) {
				estado[CuboID] = 0;
	}
	 if (1
		&& (face[CuboID] == 2)
	) {
				estado[CuboID] = 2;
	}
	 if (1
		&& (face[CuboID] == 3)
	) {
				estado[CuboID] = 4;
	}
	 if (1
		&& (face[CuboID] == 6)
	) {
				estado[CuboID] = 6;
	}
	 if (1
		&& (face[CuboID] == 5)
	) {
				estado[CuboID] = 10;
	}
  if (tempoatual < tempomarcado) tempomarcado=millis();
  else if ((tempoatual - tempomarcado) > 15000)  {
    somligado(500, 250);
    goToSaveBatteryState(0);
  }
	luzpiscando(500);
	break;
case 10:
	definirCorRGB(77, 0, 26);
	somligado(440.0, 500);
	estado[CuboID] = 11;
	break;
case 11:
	 if (1
		&& (face[CuboID] == 6)
	) {
				estado[CuboID] = 0;
	}
	 if (1
		&& (face[CuboID] == 1)
	) {
				estado[CuboID] = 2;
	}
	 if (1
		&& (face[CuboID] == 2)
	) {
				estado[CuboID] = 4;
	}
	 if (1
		&& (face[CuboID] == 3)
	) {
				estado[CuboID] = 4;
	}
	 if (1
		&& (face[CuboID] == 4)
	) {
				estado[CuboID] = 6;
	}
  if (tempoatual < tempomarcado) tempomarcado=millis();
  else if ((tempoatual - tempomarcado) > 15000)  {
    somligado(500, 250);
    goToSaveBatteryState(0);
  }
	luzpiscando(500);
	break;
