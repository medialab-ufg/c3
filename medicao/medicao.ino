/*
  C3 Acelerometro - medicao
 */
 
#include<Wire.h>  // Suporte ao Giroscpio MPU6050

//Endereco I2C do MPU6050
const int MPU=0x68;  
//Variaveis para armazenar valores dos sensores
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int min_AcX,min_AcY,min_AcZ,min_GyX,min_GyY,min_GyZ;
int max_AcX,max_AcY,max_AcZ,max_GyX,max_GyY,max_GyZ;
int frst=0;

int led = 13;




void setup() {                
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
   
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);
  // initialize the digital pin as an output.
  Serial.begin(9600);
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
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
   
  /* //Envia valor X do acelerometro para a serial e o LCD
  Serial.print("AcX = "); Serial.print(AcX);
   
  //Envia valor Y do acelerometro para a serial e o LCD
  Serial.print(" | AcY = "); Serial.print(AcY);
  
  //Envia valor Z do acelerometro para a serial e o LCD
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  
  //Envia valor da temperatura para a serial e o LCD
  //Calcula a temperatura em graus Celsius
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);
   
  //Envia valor X do giroscopio para a serial e o LCD
  Serial.print(" | GyX = "); Serial.print(GyX);
   
  //Envia valor Y do giroscopio para a serial e o LCD  
  Serial.print(" | GyY = "); Serial.print(GyY);
   
  //Envia valor Z do giroscopio para a serial e o LCD
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  */
  
  Serial.print("AcX = ["); Serial.print(min_AcX);Serial.print(",");Serial.print(max_AcX);Serial.print("] ");
  Serial.print(" | AcY = "); Serial.print(min_AcY);Serial.print(",");Serial.print(max_AcY);Serial.print("] ");
  Serial.print(" | AcZ = "); Serial.print(min_AcZ);Serial.print(",");Serial.print(max_AcZ);Serial.print("] ");
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);
  Serial.print(" | GyX = "); Serial.print(min_GyX);Serial.print(",");Serial.print(max_GyX);Serial.print("] ");
  Serial.print(" | GyY = "); Serial.print(min_GyY);Serial.print(",");Serial.print(max_GyY);Serial.print("] ");;
  Serial.print(" | GyZ = "); Serial.print(min_GyZ);Serial.print(",");Serial.print(max_GyZ);Serial.println("]");
  
  
   if (!frst) {
     min_AcX=AcX;min_AcY=AcY;min_AcZ=AcZ;
     min_GyX=GyX;min_GyY=GyY;min_GyZ=GyZ;
     max_AcX=AcX;max_AcY=AcY;max_AcZ=AcZ;
     max_GyX=GyX;max_GyY=GyY;max_GyZ=GyZ;
     frst=1;
   } else {
     min_AcX=min(min_AcX,AcX);min_AcY=min(min_AcY,AcY);min_AcZ=min(min_AcZ,AcZ);
     min_GyX=min(min_GyX,GyX);min_GyY=min(min_GyY,GyY);min_GyZ=min(min_GyZ,GyZ);
     max_AcX=max(max_AcX,AcX);max_AcY=max(max_AcY,AcY);max_AcZ=max(max_AcZ,AcZ);
     max_GyX=max(max_GyX,GyX);max_GyY=max(max_GyY,GyY);max_GyZ=max(max_GyZ,GyZ);
   }
  //Aguarda 300 ms e reinicia o processo
  delay(300);
}
