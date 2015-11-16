// ask_transmitter.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to transmit messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) transmitter with an TX-C1 module
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
RH_ASK driver;

void setup()
{
    Serial.begin(9600);   // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    else Serial.println("init with sucess");
    pinMode(13,OUTPUT);
}


void loop()
{
    //Serial.print(rxPin);
//    uint8_t rxPin = 6; // Any ways to avoid setting rxPin?
//uint8_t txPin = 10;
//uint8_t pttPin = 7;
    const char *msg = "hello";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.print("Message sent:");
    Serial.println(msg);
    delay(200);
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
}

