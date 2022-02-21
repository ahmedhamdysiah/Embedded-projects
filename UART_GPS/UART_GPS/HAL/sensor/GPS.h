/*
 * GPS.h
 *
 * Created: 7/26/2021 6:00:43 PM
 *  Author: UNO
 */ 


#ifndef GPS_H_
#define GPS_H_
#define F_CPU	8000000UL
#define SREG    _SFR_IO8(0x3f)

#include <avr/io.h>
#include "bit_handle.h"
#include "util\delay.h"
#include "DATA_TYPES.h"
#include "avr\interrupt.h"
#include "string.h"


#define Buffer_Size 150
#define degrees_buffer_size 20

u8	Latitude_Buffer[15],
	Longitude_Buffer[15],
	Time_Buffer[15],
	Altitude_Buffer[8],
	N_of_Sat_Buffer[8];

u8 degrees_buffer[degrees_buffer_size];   /* save latitude or longitude in degree */
u8 GGA_Buffer[Buffer_Size];               /* save GGA string */
u8 GGA_Pointers[20];                   /* to store instances of ',' */
u8 GGA_CODE[3];

volatile u16	GGA_Index,
				CommaCounter;


void get_gpstime(void);
void get_latitude(u8 lat_pointer);
void get_longitude(u8 long_pointer);
void get_altitude(u8 alt_pointer);
void get_N_of_Sat(u8 N_of_Sat_pointer);



#endif /* GPS_H_ */