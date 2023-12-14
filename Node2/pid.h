#ifndef PID_H_
#define PID_H_

typedef struct
{
	float Kp;
	float Ki;
	//float Kd;
	float sumError;
	float prevError;
	float T;
}PARAM_PID;


int pid_control(PARAM_PID *PID, int r, int current_value);
void pid_init(PARAM_PID *PID, float kp, float ki, float T);


#endif