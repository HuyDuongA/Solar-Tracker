//#define slew_drive
#define actuator_retract 12
#define actuator_extend 8
#define slew_cw 6
#define slew_ccw 4
#define button4 9 //controls actuator retract
#define button3 3 //controls actuator extend
#define button2 7 //controls slew clockwise
#define button1 5 //controls slew counter-clockwise
#define hall_sensor 2

volatile int countPos = 0;
volatile int countNeg = 0;
int target = 90; //target (in degrees) for tracker to move to
int cal = 112; //counts per degree
volatile int count = 0; //number of pulses from hall effect sensor on slew drive
int deg = 0; //degrees moved
int absp = 45;
boolean dir = true; //true for clockwise, false for counter-clockwise


void setup() {
  // put your setup code here, to run once
  digitalWrite(actuator_retract, HIGH);
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
  attachInterrupt(digitalPinToInterrupt(2), magnet_detect, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  forward(target);
  
  backward(target);
  
  if(digitalRead(button4) == HIGH)
    digitalWrite(actuator_retract, LOW);
  else
    digitalWrite(actuator_retract, HIGH);
    
  if(digitalRead(button3) == HIGH)
    digitalWrite(actuator_extend, LOW);
  else
    digitalWrite(actuator_extend, HIGH);

  if(digitalRead(button2) == HIGH) {
    digitalWrite(slew_cw, LOW);   
    dir = true; 
  }
  else 
    digitalWrite(slew_cw, HIGH);
  
  if(digitalRead(button1) == HIGH) {
    digitalWrite(slew_ccw, LOW);
    dir = false;
  }
  else 
    digitalWrite(slew_ccw, HIGH);  
}

void magnet_detect() {
  if(dir == true)
    countPos++;
  else
    countNeg++;
}

void forward(int targ) {
  while(absp < targ)
  {
    digitalWrite(slew_cw, LOW);
    dir = true;
    if(countPos - countNeg >= cal*deg)
    {
      Serial.print("degrees = ");
      Serial.print(deg);
      Serial.print("\n");
      deg++;
      absp++;
    }
  }
  digitalWrite(slew_cw, HIGH);
}

void backward(int targ) { //don't change global var target in this function
  while(absp > targ)
  {
    digitalWrite(slew_ccw, LOW);
    dir = false;
    if(countPos - countNeg <= cal*deg)
    {
      Serial.print("degrees = ");
      Serial.print(deg);
      Serial.print("\n");
      deg--;
      absp--;
    }
  }
  digitalWrite(slew_ccw, HIGH);
}

