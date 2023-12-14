#include <stdlib.h>
#include <stdint.h>
#include "pid.h"
	
void pid_init(PARAM_PID *PID, float kp, float ki, float T)
{
	PID->Kp = kp;
	PID->Ki = ki;
	//PID->Kd = kd;
	PID->T = T;
	PID->sumError = 0;
	PID->prevError = 0;
}

int pid_control(PARAM_PID *PID, int r, int current_value)
{
	float error = r - current_value; 
	PID->sumError += error; 
	
	float Kp_p = PID->Kp * error; 
	float Ki_p = PID->Ki * PID->T * PID->sumError; 
	//float Kd_p = PID->Kd / PID->T * (error - PID->prevError); 

	int kppp = Kp_p;
	int kiii = Ki_p;
	//int kddd = Kd_p;
	
	int u = Kp_p + Ki_p;

	PID->prevError = error; 

	return u;
}



