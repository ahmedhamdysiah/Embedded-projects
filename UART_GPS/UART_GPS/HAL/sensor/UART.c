/*
 * UART.c
 *
 * Created: 7/27/2021 1:06:33 AM
 *  Author: UNO
 */ 

#include "uart.h"
#include "GPS.h"
#define SREG    _SFR_IO8(0x3f)
Bool	_IsItGGAString	= FALSE;
/*default : 8N1*/
void Uart_Init(u32 baudRate){
	/*BR =(clock/(16*baud))-1*/
	u32 BRValue = (F_CPU/(16UL*baudRate))-1;
	/*set baud rate */
	
	UBRRH = (u8) (BRValue>>8);
	UBRRL = (u8) (BRValue);
	/*Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	/*Set frame format : 8data */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
	
	
}
void Uart_SendByate(u8 data){
	/*Wait for empty transmit buffer*/
	while (!(UCSRA &(1<<UDRE)));
	/*Put data into buffer , sends the data */
	UDR =data;
}
void Uart_ReceivedByate(u8* pData){
	/*Wait for data to be received */
	while (!(UCSRA & (1<<RXC)));
	/*Get and return received data from buffer */
	(*pData) = UDR;
}
Bool Uart_ReceivedByate_Unblock(u8* pData){
	Bool result;
	if (UCSRA & (1<<RXC)){
		result= TRUE;
		(*pData) = UDR;
	}
	else{
		result= FALSE;
	}
	return result;
}
void Uart_SendStr(u8* str){
	u32 ind =0;
	while (str[ind]!=0){
		Uart_SendByate(str[ind]);
		ind ++;
	}
}
ISR(USART_RXC_vect)
{
	
	
	u8 oldsrg = SREG;
	cli();
	char received_char = UDR;
	
	if(received_char =='$'){                 /* check for '$' */
		GGA_Index = 0;
		CommaCounter = 0;
		_IsItGGAString = FALSE;
	}
	else if(_IsItGGAString == TRUE){          /* if true save GGA info. into buffer */
		if(received_char == ',' ) GGA_Pointers[CommaCounter++] = GGA_Index;     /* store instances of ',' in buffer */
		GGA_Buffer[GGA_Index++] = received_char;
	}
	else if(GGA_CODE[0] == 'G' && GGA_CODE[1] == 'G' && GGA_CODE[2] == 'A'){    /* check for GGA string */
		_IsItGGAString = TRUE;
		GGA_CODE[0] = 0; GGA_CODE[1] = 0; GGA_CODE[2] = 0;
	}
	else{
		GGA_CODE[0] = GGA_CODE[1];  GGA_CODE[1] = GGA_CODE[2]; GGA_CODE[2] = received_char;
	}
	SREG = oldsrg;
}
