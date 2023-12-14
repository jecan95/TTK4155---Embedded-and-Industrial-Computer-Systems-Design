#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "macro_register.h"
#include "ADC.h"
#include "joystick.h"

volatile uint8_t x_offset;
volatile uint8_t y_offset;

void joystick_calibration(){
	joystick_position pos_init;
	pos_init = get_adc_value();
	x_offset = pos_init.x;
	y_offset = pos_init.y;
}

void joystick_init(){
	
	// Button inputs:
	set_bit0(DDRB, PB3);	//Joystick button
	set_bit1(PORTB, PB3);	//Set pull-up resistor
	set_bit0(DDRB, PB2);	//SW0 button
	set_bit1(PORTB, PB2);	//Set pull-up resistor
	joystick_calibration();
}


joystick_position_analog get_joystick_position()
{
	joystick_position_analog position;
	joystick_position pos_init;

	pos_init = get_adc_value();
	
	if (pos_init.x <= x_offset) 
	{
		position.x = -((-100 / x_offset) * pos_init.x + 100);
	} 
	else 
	{
		position.x = 100.0/(255-x_offset)*pos_init.x - (100.0/(255-x_offset)*x_offset);
	}
	

	if (pos_init.y <= y_offset) 
	{
		position.y = -((-100 / y_offset) * pos_init.y + 100);
	} 
	else 
	{
		position.y = 100.0/(255-y_offset)*pos_init.y - (100.0/(255-x_offset)*y_offset);
	}

	return position;
}

joystick_direction joystick_get_direction() {
	
	joystick_position_analog position = get_joystick_position();
	
	int x = position.x;
	int y = position.y;

	if(abs(x) >= abs(y))
	{
		if(abs(x) < 10)
		{
			return NEUTRAL;
		}
		else if(x > 0)
		{
			return RIGHT;
		}
		else
		{
			return LEFT;
		}
	}
	else
	{
		if(abs(y) < 10)
		{
			return NEUTRAL;
		}
		else if(y > 0)
		{
			return UP;
		}
		else
		{
			return DOWN;
		}
	}
}