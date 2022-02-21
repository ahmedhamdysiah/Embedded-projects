/*
 * TH2.h
 *
 * Created: 03/08/2021 08:46:53 PM
 *  Author: htaha10
 */ 


#ifndef TH2_H_
#define TH2_H_

#define F_CPU      8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "data_types.h"
#include "bit_handle.h"
#include <stdlib.h>


#define TH2_STATUS			0x00
#define CTRL_REG			0x03
#define TH2_Write_ADD		0x80
#define TH2_READ_ADD		0x81	
#define DATA_HUM			0x01
#define DATA_TEMP			0x11
#define TH2_RDY				0x00
#define TH2_NOTRDY			0x01
#define DATA_READ			0x01

void TH2_Init(void);
u16  TH2_Read_Relative_Temp(void);
u16  TH2_Read_Relative_HUM(void);
void TH2_Calculate_Temp(u16* Un_Temp,s8* Real_Temp);
void TH2_Calculate_HUM(u16* Un_HUM,u8* Real_HUM);
s8 Get_Temp (void);
u8 Get_HUMIDITY (void);




#endif /* TH2_H_ */