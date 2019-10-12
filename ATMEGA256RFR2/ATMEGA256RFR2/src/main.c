/*
 * 
 */ 
#include "../includes/temperature.h"
#include "../includes/at30ts.h"

#include <stdint-gcc.h>
#include <delay.h>
#include <sysclk.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <atmega256rfr2_xplained_pro/atmega256rfr2_xplained_pro.h>
#include <atmega256rfr2_xplained_pro/led.h>

int main(void)
{
	sysclk_init();
	board_init();
	TWI_init();
	
	sei(); // Enable global interrupts
	uint16_t temp=5;
	sensor_data_t data;
    while(1)
    {
		//read_temperature(&data);
		if (temp != getTemperature()){
			temp = getTemperature();
		}
		delay_ms(250);
    }
}