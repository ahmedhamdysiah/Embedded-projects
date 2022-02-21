/*
 * ultrasonic.c
 *
 * Created: 7/26/2021 7:31:50 PM
 *  Author: M
 */ 
#include "ultrasonic.h"
static void Func_ICU(void);
static void Func_OVF(void);
static volatile u16 t1,t2,flag=0,c=0;
void ULTRASONIC_Init(void)
{
	Timer1_Init(TIMER1_NORMAL_MODE,OCRA_DISCONNECTED,OCRB_DISCONNECTED);

	setBit(DDRB,ultrasonic_trigrpin);
	
	Timer1_OVF_SetCallBack(Func_OVF);
	Timer1_OVF_SetCallBack(Func_ICU);
	Timer1_OVF_InterruptEnable();
	Timer1_ICU_InterruptEnable();
	sei();
}
u32 ULTRASONIC_GetDistance(void)
{
	
	u32 distance;
	u32 time;
//	c=0;
	
	setBit(PORTB,ultrasonic_trigrpin);            /*set high on triger pin*/
	_delay_us(10);                                 /*wait 10 micro second*/
	clearBit(PORTB,ultrasonic_trigrpin);           /*set low on trigger pin*/
	TCNT1=0;
	Timer1_InputCaptureEdge(RISING);               /*active input cupture whene raising happen*/
	Timer1_Start();
	
	setBit(TIFR ,ICF1);	
    setBit(TIFR ,TOV1);	
	while ((TIFR & (1 << ICF1)) == 0);                    /* Wait for rising edge */
    TCNT1 = 0;                                        	/* Clear Timer counter */
   Timer1_InputCaptureEdge(FALLING);                 /*active input cupture whene raising happen*/
   Timer1_Start();
   
   setBit(TIFR ,ICF1);
   setBit(TIFR ,TOV1);
    c = 0;                                        /* Clear Timer overflow count */
	while ((TIFR & (1 << ICF1)) == 0);            /* Wait for falling edge */

	time = ICR1 +(65535UL * c);                    	/* Take count */
	
	distance = time /(58.30);
	//LCD_DispNumberXY(1,1,distance);
	return distance;
}
/* this func not work yet !!!!!*/
u8 ULTRASONIC_GetDistance2(void)
{
	Timer1_Start();
	u8 distance;
	u16 time;
	//TCNT1=0;
	c=0;
	flag=0;
	setBit(PORTB,ultrasonic_trigrpin);
	_delay_us(10);
	clearBit(PORTB,ultrasonic_trigrpin);
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();
	while (flag<2);
	time=t2-t1+((u32)c*65535);
	distance=time/58;
	LCD_DispNumberXY(2,1,distance);
	Timer1_ICU_InterruptDisable();
	return distance;
	
}

static void Func_ICU(void)
{
	if(flag==0)
	{
		c=0;
		t1=ICR1;
		//LCD_DispNumber(t1);
		flag=1;
		Timer1_InputCaptureEdge(FALLING);
	}
	else if (flag==1)
	{
		t2=ICR1;
		//LCD_DispNumber(t2);
		flag=2;
		Timer1_InputCaptureEdge(RISING);
		Timer1_OVF_InterruptDisable();
		Timer1_ICU_InterruptDisable();
	}
}
static void Func_OVF(void)
{
	c++;
}