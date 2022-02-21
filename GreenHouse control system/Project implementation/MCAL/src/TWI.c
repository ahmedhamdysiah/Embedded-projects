/*
 * TWI.c
 *
 * Created: 26/07/2021 03:05:32 PM
 *  Author: htaha10
 */ 
#include "TWI.h"
#include "LCD.h"
#include "bit_handle.h"


void TWI_Init (u32 scl){
	TWBR = ((F_CPU/scl) - 16)/2;
	TWSR=0;
}
Bool TWI_Start (void){
	Bool result = FALSE;
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	TWI_Wait();
	if((TWSR&0XF8) == SC_START){
		result = TRUE;
	}
	return result;
}
Bool TWI_Restart(void){
	Bool result = FALSE;
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	TWI_Wait();
	if((TWSR&0XF8) == SC_Restart){
		result = TRUE;
	}
	return result;
}
void TWI_Stop (void){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while ((TWCR & (1 << TWSTO)));
}
void TWI_Wait (void){
	while (!(TWCR&(1<<TWINT)));	
}

Bool TWI_Write(u8 u8Byte,u8 sCode){
	TWDR = u8Byte;
	TWCR = (1<<TWINT) | (1<<TWEN);
	TWI_Wait();
	return ;
}

u8 TWI_Read_ACK (){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);	
	TWI_Wait();
	return TWDR;
	
}
 u8 TWI_Read_NOACK (){
	TWCR = (1<<TWINT) | (1<<TWEN);
	TWI_Wait();
	return TWDR;
}













