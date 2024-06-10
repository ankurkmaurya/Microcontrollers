#include <Wire.h>    

#define address_ 0x50  //Address of 24LC256 eeprom chip
 
void setup(void)
{
  
  Serial.begin(9600);
  Wire.begin();  
 
  unsigned int address = 12;
 
  writeEEPROM(address_, address, 113);
  Serial.print("Reading Data : ");
  Serial.println(readEEPROM(address_, address), DEC);
}
 
void loop(){}
 
void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) 
{
  Serial.print("Writing Data : ");
  Serial.println(data, DEC);
  Wire.beginTransmission(deviceaddress);
 // Wire.send((int)(eeaddress >> 8));   // MSB
  //Wire.send((int)(eeaddress & 0xFF)); // LSB
  Wire.write(eeaddress);
  Wire.write(data);
  Wire.endTransmission();
 
  delay(5);
}
 
byte readEEPROM(int deviceaddress, unsigned int eeaddress ) 
{
  byte rdata = 0x00;
 
  Wire.beginTransmission(deviceaddress);
 // Wire.send((int)(eeaddress >> 8));   // MSB
 // Wire.send((int)(eeaddress & 0xFF)); // LSB
   Wire.write(eeaddress);
  Wire.endTransmission();
 
  Wire.requestFrom(deviceaddress,1);
 
  if (Wire.available()) 
  rdata = Wire.read();
 
  return rdata;
}
