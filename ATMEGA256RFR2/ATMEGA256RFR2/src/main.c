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
	short temp[3] = {0,0,0};
    while(1)
    {
		getTemperatureCelsius(temp);
		delay_ms(250);
    }
}