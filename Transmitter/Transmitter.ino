/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(53, 48); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  int integer = 409;
<<<<<<< HEAD
  radio.write(&integer, sizeof(integer));
=======
  //Serial.println(integer);
  radio.write(&integer, sizeof(integer));
  Serial.println(integer);
>>>>>>> 18046be4d4dac2a9c3893f834d1db562c8e5c220
  delay(1000);
}
