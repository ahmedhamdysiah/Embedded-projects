/*
 * LDR.h
 *
 * Created: 03/08/2021 12:29:30 PM
 *  Author: htaha10
 */ 
#include "avr/io.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "data_types.h"
#include "bit_handle.h"
#include <stdio.h>
#include <stdlib.h>
#include "ADC.h"

#ifndef LDR_H_
#define LDR_H_


u16 LDR_Get_Lux(ADC_Channel channel);

#endif /* LDR_H_ */