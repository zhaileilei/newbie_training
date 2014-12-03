/*============================================
 *	Filename:
 *       i2cmaster.c
 *
 *  Copright (C) 2014 Wistron
 *  All rights reserved
 *	Description:
 *		This file will achieve that i2c communication.
 *		
 *	Author/Create Date:
 *		Myth Zhai,Dec03'14
 *
 *  Modification History:
 *
 *
 *  Note:
 *
 *============================================
 */

#include <Wire.h>
#define LED 13
byte x = 0;

void setup()
{
  Wire.begin(); 
  pinMode(LED,OUTPUT);
}

void loop()
{
  Wire.beginTransmission(4); 
  Wire.send("light is ");       
  Wire.send(x);              
  Wire.endTransmission();    

  x++;
  if(x==2)
  x=0;
  delay(1000);
  
  Wire.requestFrom(4, 1);    
  while(Wire.available()>0)    
  { 
    byte c = Wire.receive(); 
    
    if(c==1)
    {digitalWrite(LED,LOW);}
    else
     {digitalWrite(LED,HIGH);}
  }
  delay(1000);
}
