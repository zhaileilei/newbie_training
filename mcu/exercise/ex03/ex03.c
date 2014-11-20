/*===========================
 *	Filename:
 *		ex03.c
 *
 *	Copyright (C) 2014 Wistron
 *	All rights reserved.
 *
 *	Description:
 *		This file is a Respiration lamp.
 *
 *	Author/Create Date:
 *		Myth Zhai, Oct30'14
 *
 *	Modification History:
 *
 *
 *	Note:
 *=================================
 */
int ledPin = 10;
void setup() {
	pinMode(ledPin,OUTPUT);
}
void loop(){
	fadeOn(1000,5);
	fadeOff(1000,5);
}
void fadeOn(unsigned int time,int increament){
	for (byte value = 0 ; value < 255; value+=increament){
		analogWrite(ledPin, value);
		delay(time/(255/5));
	}
}
void fadeOff(unsigned int time,int decreament){
	for (byte value = 255; value >0; value-=decreament){
		analogWrite(ledPin, value);
		delay(time/(255/5));
	}
}
