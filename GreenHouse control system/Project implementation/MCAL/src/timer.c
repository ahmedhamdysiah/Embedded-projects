/*
* timer.c
*
* Created: 7/12/2021 1:13:04 PM
*  Author: MahmoudH
*/
#include "timer.h"

volatile static u32 overflows = 0;
volatile static u32 calcOverflows = 0;
void (*volatile notifier)(void);
static void (*Timer1_OVF_Fptr) (void);
static void (*Timer1_OCA_Fptr) (void);
static void (*Timer1_OCB_Fptr) (void);
static void (*Timer1_ICU_Fptr) (void);

/* Tick in 1us */
void Timer_Init(Timer_Mode mode){
	Timer_Stop();
	switch(mode){
		case TM_NORMAL:
		clearBit(TCCR0,WGM00);
		clearBit(TCCR0,WGM01);
		setBit(TIMSK,TOIE0); /* enable timer0 overflow int */
		sei();
		break;
		case TM_CTC:
		clearBit(TCCR0,WGM00);
		setBit(TCCR0,WGM01);
		/* Toggle OC0 pin */
		setBit(TCCR0,COM00);
		clearBit(TCCR0,COM01);
		/* OC0 Pin Out */
		setBit(DDRB,PB3);
		/* Set OCR */
		OCR0 = 127;
		Timer_Start();
		break;
		case TM_PHASE_PWM:
		setBit(TCCR0,WGM00);
		clearBit(TCCR0,WGM01);
		/* clear OC0 pin at upcount  match and set on downcount match*/
		clearBit(TCCR0,COM00);
		setBit(TCCR0,COM01);
		/* OC0 Pin Out */
		setBit(DDRB,PB3);
		/* Set OCR */
		OCR0 = 127;
		Timer_Start();
		break;
		case TM_FAST_PWM:
		setBit(TCCR0,WGM00);
		setBit(TCCR0,WGM01);
		/* set OC0 pin at bot and clear on match*/
		clearBit(TCCR0,COM00);
		setBit(TCCR0,COM01);
		/* OC0 Pin Out */
		setBit(DDRB,PB3);
		/* Set OCR */
		OCR0 = 127;
		Timer_Start();
		break;
		default:
		break;
	}
}
void Timer_Start(void){
	clearBits(TCCR0,((1<<CS00)|(1<<CS02)));
	setBit(TCCR0,CS01);
}
void Timer_Stop(void){
	clearBits(TCCR0,((1<<CS00)|(1<<CS01)|(1<<CS02)));
}
void Timer_ResetCounters(void){
	overflows	= 0;
	TCNT0		= 0;
}

void Timer_DelayUS(u32 delay){
	Timer_Stop();
	Timer_ResetCounters();
	Timer_Start();
	while( (overflows*256UL+ TCNT0 + 1) < (delay) );
}
void Timer_DelayMS(u32 delay){
	Timer_Stop();
	Timer_ResetCounters();
	Timer_Start();
	while( (overflows*256UL+ TCNT0 + 1) < (delay*1000UL) );
}
void Timer_SetDuty(u8 duty){
	if (duty >= 100)
	{
		OCR0 = 0xFF;
	}
	else{
		OCR0 = (0xFFUL*duty)/100;
	}
}
void Timer_DecDuty(u8 duty){
	if(OCR0 >= 0xFF*(duty/100.0)){
		OCR0 -= 0xFF*(duty/100.0);
	}
	else{
		OCR0 = 0x00;
	}
}
void Timer_IncDuty(u8 duty){
	if(OCR0 + 0xFF*(duty/100.0) <= 0xFF){
		OCR0 += 0xFF*(duty/100.0);
		}else{
		OCR0 = 0xFF;
	}
}

