#ifndef servo_h_
#define servo_h_
#include <stdio.h>
#include <stdint.h>

void servo_sweep_right_to_left(int delay_ms);
void servo_init();
void servo_set_position( int x);

#endif