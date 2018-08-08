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
int target = 45;
volatile int count = 0;
int deg = 0;

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
  while(count < target*112)
  {
    digitalWrite(slew_cw, LOW);
    if(count >= 112*deg)
    {
      Serial.print("degrees = ");
      Serial.print(deg);
      Serial.print("\n");
      deg++;
    }
  }
  Serial.print(target);
  Serial.print("\n");
  digitalWrite(slew_cw, HIGH);
  
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
  }
  else {
    digitalWrite(slew_cw, HIGH);
  }
  
  if(digitalRead(button1) == HIGH) {
    digitalWrite(slew_ccw, LOW);
  }
  else {
    digitalWrite(slew_ccw, HIGH);  
  }
}

void magnet_detect() {
  count++;
}

