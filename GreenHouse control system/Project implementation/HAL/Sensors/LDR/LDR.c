/*
 * LDR.c
 *
 * Created: 03/08/2021 12:29:44 PM
 *  Author: htaha10
 */ 
#include "LDR.h"
#include "ADC.h"
#include "LCD.h"

u16 LDR_Get_Lux(ADC_Channel channel){
	
	u16 LDR_Value = ADC_Read(channel);
	
	return (100-(((LDR_Value -49)/(965.0))*100));
	
	
}
