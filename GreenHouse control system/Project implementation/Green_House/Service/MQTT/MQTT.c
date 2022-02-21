/*
* MQTT.c
*
* Created: 8/1/2021 9:21:32 AM
*  Author: MahmoudH
*/
#include "MQTT.h"

u8 protocolName[] = "MQTT";
u16 packetIdent = 1;


static void sendUTFString(u8* str){
	u8 len = strlen(str);
	Uart_SendByte(0x00);
	Uart_SendByte(len);
	Uart_SendStr(str);
}

void MQTT_Connect(u8* clientID){
	u8 remLen = (2 + strlen(protocolName)) + 1 + 1 + 2 + (2 + strlen(clientID));
	Uart_SendByte(0x10);
	Uart_SendByte(remLen);
	sendUTFString(protocolName);
	Uart_SendByte(0x04);
	Uart_SendByte(0x02);
	Uart_SendByte(0xFF);
	Uart_SendByte(0xFF);
	sendUTFString(clientID);
}
void MQTT_Publish(u8* topic, u8* message, u32 size, u8 QoS){
	u8 remLen = (2 + strlen(topic)) + size;
	u32 ind = 0;
	if(QoS > 0){
		Uart_SendByte(0x32);
		remLen += 2;
	}
	else{
		Uart_SendByte(0x30);
	}
	Uart_SendByte(remLen);
	sendUTFString(topic);
	if(QoS > 0){
		Uart_SendByte(packetIdent>>8);
		Uart_SendByte((u8)packetIdent);
		packetIdent++;
	}
	for (ind = 0; ind < size; ind++)
	{
		Uart_SendByte(message[ind]);
	}
}
void MQTT_Subscribe(u8* topic){
	u8 remLen = 2 + (2 + strlen(topic)) + 1;
	Uart_SendByte(0x82);
	Uart_SendByte(remLen);

	Uart_SendByte(packetIdent>>8);
	Uart_SendByte((u8)packetIdent);
	packetIdent++;
	
	sendUTFString(topic);
	Uart_SendByte(0x01);
}