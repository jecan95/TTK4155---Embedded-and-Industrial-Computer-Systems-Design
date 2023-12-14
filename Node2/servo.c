#include "pwm.h"

#define MIN_DUTY_CYCLE      900  // Define minimum duty cycle for PWM
#define MAX_DUTY_CYCLE      2100 // Define maximum duty cycle for PWM
#define X_MIN               -100 // Define minimum position value for servo
#define X_MAX               100  // Define maximum position value for servo

// Calculate gain for converting position to duty cycle
#define GAIN                (MAX_DUTY_CYCLE - MIN_DUTY_CYCLE) / (X_MIN - X_MAX)
// Calculate offset for converting position to duty cycle
#define OFFSET              MAX_DUTY_CYCLE - X_MIN * GAIN

// Function to set servo position based on x value
void servo_set_position(int x) {
	float duty_cycle = -GAIN * x + OFFSET; // Convert position x to duty cycle
	PWM_setDC(duty_cycle); // Set duty cycle on PWM
}

// Initialize servo to default position
void servo_init() {
	PWM_init(); // Initialize PWM module
	servo_set_position(0); // Set servo to center position
}

// Sweep servo from right to left with specified delay
void servo_sweep_right_to_left(int delay_ms) {
	for (int x = X_MIN; x <= X_MAX; x++) { // Loop from min to max position
		servo_set_position(x); 
		_delay_ms(delay_ms);  
	}
}



