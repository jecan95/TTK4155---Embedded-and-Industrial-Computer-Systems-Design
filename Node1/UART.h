#ifndef UART_H_
#define UART_H_

#include <stdio.h>

void USART_Init( unsigned int ubrr );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void ) ;
static int usart_putchar(char c, FILE *stream);
static int usart_getchar(FILE *stream);

extern FILE usart0_str;


#endif