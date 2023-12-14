#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct can_message_t
{
	uint16_t id;
	char data_length;
	char data[8];
} CAN_MESSAGE;
	
void receive_interrupt();
void CAN_init(uint8_t);
void CAN_Send(CAN_MESSAGE*);
void CAN_Receive(CAN_MESSAGE*);


#endif