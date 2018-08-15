#include <math.h>
#define Vph1 A1
#define Vph2 A2
#define Vph3 A3
#define Vph4 A4
#define sigRet A0
#define C_val 0.13

void setup() {
  // put your setup code here, to run once:
  pinMode(Vph1, INPUT); 
  pinMode(Vph2, INPUT); 
  pinMode(Vph3, INPUT);
  pinMode(Vph4, INPUT); 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int V1, V2, V3, V4, X1, X2, Y1, Y2;
  double FX, FY, angleX, angleY;
  V1 = analogRead(Vph1);
  V2 = analogRead(Vph2);
  V3 = analogRead(Vph3);
  V4 = analogRead(Vph4);
  X1 = V3 + V4;
  X2 = V1 + V2;
  FX = (double)(X2 - X1)/(X2 + X1);
  angleX = atan(C_val*FX)*360/(2*3.1415);
  Y1 = V1 + V4;
  Y2 = V2 + V3;
  FY = (double)(Y2 - Y1)/(Y2 + Y1);
  angleY = atan(C_val*FY)*360/(2*3.1415);
  Serial.print("angleX = ");
  Serial.println(angleX);
  Serial.print("angleY = ");
  Serial.println(angleY);

  Serial.print("X1 = ");
  Serial.println(X1);
  Serial.print("X2 = ");
  Serial.println(X2);
  Serial.print("FX = ");
  Serial.println(FX);
  Serial.print("Vph1 = ");
  Serial.println(V1);
  Serial.print("Vph2 = ");
  Serial.println(V2);
  Serial.print("Vph3 = ");
  Serial.println(V3);
  Serial.print("Vph4 = ");
  Serial.println(V4);
  
  Serial.print("Signal Return = ");
  Serial.println(analogRead(sigRet));  
  delay(1000);
}
