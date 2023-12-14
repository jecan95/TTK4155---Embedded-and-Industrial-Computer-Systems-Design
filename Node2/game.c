#include <stdio.h>
#include <stdlib.h>
#include "sam.h"
#include "led.h"
#include "uart.h"
#include "printf_stdarg.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "pwm.h"
#include "servo.h"
#include "game.h"
#include "joystick_scaling.h"
#include "adc.h"
#include "pid.h"
#define IR_seuil           800
joystick_position joystick_data_servo;
joystick_position joystick_data_motor;
joystick_position data_cal;
int lives=3;
int cmpt=0;

#define kp 1
#define ki 5
#define T 0.0001

PARAM_PID PID;

void game_init()
{
	pid_init(&PID, kp, ki, T);
}

void score_count()
{
	uint16_t ir_level = fetch_adc_value();
	printf("IR Level: %u \n", ir_level);

	if ((ir_level < IR_seuil) )
	{
		clear_led();
		lives--;
		_delay_ms(1000);
	}

	else if (ir_level > IR_seuil) 
	{	
		set_led();
	}
	printf("score : %d \n",lives);
}

void set_data_joystick(char* data)
{
	char x_data = data[0];
	char y_data = data[1];
	joystick_position temp_data =
	{
		.x = x_data,
		.y = y_data,
	};
	data_cal = temp_data;
	
	if(cmpt==0)
	{
		joystick_init();
		cmpt = cmpt+1;
	}
	joystick_data_servo = get_scale_joystick_position(temp_data);
	joystick_data_motor = get_scale_joystick_position_pid(temp_data);
	
}

void move_servo_w_joystick()
{
	servo_set_position(joystick_data_servo.y);
}

void move_motor_pid()
{
 	int pid_p = motor_control(&PID, joystick_data_motor.x);
	if(pid_p < -5)
	{
		set_speed(0x1200);
		set_direction_motor(RIGHT);
	}
	else if(pid_p > 5)
	{
		set_speed(0x1200);
		set_direction_motor(LEFT);
	}
	else
	{
		set_speed(0);
	}
}

void move_motor_joy()
{
	if(joystick_data_servo.x <-25)
	{
		set_speed(0x1300);
		set_direction_motor(RIGHT);
	}
	else if(joystick_data_servo.x > 25)
	{
		set_speed(0x1300);
		set_direction_motor(LEFT);
	}
	else
	{
		set_speed(0);
	}
}
