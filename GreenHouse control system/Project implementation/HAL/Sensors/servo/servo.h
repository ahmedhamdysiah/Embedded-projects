/*
 * servo.h
 *
 * Created: 7/28/2021 03:25:31 PM
 *  Author: mohammed sabry
 */ 


#ifndef SERVO_H_
#define SERVO_H_


#define F_CPU 8000000UL
#include "avr/io.h"
#include "util/delay.h"

void servo_Init(void);
void servo_angle (char angle);


#endif /* SERVO_H_ */