#include "pwm.h"
#include "sam.h"

void PWM_init()
{
	REG_PMC_PCER1 |= PMC_PCER1_PID36;		// Enable PWM peripheral clock

	REG_PIOC_PDR |= PIO_PDR_P19;			// Disable GPIO control of P19
	REG_PIOC_ABSR |= PIO_ABSR_P19;			// Switch P19 to B peripheral (PWM)

	REG_PWM_CLK |= PWM_CLK_PREA(0) | PWM_CLK_DIVA(42); // Set PWM clock rate

	REG_PWM_CMR5 = PWM_CMR_CALG | PWM_CMR_CPOL | PWM_CMR_CPRE_CLKA;	// Config PWM channel 5

	REG_PWM_CPRD5 = 20000;					// Set PWM cycle length
	REG_PWM_CDTY5 = 1500; 					// Set initial duty cycle

	REG_PWM_ENA = PWM_ENA_CHID5;			// Enable PWM channel 5
}


void PWM_setDC(int value) // Set length of pulse
{
	if(value < 900){
		value = 900;		// Min length of pulse 900
	}
	else if(value > 2100){		// Max length of pulse 2100
		value = 2100;
	}
	else{
		REG_PWM_CDTY5 = value;	// Set length of pulse
	}
}
