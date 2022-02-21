/*
 * UART_GPS.c
 *
 * Created: 7/26/2021 5:59:18 PM
 * Author : UNO
 */ 

#include <avr/io.h>
#include "LCD_20x4.h"
#include "Data_Types.h"
#include "bit_handle.h"
#include "GPS.h"
#include "UART.h"
#include "string.h"

int main(void)
{
	GGA_Index=0;
	memset(GGA_Buffer, 0, Buffer_Size);
	memset(degrees_buffer,0,degrees_buffer_size);
	LCD_Init();
	LCD_DispStr("Ahmed ");
	_delay_ms(3000);
	Uart_Init(9600);
	sei();
    while (1) 
    {
			_delay_ms(500);
			LCD_DispStrXY(1,1,"UTC Time: ");
			get_gpstime();                   /* Extract Time in UTC */
			LCD_DispStr(&Time_Buffer);
			LCD_DispStr("  ");
			
			LCD_DispStrXY(2,1,"Lat: ");
			get_latitude(GGA_Pointers[0]);   /* Extract Latitude */
			LCD_DispStr(degrees_buffer);      /* display latitude in degree */
			memset(degrees_buffer,0,degrees_buffer_size);
			LCD_DispStr("     ");
			
			LCD_DispStrXY(3,1,"Long: ");
			get_longitude(GGA_Pointers[2]);  /* Extract Longitude */
			LCD_DispStr(degrees_buffer);      /* display longitude in degree */
			memset(degrees_buffer,0,degrees_buffer_size);
			LCD_DispStr("     ");
			
			LCD_DispStrXY(4,1,"Alt: ");
			get_altitude(GGA_Pointers[7]);   /* Extract Altitude in meters*/
			LCD_DispStr(Altitude_Buffer);
			LCD_DispStr("          ");
			
			_delay_ms(500);
			LCD_DispStrXY(4,1,"No. of Sat.: ");
			get_N_of_Sat(GGA_Pointers[5]);   /* Extract Number of Stalait*/
			LCD_DispStr(N_of_Sat_Buffer);
			LCD_DispStr("          ");
			
    }
}

