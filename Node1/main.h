

#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

//Define oscillator frequency
#define F_CPU 4912500UL


// Function prototypes
void UART_init(uint32_t baudrate);
void UART_tx_char(uint8_t data);
void USART_Transmit( unsigned char data );
void UART_tx_string(const char* data);
uint8_t UART_rx_char(void);


// Global variables
volatile uint8_t rx_data;
volatile uint8_t rx_flag;



#endif /* MAIN_H_ */