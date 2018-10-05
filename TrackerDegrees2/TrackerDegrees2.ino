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

volatile int countPos = 0;    //counts in the positive direction (cw)
volatile int countNeg = 0;    //counts in the negative direction (ccw)
int target =  -45;            //target (in degrees) for tracker to move to
int cal = 112;                //counts per degree
volatile int count = 0;       //number of pulses from hall effect sensor on slew drive
int deg = 0;                  //degrees moved from initial position
int absp = 0;                 //apsolute position
boolean dir = true;           //true for clockwise, false for counter-clockwise


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
  attachInterrupt(digitalPinToInterrupt(2), magnet_detect, FALLING); //interrupt on pin 2 to detect hall sensor
}

void loop() {
  // put your main code here, to run repeatedly:
  forward(target);                          //move slew cw if position is less than target
  backward(target);                         //move slew ccw backward if position is greater than target

  //BUTTONS DO NOT CHANGE ABSOLUTE POSITION VARIABLE
  if(digitalRead(button4) == HIGH)          //retract actuator when button4 is pressed
    digitalWrite(actuator_retract, LOW);
  else
    digitalWrite(actuator_retract, HIGH);
    
  if(digitalRead(button3) == HIGH)          //extend actuator when button3 is pressed
    digitalWrite(actuator_extend, LOW);
  else
    digitalWrite(actuator_extend, HIGH);

  if(digitalRead(button2) == HIGH) {        //turn cw when button2 is pressed
    digitalWrite(slew_cw, LOW);   
    dir = true; 
  }
  else 
    digitalWrite(slew_cw, HIGH);
  
  if(digitalRead(button1) == HIGH) {        //turn ccw when button1 is pressed
    digitalWrite(slew_ccw, LOW);
    dir = false;
  }
  else 
    digitalWrite(slew_ccw, HIGH);  
}

void magnet_detect() {                      //called when hall signal detected
  if(dir == true)
    countPos++;
  else
    countNeg++;
}

void forward(int targ) {        //move slew cw if position is less than target
  while(absp < targ)            //don't change global var target in this function
  {
    digitalWrite(slew_cw, LOW);
    dir = true;
    if(countPos - countNeg >= cal*deg)
    {
      deg++;
      Serial.print("degrees = ");
      Serial.print(deg);
      Serial.print("\n");
      absp++;
    }
  }
  digitalWrite(slew_cw, HIGH);
}

void backward(int targ) {       //move slew ccw if position is greater than target
  while(absp > targ)            //don't change global var target in this function
  {
    digitalWrite(slew_ccw, LOW);
    dir = false;
    if(countPos - countNeg <= cal*deg)
    {
      deg--;
      Serial.print("degrees = ");
      Serial.print(deg);
      Serial.print("\n");
      absp--;
    }
  }
  digitalWrite(slew_ccw, HIGH);
}