void Timer_SetNotif(void (*pfNotify)(void),u32 notifyTime){
	Timer_Init(TM_NORMAL);
	notifier = pfNotify;
	//TCNT0 = 256 - ((notifyTime*1000UL)%256 -1);
	overflows = 0;
	calcOverflows = (notifyTime*1000UL)/256;// +1;
	Timer_Start();
}
/********************timer1****************/
void Timer1_Init(Timer1Mode_type mode,OC1A_Mode_type oc1_mode,OC1B_Mode_type oc1b_mode)
{
	switch (mode)
	{
		case TIMER1_NORMAL_MODE:
		clearBit(TCCR1A,WGM10);
		clearBit(TCCR1A,WGM11);
		clearBit(TCCR1B,WGM12);
		clearBit(TCCR1B,WGM13);
		break;
		case TIMER1_CTC_ICR_TOP_MODE:
		clearBit(TCCR1A,WGM10);
		clearBit(TCCR1A,WGM11);
		setBit(TCCR1B,WGM12);
		setBit(TCCR1B,WGM13);
		break;
		
		case TIMER1_CTC_OCRA_TOP_MODE:
		clearBit(TCCR1A,WGM10);
		clearBit(TCCR1A,WGM11);
		setBit(TCCR1B,WGM12);
		clearBit(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_ICR_TOP_MODE:
		clearBit(TCCR1A,WGM10);
		setBit(TCCR1A,WGM11);
		setBit(TCCR1B,WGM12);
		setBit(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		setBit(TCCR1A,WGM10);
		setBit(TCCR1A,WGM11);
		setBit(TCCR1B,WGM12);
		setBit(TCCR1B,WGM13);
		break;
	}
	switch (oc1_mode)
	{
		case OCRA_DISCONNECTED:
		clearBit(TCCR1A,COM1A0);
		clearBit(TCCR1A,COM1A1);
		break;
		case OCRA_TOGGLE:
		setBit(TCCR1A,COM1A0);
		setBit(TCCR1A,COM1A1);
		break;
		case OCRA_NON_INVERTING:
		clearBit(TCCR1A,COM1A0);
		setBit(TCCR1A,COM1A1);
		break;
		case OCRA_INVERTING:
		setBit(TCCR1A,COM1A0);
		setBit(TCCR1A,COM1A1);
		break;
	}
	switch (oc1b_mode)
	{
		case OCRB_DISCONNECTED:
		clearBit(TCCR1A,COM1B0);
		clearBit(TCCR1A,COM1B1);
		break;
		case OCRB_TOGGLE:
		setBit(TCCR1A,COM1B0);
		clearBit(TCCR1A,COM1B1);
		break;
		case OCRB_NON_INVERTING:
		clearBit(TCCR1A,COM1B0);
		setBit(TCCR1A,COM1B1);
		break;
		case OCRB_INVERTING:
		setBit(TCCR1A,COM1B0);
		setBit(TCCR1A,COM1B1);
		break;
	}
		
		
}

void Timer1_Start(void)
{
	clearBits(TCCR1B,((1<<CS11)|(1<<CS12)));
	setBit(TCCR1B,CS10);
}
void Timer1_Stop(void)
{
	clearBits(TCCR1B,((1<<CS00)|(1<<CS01)|(1<<CS02)));
	
}
void Timer1_InputCaptureEdge(ICU_Edge_type edge)
{
	if(edge==RISING)
	setBit(TCCR1B,ICES1);
	
	else if(edge==FALLING)
	clearBit(TCCR1B,ICES1);

}
void Timer1_ICU_InterruptEnable(void)
{
	setBit(TIMSK,TICIE1);
}
void Timer1_ICU_InterruptDisable(void)
{
	clearBit(TIMSK,TICIE1);
}
void Timer1_OVF_InterruptEnable(void)
{
	setBit(TIMSK,TOIE1);
}
void Timer1_OVF_InterruptDisable(void)
{
		clearBit(TIMSK,TOIE1);
}
void Timer1_OCA_InterruptEnable(void)
{
	setBit(TIMSK,OCIE1A);
}
void Timer1_OCA_InterruptDisable(void)
{
	clearBit(TIMSK,OCIE1A);
}
void Timer1_OCB_InterruptEnable(void)
{
	setBit(TIMSK,OCIE1B);
}
void Timer1_OCB_InterruptDisable(void)
{
	clearBit(TIMSK,OCIE1B);
}
/******************timer1callback*************/
void Timer1_OVF_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OVF_Fptr=LocalFptr;
}
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCA_Fptr=LocalFptr;
}
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCB_Fptr=LocalFptr;
}
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_ICU_Fptr=LocalFptr;
}
ISR(TIMER1_OVF_vect)
{
	if(Timer1_OVF_Fptr!=NULLPTR )
	{
		Timer1_OVF_Fptr();
	}
}
ISR(TIMER1_COMPA_vect)
{
	if(Timer1_OCA_Fptr!=NULLPTR )
	{
		Timer1_OCA_Fptr();
	}
}
ISR(TIMER1_COMPB_vect)
{
	if(Timer1_OCB_Fptr!=NULLPTR )
	{
		Timer1_OCB_Fptr();
	}
}
ISR(TIMER1_CAPT_vect)
{
	if(Timer1_ICU_Fptr!=NULLPTR )
	{
		Timer1_ICU_Fptr();
	}
}

ISR(TIMER0_OVF_vect){
	overflows++;
	if(overflows == calcOverflows){
		notifier();
		Timer_Stop();
	}
}