//code to move tracker based on given inputs, or with buttons 
//buttons do not change absolute input

#define actuator_retract 22
#define actuator_extend 23
#define slew_cw 26
#define slew_ccw 28
#define button4 24      //controls actuator retract
#define button3 29      //controls actuator extend
#define button2 25      //controls slew clockwise
#define button1 27      //controls slew counter-clockwise
#define hall_sensor 2
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

//actuator lengths used to calculate from angle
int b = 22.25;                
int a = 6.25;

//SLEW variables
volatile int countPosS = 0;    //counts in the positive direction (cw)
volatile int countNegS = 0;    //counts in the negative direction (ccw)
int targetS =  0;              //target (in degrees) for tracker to move to
int calS = 112;                //counts per degree
volatile int countS = 0;       //number of pulses from hall effect sensor on slew drive
int degS = 0;                  //degrees moved from initial position
int abspS = 0;                 //apsolute position
boolean dirS = true;           //true for clockwise, false for counter-clockwise

//ACTUATOR variables
volatile int countPosA = 0;    //counts in the positive direction (extend)
volatile int countNegA = 0;    //counts in the negative direction (retract)
int targetL = 0;          //target in inches for actuator to extend
int targetA =  0;              //target (in degrees) for tracker to move to
int calA = 203; //????                  //counts per degree
volatile int countA = 0;       //number of pulses from hall effect sensor on actuator
int degA = 0;                  //degrees moved from initial position
int abspA = 0;                 //apsolute position
boolean dirA = true;           //true for extend, false for retract

RF24 radio(9, 10);
const byte address[6] = "00001";


void setup() {
  // put your setup code here, to run once
  digitalWrite(actuator_retract, HIGH);     //relay triggered by a LOW signal, so set to HIGH
  digitalWrite(actuator_extend, HIGH);
  digitalWrite(slew_ccw, HIGH);
  digitalWrite(slew_cw, HIGH);
  
  pinMode(actuator_retract, OUTPUT);
  pinMode(actuator_extend, OUTPUT);
  pinMode(slew_ccw, OUTPUT);
  pinMode(slew_cw, OUTPUT); 
  
  pinMode(button4, INPUT);
  pinMode(button3, INPUT);
  pinMode(button2, INPUT);
  pinMode(button1, INPUT);
  
  digitalWrite(button4, LOW);
  digitalWrite(button3, LOW);
  digitalWrite(button2, LOW);
  digitalWrite(button1, LOW);
  
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), magnet_detectS, FALLING); //interrupt on pin 2 to detect hall sensor
  attachInterrupt(digitalPinToInterrupt(3), magnet_detectA, FALLING); //interrupt on pin 3 to detect hall sensor
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:

  /**if(radio.available()){
      radio.read(&targetS, sizeof(targetS));
      Serial.println(targetS);
    }**/

  targetL = sqrt(b*b+a*a-2*a*b*cos(targetA));
  
  forward(targetS);                          //move slew cw if position is less than target
  backward(targetS);                         //move slew ccw backward if position is greater than target
  extend(targetL);                           //extend actuator if position less than target
  retract(targetL);                          //retract actuator if position greater than target

  //BUTTONS DO NOT CHANGE ABSOLUTE POSITION VARIABLE
  if(digitalRead(button4) == HIGH)   {       //retract actuator when button4 is pressed
    dirA = false;
    digitalWrite(actuator_retract, LOW);
  }
  else
    digitalWrite(actuator_retract, HIGH);
    
  if(digitalRead(button3) == HIGH)  {        //extend actuator when button3 is pressed
    dirA = true;
    digitalWrite(actuator_extend, LOW);
  }
  else
    digitalWrite(actuator_extend, HIGH);

  if(digitalRead(button2) == HIGH) {        //turn cw when button2 is pressed
    digitalWrite(slew_cw, LOW);   
    dirS = true; 
  }
  else 
    digitalWrite(slew_cw, HIGH);
  
  if(digitalRead(button1) == HIGH) {        //turn ccw when button1 is pressed
    digitalWrite(slew_ccw, LOW);
    dirS = false;
  }
  else 
    digitalWrite(slew_ccw, HIGH);  
}

void magnet_detectS() {                      //called when hall signal detected
  if(dirS == true)
    countPosS++;
  else
    countNegS++;
}

void magnet_detectA() {
  if(dirA == true)
    countPosA++;
  else
    countNegA++;
}

void forward(int targ) {        //move slew cw if position is less than target
  while(abspS < targ)            //don't change global var target in this function
  {
    digitalWrite(slew_cw, LOW);
    dirS = true;
    if(countPosS - countNegS >= calS*degS)
    {
      degS++;
      Serial.print("degrees slew= ");
      Serial.print(degS);
      Serial.print("\n");
      abspS++;
    }
  }
  digitalWrite(slew_cw, HIGH);
}

void backward(int targ) {       //move slew ccw if position is greater than target
  while(abspS > targ)            //don't change global var target in this function
  {
    digitalWrite(slew_ccw, LOW);
    dirS = false;
    if(countPosS - countNegS <= calS*degS)
    {
      degS--;
      Serial.print("degrees slew = ");
      Serial.print(degS);
      Serial.print("\n");
      abspS--;
    }
  }
  digitalWrite(slew_ccw, HIGH);
}

void extend(int targ) {
  while(abspA < targ)            //don't change global var target in this function
    {
      digitalWrite(actuator_extend, LOW);
      dirA = true;
      if(countPosA - countNegA >= calA*degA)
      {
        degA++;
        Serial.print("degrees actuator = ");
        Serial.print(degA);
        Serial.print("\n");
        abspA++;
      }
    }
    digitalWrite(actuator_extend, HIGH);
}

void retract(int targ) {
  while(abspA > targ)            //don't change global var target in this function
  {
    digitalWrite(actuator_retract, LOW);
    dirS = false;
    if(countPosA - countNegA <= calA*degA)
    {
      degA--;
      Serial.print("degrees actuator = ");
      Serial.print(degA);
      Serial.print("\n");
      abspA--;
    }
  }
  digitalWrite(actuator_retract, HIGH);
}

