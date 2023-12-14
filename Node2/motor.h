#ifndef MOTOR_H_
#define MOTOR_H_

#include "joystick_scaling.h"
#include "pid.h"
#include <stdint.h>

void DAC_init();
void MOTOR_init();
void motor_enable();
void motor_disabled();
void set_direction_motor(joystick_direction direction);
int read_encoder();
void set_speed(uint16_t speed);
void reset_encoder();
int motor_control(PARAM_PID *PID, uint16_t joystick_pos);
int scale_encoder(int pos_encoder);

#endif 