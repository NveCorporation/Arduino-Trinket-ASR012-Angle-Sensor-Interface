/**************************************************************************************
Trinket displays NVE ASR012 I²C Smart Angle Sensor on a COM-11441 7-segment display
SDA=#0; SCL=#2; LED=#1; USB for programming=#3/#4
Use with AG966 breakout board (see https://www.nve.com/webstore/catalog )
**************************************************************************************/ 
#include <TinyWireM.h> //ATTiny85 I²C Master library
//Use Wire.h for Arduino and replace "TinyWireM." with "Wire."
int sensor, digit; //Sensor output; digit counter
void setup() {TinyWireM.begin();}

void loop() {
  TinyWireM.requestFrom(36,2); //Request two bytes from I²C address 72 (36 = 72/2)
  sensor = TinyWireM.read()<<8; //Read sensor MSB
  sensor|=TinyWireM.read(); //Read sensor LSB

//Display sensor output
  TinyWireM.beginTransmission(0x71); //Write to 7-segment display (I²C address 0x71)
  TinyWireM.write(0x76); //Clear display
  TinyWireM.write(0x77); //Set decimal point
  TinyWireM.write(0b0100); //Displays xxx.x degrees
for(digit=1000; digit>0; digit/=10) { //Start at 100s digit
  TinyWireM.write((sensor%(digit*10))/digit); //Scan through display digits
  }
  TinyWireM.endTransmission();
delay(100); //10 samples/second
}
