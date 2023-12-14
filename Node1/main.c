#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "macro_register.h"
#include "UART.h"
#include "test_sram_led.h"
#include "joystick.h"
#include "OLED.h"
#include "CAN_Driver.h"
#include "MCP2515_Driver.h"
#include "ADC.h"
#include "menu.h"

#define FOSC 4915200UL // Clock Speed 
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1 

void main( void )
{ 
	cli();
	USART_Init (UBRR);
	set_bit1(MCUCR,7);
	stdin = &usart0_str;
	stdout = &usart0_str;
	unsigned char received_char;
	
	ADC_init();
	joystick_init();
	joystick_calibration();
	oled_init();
 	CAN_init(MODE_NORMAL);
	sei();

	joystick_position_analog value;
	joystick_position_analog position;
	joystick_direction direction;
	
	int selectedOption = 0;
	int button = 1;
	int punch=0;
	int select_menu = 0;
	int gameStart = 0;
	displayMainMenu(0);
	selectedOption = selection_menu(button, select_menu);
	
	
  while(1) 
  {
	  if((PINB & (1 << PB2)) == 0) {
		  _delay_ms(50);
		  if((PINB & (1 << PB2)) == 0) 
		  {
			button = !button; 
			while((PINB & (1 << PB2)) == 0);
		  }
	  }
	  
	  selectedOption = selection_menu(button, select_menu);
	  
	  switch(selectedOption)
	  {
		  case 0 : 
			select_menu = 1;
			
			if(gameStart == 0)
			{
				printf("START GAME... \n");
			}
			
			gameStart = 1;
			
		  	if((PINB & (1 << PB3)) == 0)
		  	{
			  	punch=1;
		  	}
		  	else
		   {
			  	punch=0;
		  	}
		  		  
		  	joystick_position joystick_position = get_adc_value();
		  	CAN_MESSAGE joystick_data =
		  	{
			  	.id = 1,
			  	.data_length = 3,
			  	.data[0] = joystick_position.x,
			  	.data[1] = joystick_position.y,
			  	.data[2] = punch,
		  	};
			CAN_Send(&joystick_data);
			break;
			
		  case 1 :
			select_menu = 0;
			position = get_joystick_position();
			printf("Position X : %d \n", position.x);
			printf("Position Y : %d \n", position.y);
			printf("---------------\n");
			_delay_ms(1000);
			break;
			
		  case 3 : 
		  if(gameStart == 1)
		  {
			  printf("GAME END \n");
			  gameStart = 0;
			  select_menu = 0;
		  }
			
	  }
	  
  }

}

  ISR(INT0_vect)
  {
 	  CAN_MESSAGE message_recu;
 	  CAN_Receive(&message_recu);
 	  for (uint8_t i = 0; i < message_recu.data_length; i++)
 	  {
 		  printf("Message : 0x%x \n", message_recu.data[i]);
 	  }
	  
	  MCP2515_bit_modify(MCP_CANINTF, MCP_RX1IF | MCP_RX0IF, 0);
  }