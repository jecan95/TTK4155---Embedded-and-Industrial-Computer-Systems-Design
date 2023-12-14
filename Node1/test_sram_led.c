#include "test_sram_led.h"
#include "macro_register.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

void test_sram_led()
{
	
	   set_bit1(DDRE, 1);
	   set_bit1(PINE, 1);
	   set_bit1(PORTE, 1); // PORT E for 
		   
// 	   set_bit1(DDRA, 0);
// 	   uint8_t reg1 = PINA;
// 	   set_bit1(reg1, 0);
// 	   PORTA = reg1; // PORT A

		set_bit1(DDRA, 0);
		set_bit1(PINA, 0);
		set_bit0(PORTA, 0);
	   
		set_bit1(DDRA, 2);
		set_bit1(PINA, 2);
		set_bit0(PORTA, 2);
	   	   
		set_bit1(DDRA, 3);
		set_bit1(PINA, 3);
		set_bit0(PORTA, 3);
	   	   
		set_bit1(DDRA, 4);
		set_bit1(PINA, 4);
		set_bit0(PORTA, 4);
	   	   
		set_bit1(DDRA, 5);
		set_bit1(PINA, 5);
		set_bit0(PORTA, 5);
	   	   
		set_bit1(DDRA, 6);
		set_bit1(PINA, 6);
		set_bit0(PORTA, 6);
	   	   
		set_bit1(DDRA, 7);
		set_bit1(PINA, 7);
		set_bit0(PORTA, 7);
			  
		set_bit1(DDRA, 1);
		set_bit1(PINA, 1);
		set_bit1(PORTA, 1);
		   
		set_bit1(DDRE, 1);
		set_bit1(PINE, 1);
		set_bit0(PORTE, 1);
	   
/*	   set_bit0(PORTA, 1);*/ // test latch

}