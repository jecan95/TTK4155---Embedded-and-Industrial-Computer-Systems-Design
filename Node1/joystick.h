#ifndef JOYSTICK_H_
#define JOYSTICK_H_

typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL} joystick_direction;

typedef struct {
	int x;
	int y;
} joystick_position_analog;


void joystick_calibration();
void joystick_init();
joystick_position_analog get_joystick_position();
joystick_direction joystick_get_direction();

#endif 