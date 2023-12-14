#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_

#include <stdint.h>

void PWM_init();
void pwm_set_duty(int8_t duty);

#define PWM_PERIOD 40000
#define PWM_MAX 4200
#define PWM_MIN 1800
#define PWM_MID ((PWM_MAX+PWM_MIN)/2)
#define PWM_RES ((PWM_MAX-PWM_MIN)/100)

#endif
