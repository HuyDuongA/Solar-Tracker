//#define slew_drive
#define actuator_retract 12
#define actuator_extend 8
#define slew_cw 6
#define slew_ccw 7
#define button4 2 //controls actuator retract
#define button3 3 //controls actuator extend
#define button2 4 //controls slew clockwise
#define button1 5 //controls slew counter-clockwise

void setup() {
  // put your setup code here, to run once
  pinMode(actuator_retract, OUTPUT);
  pinMode(actuator_extend, OUTPUT);
  pinMode(slew_ccw, OUTPUT);
  pinMode(slew_cw, OUTPUT);
  digitalWrite(actuator_retract, HIGH);
  digitalWrite(actuator_extend, HIGH);
  digitalWrite(slew_ccw, HIGH);
  digitalWrite(slew_cw, HIGH);
  pinMode(button4, INPUT);
  pinMode(button3, INPUT);
  pinMode(button2, INPUT);
  pinMode(button1, INPUT);
  digitalWrite(button4, LOW);
  digitalWrite(button3, LOW);
  digitalWrite(button2, LOW);
  digitalWrite(button1, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(button4) == HIGH)
    digitalWrite(actuator_retract, LOW);
  else
    digitalWrite(actuator_retract, HIGH);
    
  if(digitalRead(button3) == HIGH)
    digitalWrite(actuator_extend, LOW);
  else
    digitalWrite(actuator_extend, HIGH);

  if(digitalRead(button2) == HIGH)
    digitalWrite(slew_cw, LOW);
  else
    digitalWrite(slew_cw, HIGH);

  if(digitalRead(button1) == HIGH)
    digitalWrite(slew_ccw, LOW);
  else
    digitalWrite(slew_ccw, HIGH);
}
