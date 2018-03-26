// Dados necessários para o Acelerômetro/Giroscópio
//Endereco I2C do MPU6050
#define MPU 0x68


//  Medicoes atualizadas:
//      Axis         Face 01         Face 02         Face 03         Face 04         Face 05         Face 06

int16_t 
#if CuboID==0// Cubo 0
         v_AcX[6][2]={{-4136, 3072},{-14496,-1112 },{  8520, 16384},{9760,15672},{-13196,-7500},{-1516,5536}},
         v_AcY[6][2]={{-5232,  948},{-29384,-11432},{-19952, -9500},{3684,10960},{  5020,11392},{-5888, 590}},
         v_AcZ[6][2]={{15808,21676},{ -2788,  8704},{   200,  7200},{-516, 6140},{ -5280, 4192},{-22520,  0}};
#endif


#if CuboID==1// Cubo 1
         v_AcX[6][2]={{-5776, 3708},{-13904, -7684},{-17396,  -472},{ 10844, 15276},{ 10300,13932},{ -1796,  5648}},
         v_AcY[6][2]={{-8920, -644},{  4820, 10752},{-18216,-11888},{-18352,-13032},{  5152, 9852},{ -7988,  -600}},
         v_AcZ[6][2]={{ 7032,25568},{ -5368,   736},{ -6544,  2436},{ -4424,  1736},{ -2756, 2180},{-27524,-14068}};
#endif

#if CuboID==2// Cubo 2
         v_AcX[6][2]={{-2904, 3832},{-13460, -8844},{ -13700,-7724},{  7040,14956},{ 8544,15164},{ -1796,  6112}},
         v_AcY[6][2]={{-6952, 4792},{  8912, 13368},{ -14912,-9064},{-14760,-7744},{ 7676,14440},{ -3476,  5024}},
         v_AcZ[6][2]={{13236,20576},{ -3588,  2292},{  -3812, 3188},{ -3600, 5104},{-2000, 4184},{-22140,-14436}};
#endif


long int bAcX, bAcY, bAcZ, bGyX, bGyY, bGyZ;


#define maxcontdist 6

double dist[maxcontdist];
int   posdist=-2;  // posicao do ultime elemento colocado no vertor de distancia. O valor -2 indica que eh preciso ainda obter os primeiros valores do acelerometro e giroscopio
double somadist=0;

bool balancando=false, segurando=false;

uint32_t mark_time_acel, tmp_time_acel = 0;

int face[4]={0,0,0,0}; // Guarda as faces dos cubos

/*
  Codigo do Acelerometro
*/
void inicia_contdiff();

void setup_Acl() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);

  //Inicializa o MPU-6050
  Wire.write(0);
  Wire.endTransmission(true);

  //Zera o vetor de distancia do acelerometro
  inicia_contdiff();
  mark_time_acel = millis();
}


// Preenche vetor de distancias do acelerometro com zero
void inicia_contdiff(){
  int i;

  for (i=0;i<maxcontdist;i++) dist[i]=0;
}


// the loop routine runs over and over again forever:
void loop_Acl() {
  //Variaveis para armazenar valores dos sensores
  long int AcX,AcY,AcZ,Tmp, GyX,GyY,GyZ;
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);
  //Armazena o valor dos sensores nas variaveis correspondentes
  AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

   // Obtem a face do cubo virada para cima
  face[CuboID] = 0;
  int f;
  for (f=0; f<6; f++)
    if ((AcX  >= v_AcX[f][0]) && (AcX  <= v_AcX[f][1]) &&
        (AcY  >= v_AcY[f][0]) && (AcY  <= v_AcY[f][1]) &&
        (AcZ  >= v_AcZ[f][0]) && (AcZ  <= v_AcZ[f][1]) ) {
          face[CuboID] = f+1;
          break;
     }

   // verificar se o usuario esta' balancando o cubo, movendo-o ou parado
  tmp_time_acel = millis();

     
  if (posdist==-2) {
     bAcX=AcX; bAcY=AcY; bAcZ=AcZ; bGyX=GyX; bGyY=GyY; bGyZ=GyZ;
     posdist = -1;
  } else if ((tmp_time_acel - mark_time_acel) >= 200) {
    double dist1 = 1.0*abs(bAcX-AcX) + abs(bAcY-AcY) + abs(bAcZ-AcZ);
    double dist2=1.0*(bGyX-GyX)*(bGyX-GyX) + 1.0*(bGyY-GyY)*(bGyY-GyY) + 1.0*(bGyZ-GyZ)*(bGyZ-GyZ);
    posdist = (posdist+1)%maxcontdist;
    //double dist_old=dist[posdist]; 
    somadist -= dist[posdist];
    somadist += (dist[posdist] =  dist1);
    #ifdef DEBUG_AC
      Serial.print("face = "); Serial.print(face[CuboID]); 
      Serial.print("\tsoma dist = "); Serial.print(somadist); 
      Serial.print("\t\tdist1 = "); Serial.print(dist1); 
      if (dist1<0)  Serial.print("ERROR   ");
      Serial.print("\t\tdist2 = "); Serial.println(dist2);
    #endif
    //////////////////////////////////////////////////////////////////////////////////////
    // DEPURACAO DOS VALORES DE DISTANCIA E SUA SOMA
    /* double f=0; for (int i=0; i<maxcontdist;i++) f+=dist[i]; 
    if (f!=somadist) {
     Serial.print("soma dist REAL = "); Serial.println(f); Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");      
       Serial.print("soma dist = "); Serial.print(somadist); 
      Serial.print("\t\tdist_old = "); Serial.print(dist_old); 
      Serial.print("\t\tdist1 = "); Serial.print(dist1); 
      Serial.print("\t\tdist2 = "); Serial.println(dist2);
      for (int i=0; i<maxcontdist;i++) Serial.println(dist[i]); 
    } */
    bAcX=AcX; bAcY=AcY; bAcZ=AcZ; bGyX=GyX; bGyY=GyY; bGyZ=GyZ;
    if (somadist>90000) {
      #ifdef DEBUG_AC
         Serial.println(">>>>>>balancando");
      #endif
      balancando=true;
      segurando=true;
    } else {
      balancando=false;
      if (/*dist1 > 500  || */ dist2 > 30000) {
        #ifdef DEBUG_AC
           Serial.println("\t\t\t\t*************Segurando*****");
        #endif
        segurando=true;
      } else segurando = false;
    }
    mark_time_acel = tmp_time_acel;
  }
}

