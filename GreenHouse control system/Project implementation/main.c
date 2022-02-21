/*
 * AVR_Interfacing.c
 *
 * Created: 7/5/2021 1:41:51 PM
 * Author : MahmoudH
 */ 
#define F_CPU	8000000UL

#include <avr/io.h>
#include "BasicIO.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "LCD.h"
#include "uart.h"
#include "SPI.h"
#include "timer.h"
#include "Green.h"

int main(void)
{
 GHC_init();
 
	
	
    while (1) 
    {
		
		GHC_Run();
		
		
		
		
	    
		
		
		
		
                 
               // x=ULTRASONIC_GetDistance();
				 //dtostrf(x, 2, 2, string);/* distance to string */
				 //strcat(string, " cm   ");	/* Concat unit i.e.cm */
			    //LCD_DispStrXY(2, 1, "Dist = ");
				//LCD_DispStrXY(2, 7, string);	/* Print distance */
				//_delay_ms(200);
				
				
		
	}
}