/*
 * LCD_20x4.c
 *
 * Created: 7/26/2021 6:03:11 PM
 *  Author: UNO
 */ 
#include "LCD_20x4.h"


static void LCD_sendCMD(u8 u8CMD);
static void LCD_sendData(u8 u8Data);
static void LCD_GoToXY(u8	row, u8 col);
static void LCD_Latch(void);
void LCD_Init(void){
	//out 
	setBits(LCD_DATA_DDR,LCD_DATA_MSK);
	setBit(LCD_CTRL_DDR,LCD_RS_PIN);
	setBit(LCD_CTRL_DDR,LCD_EN_PIN);
	_delay_ms(20);
	LCD_sendCMD(CMD_FUN_SET_4BIT);	/*Required: to set 4Bit operation */
	LCD_sendCMD(CMD_CFG);			
	LCD_sendCMD(CMD_DISP_ON);
	LCD_sendCMD(CMD_ENTRY_MODE);
	LCD_Clear();
}
void LCD_Clear(void){
	LCD_sendCMD(CMD_CLEAR);
	_delay_ms(5);
}

void LCD_DispChar(u8 u8Char){
	LCD_sendData(u8Char);
}
void LCD_DispStr(u8 *pu8Str){
	while (*pu8Str)
	{
		LCD_sendData(*pu8Str);
		pu8Str++;
	}
	/*u8 i=0;
	while(pu8Str[i]!='\0'){
		LCD_DispChar(pu8Str[i]);
		i++;
	}*/
}
void LCD_DispInt(u32 pu8Int){
	u8 data_dig[7];
	for (int i=(sizeof(data_dig)-1);i>=0;i--){
	data_dig[i]=pu8Int%10;
	pu8Int-=data_dig[i];
	pu8Int/=10;	
	}
	
	Bool flag=TRUE;
	for(int i=0;i<sizeof(data_dig)&&flag;i++){
		int j=i;
		for(;j<sizeof(data_dig)&&data_dig[i];j++){
			LCD_sendData(data_dig[j]+'0');
			flag=FALSE;
		}
	}
	if (flag){
		LCD_sendData(data_dig[sizeof(data_dig)-1]+'0');
	}
}

//row :1/2	- col 1-16
void LCD_DispCharXY(u8 row ,u8 col,u8 u8Char){
	LCD_GoToXY(row,col);
	LCD_DispChar(u8Char);
}
void LCD_DispStrXY(u8 row , u8 col,u8* pu8Str){
	LCD_GoToXY(row,col);
	LCD_DispStr(pu8Str);
}
void LCD_DispIntXY(u8 row , u8 col,u32 pu8Int){
	LCD_GoToXY(row,col);
	LCD_DispInt(pu8Int);
}

static void LCD_sendCMD(u8 u8CMD){
	// RS =0: COMMAND 
	clearBit(LCD_CTRL_PORT,LCD_RS_PIN);
	// UPLOAD MOST 4 BIT AND THEN LATCH
	LCD_DATA_Reg.HN = ((u8CMD)>>4);
	LCD_Latch();
	// UPLOAD least 4 BIT AND THEN LATCH
	LCD_DATA_Reg.HN = u8CMD;
	LCD_Latch();
	//delay 40 us 
	_delay_us(40);
}
static void LCD_sendData(u8 u8Data){
	// RS =1: COMMAND
	setBit(LCD_CTRL_PORT,LCD_RS_PIN);
	// UPLOAD MOST 4 BIT AND THEN LATCH
	LCD_DATA_Reg.HN = (u8Data)>>4;
	LCD_Latch();
	// UPLOAD least 4 BIT AND THEN LATCH
	LCD_DATA_Reg.HN = u8Data;
	LCD_Latch();
	//delay 40 us
	_delay_us(40);
}
static void LCD_GoToXY(u8	row, u8 col){
	if (row ==1)
	{
		LCD_sendCMD((0x80) + col -1);
	}
	else if (row ==2)
	{
		LCD_sendCMD((0xC0) + col -1);
	}
	else if (row ==3)
	{
		LCD_sendCMD((0x94) + col -1);
	}
	else{
		LCD_sendCMD((0xD4) + col -1);
	}
}
static void LCD_Latch(void){
	setBit(LCD_CTRL_PORT,LCD_EN_PIN);
	_delay_us(1);
	clearBit(LCD_CTRL_PORT,LCD_EN_PIN);
}

