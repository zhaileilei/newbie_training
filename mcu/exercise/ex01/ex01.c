/*===========================
 *	Filename:
 *		ex01.c
 *
 *	Copyright (C) 2014 Wistron
 *	All rights reserved.
 *
 *	Description:
 *		This file will achieve LED blink.
 *
 *	Author/Create Date:
 *		Myth Zhai, Oct23'14
 *
 *	Modification History:
 *
 *
 *	Note:
 *=================================
 */


int ledPin = 10;
void setup() {
	pinMode(ledPin, OUTPUT);
}
void loop() {
	digitalWrite(ledPin,HIGH);
	delay(1000);
	digitalWrite(ledPin,LOW);
	delay(1000);
}
