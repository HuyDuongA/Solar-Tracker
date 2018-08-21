/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include "RF24.h"

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
int integer = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.print("isChipConnected: ");
  Serial.println(radio.isChipConnected());
}

void loop() {
  if (radio.available()) {
    //Serial.println(radio.available());
    radio.read(&integer, sizeof(integer));
    //Serial.print("h");
    //Serial.println(integer);
  }
}
