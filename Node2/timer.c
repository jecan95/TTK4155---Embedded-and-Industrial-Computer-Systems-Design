#include "timer.h"
#include "sam.h"

#define IRQ_SysTick_priority    0  // SysTick interrupt priority
#define F_CPU                   84000000  

volatile uint32_t wait_ticks = 0;  

// Initializes SysTick for microsecond delays
static void SysTick_init_us(int period) {
	SysTick->LOAD = ((int)(period*84) & SysTick_LOAD_RELOAD_Msk)-1;  // Set reload value for 1us
	
	SysTick->VAL = 0;  // Reset SysTick current value

	NVIC_SetPriority(SysTick_IRQn, IRQ_SysTick_priority);  // Set SysTick interrupt priority

	SysTick->CTRL  = (1 << SysTick_CTRL_CLKSOURCE_Pos) & SysTick_CTRL_CLKSOURCE_Msk;  // Use processor clock
	SysTick->CTRL |= (1 << SysTick_CTRL_TICKINT_Pos) & SysTick_CTRL_TICKINT_Msk;  // Enable SysTick interrupt
	SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos) & SysTick_CTRL_ENABLE_Msk;  // Enable SysTick
}

// Delay function in microseconds
void _delay_us(uint16_t us) {
	wait_ticks = us;  // Set delay duration
	SysTick_init_us(1);  // Initialize SysTick for 1us ticks
	while(wait_ticks != 0);  // Wait until delay is complete
}

// Delay function in milliseconds
void _delay_ms(uint16_t ms) {
	wait_ticks = ms;  // Set delay duration
	SysTick_init_us(1000);  // Initialize SysTick for 1ms ticks
	while(wait_ticks != 0);  // Wait until delay is complete
}

// SysTick interrupt handler
void SysTick_Handler(void) {
	if(wait_ticks!=0) {
		wait_ticks--;  // Decrement wait_ticks each SysTick
	}
	else {
		SysTick->CTRL = 0;  // Disable SysTick when delay is complete
	}
}
