/*
 * TWI.h
 *
 * Created: 26/07/2021 03:05:15 PM
 *  Author: htaha10
 */ 


#ifndef TWI_H_
#define TWI_H_

#define F_CPU      8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "data_types.h"
#include "bit_handle.h"
/* Control Status Codes */
#define SC_START			0x08
#define SC_Restart			0x10
/* Master Transmit Codes */
#define SC_MT_SLAW_ACK		0x18
#define SC_MT_SLAW_NOACK	0x20
#define SC_MT_DATA_ACK		0x28
#define SC_MT_DATA_NOACK	0x30
/* Master Receive Codes */
#define SC_MR_SLAR_ACK		0x40
#define SC_MR_SLAR_NOACK	0x48
#define SC_MR_DATA_ACK		0x50
#define SC_MR_DATA_NOACK	0x58


void TWI_Init (u32 scl);
Bool TWI_Start (void);
Bool TWI_Restart(void);
void TWI_Stop (void);
void TWI_Wait (void);

Bool TWI_Write(u8 u8Byte,u8 sCode);
u8 TWI_Read_ACK ();
u8 TWI_Read_NOACK ();









#endif /* TWI_H_ */