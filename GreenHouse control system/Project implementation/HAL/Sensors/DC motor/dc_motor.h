/*
 * dc_motor.h
 *
 * Created: 8/4/2021 11:26:09 AM
 *  Author: M
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "avr/io.h"
#include "util/delay.h"
#include "data_types.h"
#include "bit_handle.h"
#define DCMotor_DDR       DDRD
#define DCMotor_PORT      PORTD
#define DC_mask           0xc0
#define DCMotor_PIN       PD6
#define DCMotor_EnPIN     PD7


void DC_init(void);
void DC_ON(void);
void DC_OFF(void);





#endif /* DC_MOTOR_H_ */