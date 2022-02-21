/*
 * MQTT.h
 *
 * Created: 8/1/2021 9:21:09 AM
 *  Author: MahmoudH
 */ 


#ifndef MQTT_H_
#define MQTT_H_

#define F_CPU	8000000UL

#include "avr/io.h"
#include "util/delay.h"
#include "bit_handle.h"
#include "data_types.h"
#include "uart.h"
#include "string.h"

void MQTT_Connect(u8* clientID);
void MQTT_Publish(u8* topic, u8* message, u32 size, u8 QoS);
void MQTT_Subscribe(u8* topic);


#endif /* MQTT_H_ */