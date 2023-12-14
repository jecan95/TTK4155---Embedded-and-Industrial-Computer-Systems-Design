#ifndef GAME_H_
#define GAME_H_

void game_init();
void set_data_joystick(char* data);
void move_servo_w_joystick();
void move_motor_pid();
void move_motor_joy();

#endif 