/*
 * Green.c
 *
 * Created: 8/4/2021 12:46:44 PM
 *  Author: M
 */ 
#include "Green.h"
u8 LDR=0;
s8 c=0;
u8 h=0;

Display_State Disp=Display_LDR;
Display_State prev_state=Display_Non;
u8 counter=0;
u8 *LEDstate[3];
u8 *servoState[2];
u8 *FanState[3];
u8 *valve[3];
u8 minusC_Disp[10];
u8 messges[200]={"Welcome to Green House System"};



void GHC_init(void)
{
	ADC_Init();
	servo_Init();
	Led_Init(LED6);
	TH2_Init();
	DC_init();
	valvInit();
	LCD_Init();
	Uart_Init(9600);
	MQTT_Connect("GreenHouse");
	MQTT_Publish("GHC",messges,strlen(messges), 0);
	
}
void GHC_Run(void)
{
	LDR=LDR_Get_Lux(ADC_CH0);
	if(LDR<LRL)
	{
		Led_On(LED6);
		*LEDstate="ON ";
	}
	else 
	{
		Led_Off(LED6);
		*LEDstate="OFF";
	}
	if(LDR>LRH)
	{
		servo_angle(90);
		*servoState="90";
	}
	else
	{
		servo_angle(0);
		*servoState="0 ";
	}
	c=Get_Temp();
	if(c>Tt)
	{
		DC_ON();
		*FanState="ON ";
	}
	else 
	{
		DC_OFF();
		*FanState="OFF";
	}
	h=Get_HUMIDITY();
	if(h<Th)
	{
		valvOn();
		*valve="ON ";
	}
	else
	{
		valvOff();
		*valve="OFF";
	}
	switch (Disp)
	{
		case Display_LDR:
		
		if(prev_state!=Display_LDR)
		
		{
			prev_state=Display_LDR;
			memset(messges,0,strlen(messges));
			sprintf(messges,"LDR Value=%d \nLED state:%s \nServo angle:%s \nLRL:%d LRH:%d",LDR,*LEDstate,*servoState,LRL,LRH);
			MQTT_Publish("GHC",messges,strlen(messges), 0);
			LCD_DispStrXY(1,1,LCD_LDR_L1);
			LCD_DispStrXY(2,1,LCD_LDR_L2);
			
		}
		LCD_DispStrXY(1,DISP_IND_LDR,"    ");
		
		LCD_DispNumberXY (1,DISP_IND_LDR,LDR);
		LCD_DispStrXY   (1,DISP_IND_LED,*LEDstate);
		LCD_DispStrXY  (2,DISP_IND_SERVO,*servoState);
		counter++;
		break;
		case Display_Temp:
		if(prev_state!=Display_Temp)
		{
			prev_state=Display_Temp;
			memset(messges,0,strlen(messges));
			sprintf(messges,"Current temperature=%d \nFan State:%s \nThreshold temperature =%d",c,*FanState,Tt);
			MQTT_Publish("GHC",messges,strlen(messges), 0);
			LCD_DispStrXY(1,1,LCD_temp_L1);
			LCD_DispStrXY(2,1,LCD_temp_L2);
			
		}
	    LCD_DispStrXY(1,DISP_IND_C,"    ");
		
		//LCD_DispNumberXY(1,DISP_IND_C,c);
		itoa(c,minusC_Disp,10);
		LCD_DispStrXY(1,DISP_IND_C,minusC_Disp);
		LCD_DispStrXY(1,DISP_IND_Fan,*FanState);
		LCD_DispNumberXY(2,DISP_IND_Tt,Tt);
		counter++;
		break;
		case Display_Humd:
		if(prev_state!=Display_Humd)
		{
			prev_state=Display_Humd;
			memset(messges,0,strlen(messges));
			sprintf(messges,"Current Humidity =%d \nValve State:%s \nThreshold Humidity =%d",h,*valve,Th);
			MQTT_Publish("GHC",messges,strlen(messges), 0);
			LCD_DispStrXY(1,1,LCD_Humdity_L1);
			LCD_DispStrXY(2,1,LCD_Humdity_L2);
			
		}
		LCD_DispStrXY(1,DISP_IND_h,"    ");
		
		LCD_DispNumberXY(1,DISP_IND_h,h);
		LCD_DispStrXY(1,DISP_IND_Valve,*valve);
		LCD_DispNumberXY(2,DISP_IND_th,Th);
		counter++;
		default:
		/* Your code here */
		break;
	}
	if(counter==10)
	{
		counter=0;
		Disp++;
		Disp%=(Display_Non);
	}
	
}
