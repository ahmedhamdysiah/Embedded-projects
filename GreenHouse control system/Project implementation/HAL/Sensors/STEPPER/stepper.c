/*
 * stepper.c
 *
 * Created: 8/3/2021 10:37:16 PM
 *  Author: M
 */ 
#include "stepper.h"
void valvInit (void)
{
	setBits(stepperDDR,stepperMask);
	clearBits(stepperPort,stepperMask);
	
}
void valvOff  (void)
{
	setBit(stepperPort,angle0_PIN );
	clearBit(stepperPort,angle90_PIN);
}
void valvOn   (void)
{
	setBit(stepperPort,angle90_PIN);
	clearBit(stepperPort,angle0_PIN);
}
