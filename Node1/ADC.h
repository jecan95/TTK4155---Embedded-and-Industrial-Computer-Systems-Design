#ifndef ADC_H_
#define ADC_H_

typedef struct {
	int x;
	int y;
} joystick_position;

void ADC_init(void);
joystick_position get_adc_value();

#endif