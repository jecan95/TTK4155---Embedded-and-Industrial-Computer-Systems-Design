#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

static void SysTick_init_us(int period);
void _delay_us(uint16_t us);
void _delay_ms(uint16_t ms);
void SysTick_Handler(void);

#endif