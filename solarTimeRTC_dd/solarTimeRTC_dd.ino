// 
//  PolyTracker
//
//  This code determines the Elevation and Altitude of the Sun for a 2-Axis Tracker located on the Solar Balcony of building-13 
//  on the campus of Cal Poly.
//
//  The Lion's share of this code is from...
//
// Calculate solar position from time and location information
// using an RTC as a time source.

// 2017 Ken Willmott
// Arduino library based on the program "Arduino Uno and Solar Position Calculations"
// (c) David R. Brooks, which can be found at http://www.instesre.org/ArduinoDocuments.htm
// and issued under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License:
// https://creativecommons.org/licenses/by-nc-nd/4.0/

//  Include libraries
//
#include <SolarPosition.h>
#include <DS1307RTC.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// set the LCD address to 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27,20,4);
    
// number of decimal digits to print
const uint8_t digits = 3;

// set position for tracker:
SolarPosition CalPoly(35.17, -120.40);  // Bldg. 13 solar balcony

// program begins

void setup()
{
  Serial.begin(9600);
  Serial.println(F("\tSolar Position Cal Poly SLO"));

  // set the Time service as the time provider
  SolarPosition::setTimeProvider(RTC.get);

  //initialize the lcd
  lcd.init();  
  //open the backlight 
  lcd.backlight(); 
}

void loop()
{
  printTime(RTC.get());

  Serial.print(F("Cal Poly:\t"));
  printSolarPosition(CalPoly.getSolarPosition(), digits);
  Serial.println();
  delay(3000);
}

// Print the solar position to serial and LCD display
//
void printSolarPosition(SolarPosition_t pos, int numDigits)
{
  Serial.print(F("el: "));
  Serial.print(pos.elevation, numDigits);
  Serial.print(F(" deg\t"));

  Serial.print(F("az: "));
  Serial.print(pos.azimuth, numDigits);
  Serial.println(F(" deg"));

   //print to LCD
  if (pos.elevation > 0)
  {
  lcd.setCursor ( 0, 2 );            // 
  lcd.print("Elevation");            //
  lcd.setCursor ( 11, 2 );           // 
  lcd.print(pos.elevation);          //
  lcd.setCursor ( 0, 3 );            // 
  lcd.print("Azimuth");              //
  lcd.setCursor ( 11, 3 );           // 
  lcd.print(pos.azimuth);            //
  }
  else
  {
  lcd.setCursor ( 0, 2 );            // 
  lcd.print("It's Night ...");       //
  lcd.setCursor ( 0, 3 );            // 
  lcd.print("Go to bed!");            //
  }
}

// Print the time to serial and LCD display
//
void printTime(time_t t)
{
  tmElements_t someTime;
  breakTime(t, someTime);

  Serial.print(someTime.Hour);
  Serial.print(F(":"));
  Serial.print(someTime.Minute);
  Serial.print(F(":"));
  Serial.print(someTime.Second);
  Serial.print(F(" UTC on "));
  Serial.print(dayStr(someTime.Wday));
  Serial.print(F(", "));
  Serial.print(monthStr(someTime.Month));
  Serial.print(F(" "));
  Serial.print(someTime.Day);
  Serial.print(F(", "));
  Serial.println(tmYearToCalendar(someTime.Year));
   
  lcd.setCursor ( 0, 0 );               // 
  lcd.print(monthStr(someTime.Month));  // 
  lcd.setCursor ( 10, 0 );              // 
  lcd.print(someTime.Day);              //
  lcd.setCursor ( 0, 1 );               // 
  lcd.print(someTime.Hour);             //
  lcd.print(":");                       //
  lcd.print(someTime.Minute);           //
  lcd.print(":");                       // 
  lcd.print(someTime.Second);           // 
  lcd.print(" UTC TIME   ");            //
}
