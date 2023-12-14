#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "SPI_Driver.h"

//******************SPI as master**************************//

void SPI_MasterInit(void)
{
	DDRB = (1<<PB5)|(1<<PB7)|(1<<PB4);   // Set MOSI, SCK, and SS as output

	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); // Enable SPI, set as master, set clock rate

	PORTB |= (1<<PB4);                   // Set SS high
}

void SPI_Transmit(char cData)
{
	SPDR = cData;                       // Start transmission
	while(!(SPSR & (1<<SPIF)))          // Wait for transmission complete
	;
}

char SPI_Receive(void)
{
	SPI_Transmit(0);                    // Transmit dummy data
	while(!(SPSR & (1<<SPIF)))          // Wait for transmission complete
	;
	return SPDR;                        // Return received data
}