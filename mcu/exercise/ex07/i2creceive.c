
/*============================================
 *	Filename:
 *       i2creceive.c
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
int x;

void setup()
{
  Wire.begin(4);                
  Wire.onReceive(receiveEvent); 
  Wire.onRequest(requestEvent); 
  Serial.begin(9600);           
}

void loop()
{
  delay(100);
}


void receiveEvent(int howMany)
{
  while( Wire.available()>1) 
  {
    char c = Wire.receive(); 
    Serial.print(c);         
  }
   
  x = Wire.receive();    
  Serial.println(x);     
}


void requestEvent()
{
  
  Wire.send( x); 
}
