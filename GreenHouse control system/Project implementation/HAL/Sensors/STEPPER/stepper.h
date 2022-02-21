/*
 * stepper.h
 *
 * Created: 8/3/2021 10:37:38 PM
 *  Author: M
 */ 


#ifndef STEPPER_H_
#define STEPPER_H_

#define F_CPU	8000000UL
#include "avr/io.h"
#include "bit_handle.h"
#include "data_types.h"
#define stepperDDR    DDRB
#define stepperPort   PORTB
#define stepperMask   0xf0

#define angle0_PIN          5
#define angle90_PIN         4
void valvInit (void);
void valvOff  (void);
void valvOn   (void);




#endif /* STEPPER_H_ */