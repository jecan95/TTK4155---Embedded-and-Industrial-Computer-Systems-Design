#include "motor.h"
#include "joystick_scaling.h"
#include "sam.h"
#include "timer.h"
#include <stdint.h>
#include <stdio.h>

#define DIR PIO_PD10				
#define EN PIO_PD9					
#define SEL PIO_PD2					
#define NOT_OE PIO_PD0				
#define NOT_RST PIO_PD1		

#define PORT_MJ2_ENCODER_MASK 0x1FE	

#define encoder_max 312


void DAC_init(){
	
	//Peripheral clock register enable 1 
	REG_PMC_PCER1 |= PMC_PCER1_PID38;
	
	//mode register - channel 1 - half word transfer - 0 period of dac clock 
	//normal mode 
	DACC->DACC_MR = DACC_MR_USER_SEL_CHANNEL1 | DACC_MR_WORD_HALF | DACC_MR_STARTUP_0;
	
	//DAC channel register - channel 1 enable 
	REG_DACC_CHER = DACC_CHER_CH1;

}

void MOTOR_init(){
	//control pio enable register 
	PIOD->PIO_PER |= DIR | EN | SEL | NOT_OE | NOT_RST;
	//output enable register
	//pin motor box in output 
	PIOD->PIO_OER |= DIR | EN | SEL | NOT_OE | NOT_RST;
	
	
	PIOC->PIO_PER |= PORT_MJ2_ENCODER_MASK;
	//pin motor encoder as input 
	PIOC->PIO_ODR |= PORT_MJ2_ENCODER_MASK;
	
	//enable clock 
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PIOC << PMC_PCR_PID_Pos);
	PMC->PMC_PCER0 |= 1 << (ID_PIOC);
	
	REG_PIOC_IFER = (0xFF<<1);
	REG_PIOC_PUDR = (0xFF)<<1;
	
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	
}

void motor_enable()
{
	//PIO controller set output data register motor enable 
	PIOD->PIO_SODR = EN;
}

void motor_disabled()
{
	set_speed(0);
	PIOD->PIO_CODR = EN;
}

void set_direction_motor(joystick_direction direction)
{
	if(direction == RIGHT)
	{
		PIOD->PIO_CODR |= DIR; 
	}
	else
	{
		PIOD->PIO_SODR |= DIR; 
	}
}

int read_encoder()
{
	int data;
	
	PIOD->PIO_CODR |= NOT_OE; //NOT OE low to enable encoder output (sample and hold encoder value)
	
	PIOD->PIO_CODR |= SEL; //SEL low 
	_delay_us(30);
	uint8_t msb = ((PIOC->PIO_PDSR & PORT_MJ2_ENCODER_MASK) >> 1); //read msb MJ2
	
	PIOD->PIO_SODR |= SEL; //SEL high (get low byte) 
	_delay_us(30);
	uint8_t lsb = ((PIOC->PIO_PDSR & PORT_MJ2_ENCODER_MASK) >> 1); //read msb MJ2
	
	//reset encoder
	PIOD->PIO_CODR |= NOT_RST;
	PIOD->PIO_SODR |= NOT_RST;
	
	//Disable output encoder
	PIOD->PIO_SODR = NOT_OE;
	
	data = (msb<<8) | lsb;
	
	if (data & (0x8000)){
		return ((uint16_t)(~data));
	}
	
	return -data;
	
}

void set_speed(uint16_t speed)
{
	DACC->DACC_CDR = speed;
}

void reset_encoder()
{
	PIOD->PIO_CODR |= NOT_RST;
	_delay_us(200);
	PIOD->PIO_SODR |= NOT_RST;
}


void encoder_calibrate(){
	motor_enable();
	set_speed(0);
	set_speed(0x1300);
	set_direction_motor(RIGHT);
	_delay_ms(3000);

	reset_encoder();
	
	set_speed(0x1300);
	set_direction_motor(LEFT);
	_delay_ms(3000);
	
	printf("Calibration Ok ! \n\r");
}

int motor_control(PARAM_PID *PID, uint16_t joystick_pos)
{
	float current_position_encoder = read_encoder();
	uint16_t scaled_position_encoder = scale_encoder(current_position_encoder);
	int pid = pid_control(PID, joystick_pos, scaled_position_encoder);
	return pid; 
}

int scale_encoder(int pos_encoder)
{
	uint16_t scale_value = pos_encoder/(encoder_max/100);
	return scale_value; // scale between 0-100
}

