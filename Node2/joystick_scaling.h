#ifndef JOYSTICK_SCALING_H_
#define JOYSTICK_SCALING_H_

typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL} joystick_direction;

typedef struct {
	int x;
	int y;
} joystick_position;


void joystick_calibration();
void joystick_init();
joystick_position get_scale_joystick_position();
joystick_position get_scale_joystick_position_pid(joystick_position pos_init);

#endif 