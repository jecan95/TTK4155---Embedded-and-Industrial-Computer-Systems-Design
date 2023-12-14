#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "CAN_Driver.h"
#include "MCP2515_Driver.h"
#include <stdbool.h>
bool buffer_is_free();

void receive_interrupt() // Initialize CAN receive interrupt
{
	DDRD &= ~(1 << PD2); // Configure PD2 as input

	GICR |= (1 << INT0); // Enable external interrupt INT0

	MCUCR |= (1 << ISC01); // Set interrupt on falling edge
	MCUCR &= ~(1 << ISC00); // Set interrupt on falling edge
}

void CAN_init(uint8_t mode)
{
	MCP2515_init(mode); 

	MCP2515_write(MCP_RXB0CTRL, MCP_RXM1 | MCP_RXM0); // Turn off filters/masks

	MCP2515_bit_modify(MCP_CANINTE, MCP_RX1IF | MCP_RX0IF, 0xFF); 	// Enable interrupts for RX0 and RX1
	receive_interrupt(); // Setup interrupt for CAN reception
	
	MCP2515_bit_modify(MCP_CANCTRL, MODE_MASK, mode); // Re-apply mode setting
}

void CAN_Send(CAN_MESSAGE* message)
{
	MCP2515_write(MCP_TXB0SIDH, (message->id) >> 3); // Set ID high bits
	MCP2515_write(MCP_TXB0SIDL, (message->id & 0x07) << 5); // Set ID low bits
	
	MCP2515_write(MCP_TXB0DLC, message->data_length); // Set data length

	while(!buffer_is_free()) // Wait until buffer is free
	{
		// Busy wait
	}
	for (uint8_t i = 0; i < message->data_length; i++) // Load data bytes
	{
		MCP2515_write(MCP_TXB0D0 + i, message->data[i]); // Write data bytes
	}
	MCP2515_request_to_send(); // Send request to MCP2515
}

bool buffer_is_free(){
	return (MCP2515_read((MCP_TXB0CTRL) & MCP_TXREQ)) == 0; // Check if buffer is ready to send
}


void CAN_Receive(CAN_MESSAGE* message)
{
	if (MCP2515_read(MCP_CANINTF) & MCP_RX0IF) // Check if RX0 buffer has a message
	{
		uint8_t id_low_0 = MCP2515_read(MCP_RXB0SIDL); // Read ID low bits
		uint8_t id_high_0 = MCP2515_read(MCP_RXB0SIDH); // Read ID high bits
		message->id = (id_low_0 >> 5) + (id_high_0 << 3); // Combine ID parts
		
		message->data_length = MCP2515_read(MCP_RXB0DLC); // Read data length
		
		for (uint8_t i = 0; i < message->data_length; i++) // Read data bytes
		{
			message->data[i] = MCP2515_read(MCP_RXB0D0 + i); // Store data in message
		}
	}
	else if (MCP2515_read(MCP_CANINTF) & MCP_RX1IF) // Check if RX1 buffer has a message
	{
		uint8_t id_low_1 = MCP2515_read(MCP_RXB1SIDL); // Read ID low bits for buffer 1
		uint8_t id_high_1 = MCP2515_read(MCP_RXB1SIDH); // Read ID high bits for buffer 1
		message->id = (id_low_1 >> 5) + (id_high_1 << 3); // Combine ID parts for buffer 1

		message->data_length = MCP2515_read(MCP_RXB1DLC); // Read data length for buffer 1

		for (int m = 0; m < message->data_length; m++) { // Read data bytes for buffer 1
			message->data[m] = MCP2515_read(MCP_RXB1D0 + m); // Store data in message for buffer 1
		}
	}
}
