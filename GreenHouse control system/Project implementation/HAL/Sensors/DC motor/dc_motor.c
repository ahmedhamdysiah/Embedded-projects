/*
 * dc_motor.c
 *
 * Created: 8/4/2021 11:26:36 AM
 *  Author: M
 */ 
#include "dc_motor.h"
void DC_init(void)
{
	setBits(DCMotor_DDR,DC_mask);
	setBit(DCMotor_PORT,DCMotor_EnPIN);
	
}
void DC_ON(void)
{
	setBit(DCMotor_PORT,DCMotor_PIN);
}
void DC_OFF(void)
{
	clearBit(DCMotor_PORT,DCMotor_PIN);
}
