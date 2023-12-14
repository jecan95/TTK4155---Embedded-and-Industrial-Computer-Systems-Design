#include "sam.h"
#include "led.h"

#define LED1_PIN PIO_PA19
#define LED2_PIN PIO_PA20

void set_led()
{
	PIOA->PIO_OER = LED1_PIN | LED2_PIN;
	PIOA->PIO_PER = LED1_PIN | LED2_PIN;
	PIOA->PIO_SODR = LED1_PIN | LED2_PIN;
}

void clear_led()
{
	PIOA->PIO_OER = LED1_PIN | LED2_PIN;
	PIOA->PIO_PER = LED1_PIN | LED2_PIN;
	PIOA->PIO_CODR = LED1_PIN | LED2_PIN;
}