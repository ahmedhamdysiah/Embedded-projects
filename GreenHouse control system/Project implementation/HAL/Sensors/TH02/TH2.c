/*
 * TH2.c
 *
 * Created: 03/08/2021 08:47:06 PM
 *  Author: htaha10
 */ 
#include "TH2.h"
#include "LCD.h"
#include "TWI.h"
#include "avr/io.h"

void TH2_Init(void){
	TWI_Init(2000000UL);
	TWI_Start();
	TWI_Write(TH2_Write_ADD,SC_MT_SLAW_ACK);
	TWI_Write(CTRL_REG,SC_MT_DATA_ACK);
	TWI_Write(DATA_HUM,SC_MT_DATA_ACK);
	_delay_ms(35);
	TWI_Write(DATA_TEMP,SC_MT_DATA_ACK);
	_delay_ms(35);
	TWI_Stop();	
}
u16 TH2_Read_Relative_Temp(void){
	TWI_Start();
	TWI_Write(TH2_Write_ADD,SC_MT_SLAW_ACK);
	TWI_Write(CTRL_REG,SC_MT_DATA_ACK);
	TWI_Write(DATA_TEMP,SC_MR_SLAR_ACK);
	_delay_ms(35);
	TWI_Stop();
	TWI_Start();
	TWI_Write(TH2_Write_ADD,SC_MT_SLAW_ACK);
	TWI_Write(DATA_READ,SC_MT_DATA_ACK);
	TWI_Restart();
	TWI_Write(TH2_READ_ADD,SC_MR_SLAR_ACK);
	u8 MSB= TWI_Read_ACK();
	u8 LSB= TWI_Read_NOACK();
	TWI_Stop();
	u16 Full_Bits = 0;
	Full_Bits |= ((u16)MSB << 8) | LSB;
	Full_Bits = Full_Bits >> 2 ;
	return Full_Bits;
}
u16 TH2_Read_Relative_HUM(void){
	TWI_Start();
	TWI_Write(TH2_Write_ADD,SC_MT_SLAW_ACK);
	TWI_Write(CTRL_REG,SC_MT_DATA_ACK);
	TWI_Write(DATA_HUM,SC_MR_SLAR_ACK);
	_delay_ms(35);
	TWI_Stop();
	TWI_Start();
	TWI_Write(TH2_Write_ADD,SC_MT_SLAW_ACK);
	TWI_Write(DATA_READ,SC_MT_DATA_ACK);
	TWI_Restart();
	TWI_Write(TH2_READ_ADD,SC_MR_SLAR_ACK);
	u8 MSB= TWI_Read_ACK();
	u8 LSB= TWI_Read_NOACK();
	TWI_Stop();
	u16 Full_Bits = 0;
	Full_Bits |= ((u16)MSB << 8) | LSB;
	Full_Bits = Full_Bits >> 4 ;
	return Full_Bits;
}
void TH2_Calculate_Temp(u16* Un_Temp,s8* Real_Temp){
	*Real_Temp = (*Un_Temp / 32)-50 ;
	
}
void TH2_Calculate_HUM(u16* Un_HUM,u8* Real_HUM){
	*Real_HUM = (*Un_HUM / 16)-24;
}
s8 Get_Temp(void){
	u16 Uncompensated_Temp ;
	s8 True_Temp ;
	Uncompensated_Temp = TH2_Read_Relative_Temp();
	TH2_Calculate_Temp(&Uncompensated_Temp,&True_Temp);
	return True_Temp ;	
}
u8 Get_HUMIDITY (void){
	u16 Uncompensated_Humidity ;
	u8 True_Humidity ;
	Uncompensated_Humidity = TH2_Read_Relative_HUM();
	TH2_Calculate_HUM(&Uncompensated_Humidity,&True_Humidity);
	return True_Humidity ;
}

