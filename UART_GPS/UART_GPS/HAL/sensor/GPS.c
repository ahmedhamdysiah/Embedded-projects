/*
 * GPS.c
 *
 * Created: 7/26/2021 6:01:00 PM
 *  Author: UNO
 */ 
#include "GPS.h"
#include "stdio.h"
#include "stdlib.h"

static void convert_time_to_UTC();
static void convert_to_degrees(u8 *raw,u8 *dir);
static u8 dir_Long_Buffer[2];
static u8 dir_Lat_Buffer[2];

void get_gpstime(){
	cli();
	u8 time_index=0;

	/* parse Time in GGA string stored in buffer */
	for(int index = 0;index<7; index++){
		
		Time_Buffer[time_index] = GGA_Buffer[index];
		time_index++;
	}
	convert_time_to_UTC();
	sei();
}
void get_latitude(u8 lat_pointer){
	cli();
	u8 lat_index;
	u8 index = lat_pointer+1;
	lat_index=0;
	
	/* parse Latitude in GGA string stored in buffer */
	for(;GGA_Buffer[index]!=',';index++){
		Latitude_Buffer[lat_index]= GGA_Buffer[index];
		lat_index++;
	}
	
	dir_Lat_Buffer[0]	= GGA_Buffer[index++];
	dir_Lat_Buffer[1]   = GGA_Buffer[index];  /* get direction */
	memset(dir_Long_Buffer,0,2);
	convert_to_degrees(Latitude_Buffer,dir_Lat_Buffer);
	sei();
}
void get_longitude(u8 long_pointer){
	cli();
	u8 long_index;
	u8 index = long_pointer+1;
	long_index=0;
	
	/* parse Longitude in GGA string stored in buffer */
	for( ; GGA_Buffer[index]!=','; index++){
		Longitude_Buffer[long_index]= GGA_Buffer[index];
		long_index++;
	}
	
	dir_Long_Buffer[0]	 = GGA_Buffer[index++];
	dir_Long_Buffer[1]   = GGA_Buffer[index]; /* get direction */
	convert_to_degrees(Longitude_Buffer,dir_Long_Buffer);
	sei();
}

void get_altitude(u8 alt_pointer){
	cli();
	u8 alt_index;
	u8 index = alt_pointer+1;
	alt_index=0;
	/* parse Altitude in GGA string stored in buffer */
	for( ; GGA_Buffer[index]!=','; index++){
		Altitude_Buffer[alt_index]= GGA_Buffer[index];
		alt_index++;
	}
	
	Altitude_Buffer[alt_index] = GGA_Buffer[index+1];
	sei();
}
void get_N_of_Sat(u8 N_of_Sat_pointer){
	cli();
	u8 Sat_index;
	u8 index = N_of_Sat_pointer+1;
	Sat_index=0;
	/* parse Altitude in GGA string stored in buffer */
	for( ; GGA_Buffer[index]!=','; index++){
		N_of_Sat_Buffer[Sat_index]= GGA_Buffer[index];
		Sat_index++;
	}
	
	sei();
}
static void convert_time_to_UTC()
{
	int hour, min, sec;
	long Time_value;
	Time_value = atol(Time_Buffer);       /* convert string to integer */
	//LCD_DispInt(Time_value);
	hour = (Time_value / 10000UL);          /* extract hour from integer */
	min  = (Time_value % 10000UL) / 100UL;    /* extract minute from integer */
	sec  = (Time_value % 10000UL) % 100;    /* extract second from integer*/

	sprintf(Time_Buffer, "%d:%d:%d", hour,min,sec);
	
}


static void convert_to_degrees(u8 *raw,u8 *dir){
	
	double value;
	float decimal_value,temp;
	
	int32_t degrees;
	
	float position;
	value = atof(raw);    /* convert string into float for conversion */
	
	/* convert raw latitude/longitude into degree format */
	decimal_value = (value/100);
	degrees       = (int)(decimal_value);
	temp          = (decimal_value - (int)decimal_value)/0.6;
	position      = (float)degrees + temp;
	
	dtostrf(position, 6, 4, degrees_buffer);  /* convert float value into string */
	strcat(degrees_buffer,dir);
}