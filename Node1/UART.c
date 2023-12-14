#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#define FOSC 4915200UL // Clock Speed
#define BAUD 9600

void USART_Init( unsigned int ubrr ) {
	UBRR0H = (unsigned char)(ubrr>>8);  // Set higher byte of baud rate
	UBRR0L = (unsigned char)ubrr;       // Set lower byte of baud rate

	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);  // Configure USART: 8 data bits, 2 stop bits

	UCSR0B = (1<<RXEN0)|(1<<TXEN0);  // Enable receiver and transmitter
}

void USART_Transmit( unsigned char data ) {
	while ( !( UCSR0A & (1<<UDRE0)) )  // Wait for empty transmit buffer
	;

	UDR0 = data;  // Put data into buffer, sends the data
}

unsigned char USART_Receive( void ) {
	while ( !(UCSR0A & (1<<RXC0)) )  // Wait for data to be received
	;
	return UDR0;  // Get and return received data from buffer
}

int usart_putchar(char c, FILE *stream) {
	if (c == '\n') {
		usart_putchar('\r', stream);  // Convert newline to carriage return-newline
	}
	USART_Transmit(c);
	return 0;
}

int usart_getchar(FILE *stream) {
	return USART_Receive();  // Read character from USART
}

FILE usart0_str = FDEV_SETUP_STREAM(usart_putchar, usart_getchar, _FDEV_SETUP_RW);  // Setup USART streams
