/*
 * timer.h
 *
 * Created: 7/12/2021 1:12:48 PM
 *  Author: MahmoudH
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#define F_CPU	8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "bit_handle.h"
#include "data_types.h"

typedef enum{
	TM_NORMAL,TM_CTC,TM_PHASE_PWM,TM_FAST_PWM
}Timer_Mode;
typedef enum{
	RISING,
	FALLING
}ICU_Edge_type;

/* Tick in 1us */
void Timer_Init(Timer_Mode mode);
void Timer_Start(void);
void Timer_Stop(void);
void Timer_ResetCounters(void);

void Timer_DelayUS(u32 delay);
void Timer_DelayMS(u32 delay);

/* Set, inc, dec */
void Timer_SetDuty(u8 duty);
void Timer_DecDuty(u8 duty);
void Timer_IncDuty(u8 duty);

void Timer_SetNotif(void (*pfNotify)(void),u32 notifyTime);


/*timer1*/
typedef enum
{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE

}Timer1Mode_type;
typedef enum
{
	OCRA_DISCONNECTED=0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING

}OC1A_Mode_type;

typedef enum
{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING

}OC1B_Mode_type;
void Timer1_Init(Timer1Mode_type mode,OC1A_Mode_type oc1_mode,OC1B_Mode_type oc1b_mode);
void Timer1_Start(void);
void Timer1_Stop(void);

void Timer1_InputCaptureEdge(ICU_Edge_type edge);
void Timer1_ICU_InterruptEnable(void);
void Timer1_ICU_InterruptDisable(void);
void Timer1_OVF_InterruptEnable(void);
void Timer1_OVF_InterruptDisable(void);
void Timer1_OCA_InterruptEnable(void);
void Timer1_OCA_InterruptDisable(void);
void Timer1_OCB_InterruptEnable(void);
void Timer1_OCB_InterruptDisable(void);
void Timer1_OVF_SetCallBack(void(*LocalFptr)(void));
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void));
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void));
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void));


#endif /* TIMER_H_ */