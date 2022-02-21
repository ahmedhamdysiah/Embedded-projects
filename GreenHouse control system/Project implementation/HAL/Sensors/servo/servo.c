/*
 * servo.c
 *
 * Created: 7/28/2021 03:25:58 PM
 *  Author: mohammed sabry
 */ 
#include "servo.h"
void servo_Init(void)
{
	
	//Configure TIMER1
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)

	ICR1=2499;  //fPWM=50Hz (Period = 20ms Standard).

	DDRD|=(1<<PD5);   //PWM Pin as Out

	
}
void servo_angle (char angle)
{
	OCR1A =((angle /180.0)*124.57)+124.57;
	
	
}