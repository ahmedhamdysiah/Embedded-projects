/*
 * LCD_20x4.h
 *
 * Created: 7/26/2021 6:01:49 PM
 *  Author: UNO
 */ 


#ifndef LCD_20X4_H_
#define LCD_20X4_H_
#define F_CPU 8000000UL
#include <avr/io.h>
#include "bit_handle.h"
#include "util\delay.h"
#include "DATA_TYPES.h"

//CFG START
#define LCD_DATA_PORT	PORTA
#define LCD_DATA_DDR	DDRA
#define LCD_DATA_MSK	0XF0

#define LCD_CTRL_PORT	PORTB
#define LCD_CTRL_DDR	DDRB
#define LCD_EN_PIN		PB0
#define LCD_RS_PIN		PB1
//CFG END

//COMMANDS
#define	CMD_CLEAR			0X01
#define CMD_ENTRY_MODE		0X06
#define CMD_DISP_ON			0X0C
#define CMD_CFG				0X28
#define CMD_FUN_SET_4BIT	0x02
typedef struct{
	u8 LN:4;
	u8 HN:4;
}LCD_DATA_Struct;
#define LCD_DATA_Reg		(*((volatile LCD_DATA_Struct*)(&LCD_DATA_PORT)))

//Functions
void LCD_Init(void);
void LCD_Clear(void);
void LCD_DispChar(u8 u8Char);
void LCD_DispStr(u8 *pu8Str);
void LCD_DispInt(u32 pu8Int);
//row :1-4	- col 1-20
void LCD_DispCharXY(u8 row ,u8 col,u8 u8Char);
void LCD_DispStrXY(u8 row , u8 col,u8* pu8Str);
void LCD_DispIntXY(u8 row , u8 col,u32 pu8Int);





#endif /* LCD_20X4_H_ */