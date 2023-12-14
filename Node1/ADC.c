#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "macro_register.h"
#include "ADC.h"

volatile uint8_t* pt_adc = (uint8_t *) 0x1400;	


void ADC_init(void)
{

 	DDRD |= (1 << PD4); // PD4 in output
 	
	// CTC mode
	TCCR3B |= (1 << WGM32);
	
	//PWM frequency (2.4 Mhz now)
	//OCR3A = 0x0000; 
	
	//TCCR3A |= (1 << COM3B0); // toogle OCC3B (PD5) on cpmpare match
	TCCR3A |= (1 << COM3A0);
	
	// start timer with pre-scaler = 1
	TCCR3B |= (1 << CS30);

}

joystick_position get_adc_value()
{
	uint8_t values[4] = {0,0,0,0};
	pt_adc[0] = 0;
	joystick_position position;
	for (int i = 0; i < 4; ++i){
		_delay_us(30);
		values[i] = *pt_adc;
	}
	position.x = values[0];
	position.y = values[1]; 
	
	return position;
}


