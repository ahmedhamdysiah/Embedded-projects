/*
 * uart.h
 *
 * Created: 7/14/2021 10:44:38 AM
 *  Author: MahmoudH
 */ 


#ifndef UART_H_
#define UART_H_

#define F_CPU	8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "bit_handle.h"
#include "data_types.h"

void	Uart_Init(u32 baudRate);
void	Uart_SendByte(u8 data);
void	Uart_ReceiveByte(u8* pData);
Bool	Uart_ReceiveByte_Unblock(u8* pData);
void	Uart_SendStr(u8* str);



#endif /* UART_H_ */