/*
 * ultrasonic.h
 *
 * Created: 7/26/2021 7:31:32 PM
 *  Author: M
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define F_CPU	8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "bit_handle.h"
#include "data_types.h"
#include "timer.h"
#define triger_PORT PORTB
#define triger_DDR  DDRB
#define ultrasonic_trigrpin   PB7

void ULTRASONIC_Init(void);
u32 ULTRASONIC_GetDistance(void);
u8 ULTRASONIC_GetDistance2(void);

#endif /* ULTRASONIC_H_ */