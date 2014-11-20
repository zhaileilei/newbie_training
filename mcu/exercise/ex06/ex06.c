/*===========================
 *	Filename:
 *		ex06.c
 *
 *	Copyright (C) 2014 Wistron
 *	All rights reserved.
 *
 *	Description:
 *		This file is a Infrared remote control lamp.
 *
 *	Author/Create Date:
 *		Myth Zhai, Nov16'14
 *
 *	Modification History:
 *
 *
 *	Note:
 *=================================
 */
#define BUZZER 10
#define LED_RED 11
#define IR_IN  8  

int Pulse_Width=0;
int  ir_code=0x00;

void timer1_init(void)
{
  TCCR1A = 0X00; 
  TCCR1B = 0X05;
  TCCR1C = 0X00;
  TCNT1 = 0X00;
  TIMSK1 = 0X00;	
}
void remote_deal(void)
{ 
  switch(ir_code)
  {
  case 0xff00:
    digitalWrite(LED_RED,LOW);
    digitalWrite(BUZZER,LOW);
    break;
  case 0xfe01:
    digitalWrite(LED_RED,HIGH);
    break;
  case 0xf609:
    digitalWrite(BUZZER,HIGH);
    break;
  }
}
char logic_value()
{
  while(!(digitalRead(8))); 
  Pulse_Width=TCNT1;
  TCNT1=0;
  if(Pulse_Width>=7&&Pulse_Width<=10)
  {
    while(digitalRead(8));
    Pulse_Width=TCNT1;
    TCNT1=0;
    if(Pulse_Width>=7&&Pulse_Width<=10)
      return 0;
    else if(Pulse_Width>=25&&Pulse_Width<=27) 
      return 1;
  }
  return -1;
}
void pulse_deal()
{
  int i;
  for(i=0; i<8; i++)
  {
    if(logic_value() != 0) 
        return;
  }
  for(i=0; i<6; i++)
  {
    if(logic_value()!= 1) 
        return;
  }
  if(logic_value()!= 0) 
      return;
  
  if(logic_value()!= 1) 
      return;

  ir_code=0x00;
  for(i=0; i<16;i++ )
  {
    if(logic_value() == 1)
    {
      ir_code |=(1<<i);
    }
  }
}
void remote_decode(void)
{
  TCNT1=0X00;       
  while(digitalRead(8))
  {
    if(TCNT1>=1563)  
	{
      ir_code = 0xff00;
      return;
    }  
  }

  
  TCNT1=0X00;

  while(!(digitalRead(8))); 
  Pulse_Width=TCNT1;
  TCNT1=0;
  if(Pulse_Width>=140&&Pulse_Width<=141)
  {

    while(digitalRead(8));
    Pulse_Width=TCNT1;
    TCNT1=0;
    if(Pulse_Width>=68&&Pulse_Width<=72)
    {
      pulse_deal();
      return;
    }
    else if(Pulse_Width>=34&&Pulse_Width<=36)
    {
      while(!(digitalRead(8)));
      Pulse_Width=TCNT1;
      TCNT1=0;
      if(Pulse_Width>=7&&Pulse_Width<=10)
      {
        return; 
      }
    }
  }
}
void setup()
{
  unsigned char i;
  pinMode(LED_RED,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  pinMode(IR_IN,INPUT);
}
void loop()
{  
  timer1_init();
  while(1)
  {
    remote_decode();  
    remote_deal();   
  }  
}



