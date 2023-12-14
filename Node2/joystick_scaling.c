#include <stdlib.h>
#include <stdint.h>
#include "joystick_scaling.h"
#include "game.h"

volatile float x_offset;
volatile float y_offset;

 joystick_position joystick_data;

extern joystick_position data_cal;

void joystick_calibration(joystick_position pos_init){
	x_offset = pos_init.x;
	y_offset = pos_init.y;
}

void joystick_init(){
	
	joystick_calibration(data_cal);
	
}

joystick_position get_scale_joystick_position(joystick_position pos_init)
{
	joystick_position position;
	
	if (pos_init.x <= x_offset) 
	{
		position.x = -((-100 / x_offset) * pos_init.x + 100);
	} 
	else 
	{
		position.x = 100.0/(255-x_offset)*pos_init.x - (100.0/(255-x_offset)*x_offset);
	}
	

	if (pos_init.y <= y_offset) 
	{
		position.y = -((-100 / y_offset) * pos_init.y + 100);
	} 
	else 
	{
		position.y = 100.0/(255-y_offset)*pos_init.y - (100.0/(255-x_offset)*y_offset);
	}

	return position;
}


joystick_position get_scale_joystick_position_pid(joystick_position pos_init2)
{
	 joystick_position position2;
	 
	  
	 if (pos_init2.x <= x_offset) 
	 {
		 position2.x = (pos_init2.x*100)/255; 
	 }
	 else
	 {
		 position2.x = ((pos_init2.x-x_offset)/(255-94)) * 50 + 50;
	 }
	 
	 if (pos_init2.y <= y_offset)
	 {
		 position2.y = (pos_init2.y*100)/255;
	 }
	 else
	 {
		 position2.y = ((pos_init2.y-y_offset)/(255-94)) * 50 + 50;
	 }
	 
	 return position2;
}