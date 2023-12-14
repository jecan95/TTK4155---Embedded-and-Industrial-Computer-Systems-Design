#include "solenoide.h"
#include "sam.h"

char punch;

void solenoid_init(){
	PIOA->PIO_PER |= PIO_PA24;	
	PIOA->PIO_OER |= PIO_PA24;	
	PIOA->PIO_SODR |= PIO_PA24;
}

void set_data_solenoid(char* data)
{
	 punch = data[2];
}

void solenoid_punch(){
	if (punch == 1)			
	{
		PIOA->PIO_CODR |= PIO_PA24;	
	}
	else if (punch == 0){		
		PIOA->PIO_SODR |= PIO_PA24;	
	}
}