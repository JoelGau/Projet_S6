/*
 * 
 */ 
#include "../includes/temperature.h"

#include <stdint-gcc.h>
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
	//AT30TSE758_init();
	
	sei(); // Enable global interrupts
	short temp=5;
    while(1)
    {
		if (temp != getTemperature()){
			temp = getTemperature();
			LED_Toggle(0);
		}	
    }
}