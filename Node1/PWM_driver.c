#include <avr/io.h>          
#include <stdint.h>          

#include "PWM_driver.h"      
#include "macro_register.h"  

static unsigned int pwm_period = 0x9C40; // Set PWM period to 40,000 (TOP value)
#define PWM_PERIOD 40000                  
#define PWM_MAX 4200                      
#define PWM_MIN 1800                      
#define PWM_MID ((PWM_MAX+PWM_MIN)/2)     
#define PWM_RES ((PWM_MAX-PWM_MIN)/100)   

void PWM_init(){
	set_bit1(DDRB, PB5); // Set PB5 as output for PWM

	// Configure timer/counter1 for PWM mode
	set_bit1(TCCR1B, WGM13);             // Set waveform generation mode bits
	set_bit1(TCCR1B, WGM12);
	set_bit1(TCCR1A, WGM11);
	set_bit0(TCCR1A, WGM10);

	set_bit1(TCCR1A, COM1A1);            // Set non-inverting mode for OC1A
	set_bit0(TCCR1A, COM1A0);

	// Set clock source and prescaler for timer/counter1
	set_bit0(TCCR1B, CS12);              // Configure prescaler bits
	set_bit1(TCCR1B, CS11);
	set_bit0(TCCR1B, CS10);

	ICR1 = PWM_PERIOD;                   // Set TOP for timer/counter1

	OCR1A = PWM_MID;                     // Set initial PWM duty cycle to midpoint
}

void pwm_set_duty(int8_t duty){
	if (duty > 100){                     // Limit duty cycle to 100%
		duty = 100;
		} else if (duty < 0){                // Limit duty cycle to 0%
		duty = 0;
	}
	
	OCR1A = PWM_MIN + PWM_RES*duty;      // Calculate and set PWM duty cycle
}
