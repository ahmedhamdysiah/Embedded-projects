/*
 * keypad.h
 *
 * Created: 7/7/2021 1:16:41 PM
 *  Author: MahmoudH
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU	8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "bit_handle.h"
#include "data_types.h"

/* CFG Start */

#define KEY_ROWS_PORT	PORTC
#define KEY_ROWS_DDR	DDRC
#define KEY_ROWS_MSK	0x0F

#define KEY_COLS_PORT	PORTA
#define KEY_COLS_DDR	DDRA
#define KEY_COLS_PINR	PINA
#define KEY_COLS_MSK	0x0F
/* CFG End */

void	Key_Init(void);
u8		Key_GetKey(void);
#endif /* KEYPAD_H_ */