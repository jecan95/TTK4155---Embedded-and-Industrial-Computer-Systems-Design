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
#include "motor.h"
#include "pid.h"
#define  F_CPU 84000000


void main(void)
{
 	SystemInit();
 	configure_uart();
 	servo_init();
 	can_init_def_tx_rx_mb(CAN_BR_timing);
// 	set_led();
 	initialize_adc();
 	solenoid_init();
 	game_init();
 	DAC_init();
 	MOTOR_init();
 	encoder_calibrate();
 	initialize_adc();
	

	
    while (1) 
    {       
  		motor_enable();
		solenoid_punch();
		score_count();
		move_servo_w_joystick();
		//move_motor_pid();
    }

}
