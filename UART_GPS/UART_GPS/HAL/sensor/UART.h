/*
 * UART.h
 *
 * Created: 7/27/2021 1:06:14 AM
 *  Author: UNO
 */ 


#ifndef UART_H_
#define UART_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include "util\delay.h"
#include "avr/interrupt.h"
#include "bit_handle.h"
#include "DATA_TYPES.h"

void Uart_Init(u32 baudRate);
void Uart_SendByate(u8 data);
void Uart_ReceivedByate(u8* pData);
Bool Uart_ReceivedByate_Unblock(u8* pData);
void Uart_SendStr(u8* str);







#endif /* UART_H_ */