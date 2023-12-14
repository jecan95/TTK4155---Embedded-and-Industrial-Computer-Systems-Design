#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "MCP2515_Driver.h"

#define SYNC_SEG 1
#define PROPAG 2
#define PS1 6
#define PS2 7
//#define BRP 4
#define F_CPU 16000000

uint8_t MCP2515_init(uint8_t mode)
{
	SPI_MasterInit();
	MCP2515_reset();
	
	_delay_ms(2);

	uint8_t value = MCP2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2515 is NOT in configuration mode after reset!\n"); 
		return 1;
	}
	// More initialization
	//MCP2515_write(MCP_CANCTRL, mode);
	
// 	MCP2515_write(MCP_CNF1, ((SJW1-1)<<6) | (BRP-1));
// 	MCP2515_write(MCP_CNF2, BTLMODE | SAMPLE_3X | ((PS1-1) << 3) | (PROPAG-1));
// 	MCP2515_write(MCP_CNF3, (PS2-1));
	
	uint8_t BRP = F_CPU / (2 * 16 * 250000);

	MCP2515_write(MCP_CNF1, SJW4 | (BRP - 1));
	MCP2515_write(MCP_CNF2, BTLMODE | SAMPLE_3X | ((PS1 - 1) << 3) | (PROPAG - 1));
	MCP2515_write(MCP_CNF3, WAKFIL_DISABLE | (PS2 - 1));
	
	return 0;
}

uint8_t MCP2515_read(uint8_t address)
{
	uint8_t data;

	PORTB &= ~(1 << PB4); //CS Low
	SPI_Transmit(MCP_READ); //READ Command
	SPI_Transmit(address);
	data = SPI_Receive();
	PORTB |= (1 << PB4); //CS High

	return data;
}

uint8_t MCP2515_write(uint8_t address, uint8_t data)
{
	PORTB &= ~(1 << PB4);
	SPI_Transmit(MCP_WRITE);
	SPI_Transmit(address);
	SPI_Transmit(data);
	PORTB |= (1 << PB4);
}

void MCP2515_request_to_send()
{
	PORTB &= ~(1 << PB4);
	SPI_Transmit(MCP_RTS_TX0);
	PORTB |= (1 << PB4);
}


uint8_t MCP2515_read_status()
{
	uint8_t status;

	PORTB &= ~(1 << PB4);
	SPI_Transmit(MCP_READ_STATUS);
	status = SPI_Receive();
	PORTB |= (1 << PB4);

	return status;
}


void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
{
	PORTB &= ~(1 << PB4);
	SPI_Transmit(MCP_BITMOD);
	SPI_Transmit(address);
	SPI_Transmit(mask);
	SPI_Transmit(data);
	PORTB |= (1 << PB4);
}


void MCP2515_reset()
{
	PORTB &= ~(1 << PB4);
	SPI_Transmit(MCP_RESET);
	PORTB |= (1 << PB4);
}