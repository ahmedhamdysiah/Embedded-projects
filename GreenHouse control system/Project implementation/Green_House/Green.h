/*
 * Green.h
 *
 * Created: 8/4/2021 12:46:15 PM
 *  Author: M
 */ 


#ifndef GREEN_H_
#define GREEN_H_

#define F_CPU	8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "bit_handle.h"
#include "data_types.h"
#include "BasicIO.h"
#include "LDR.h"
#include "LCD.h"
#include "servo.h"
#include "TH2.h"
#include "ADC.h"
#include "dc_motor.h"
#include "stepper.h"
#include "MQTT.h"
#include "uart.h"
#include "string.h"
/*    GFS    */

#define  LRL     30
#define  LRH     70
#define  Tt      45
#define  Th      50

#define LCD_LDR_L1     "LDR:    LED:    "
#define LCD_LDR_L2     "SERVO angle:    "
#define LCD_temp_L1    " c=    Fan:     "
#define LCD_temp_L2    "     Tt:        "
#define LCD_Humdity_L1   "h=    Valve:    "
#define LCD_Humdity_L2   "     Th:        "

#define DISP_IND_LDR		5
#define DISP_IND_LED		13
#define DISP_IND_SERVO		13
#define DISP_IND_C			4
#define DISP_IND_Fan		12
#define DISP_IND_Tt			9
#define DISP_IND_h			3
#define DISP_IND_Valve		13
#define DISP_IND_th			9

typedef enum{
	
	Display_LDR=0,Display_Temp,Display_Humd,Display_Non,
	
}Display_State;

 

/*    GFE   */


void GHC_init(void);
void GHC_Run(void);




#endif /* GREEN_H_ */