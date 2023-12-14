#include "adc.h"
#include "led.h"
#include "sam.h"
static unsigned int counting_flag;

void initialize_adc() {
	
	REG_PMC_PCER1 |= PMC_PCER1_PID37;	// Enable clock for ADC, peripheral ID 37
	REG_ADC_MR |= ADC_MR_FREERUN_ON;	// Set ADC to free-run mode
	REG_ADC_CHER |= ADC_CHER_CH0;		// Enable ADC channel 0
	REG_ADC_CR |= ADC_CR_START;		// Start ADC conversion

}

uint16_t fetch_adc_value() {
	return ADC->ADC_CDR[0]; // Return ADC value from channel 0
}


