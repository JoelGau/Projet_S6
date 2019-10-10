/*
 * 
 */ 


#include "../includes/miscellaneous.h"
#include "../includes/temperature.h"

#include <stdint-gcc.h>
#include <avr/interrupt.h>
#include <stdio.h>

int main(void)
{
	Board_Init();
	Timer_Init();
	TWI_init();
	
	sei(); // Enable global interrupts
	short temp=5;
	short i;
    while(1)
    {
		// Wait 0.5 seconds
		if (temp != getTemperature()){
			temp = getTemperature();
			LED_Toggle;
		}
		for(i=0; i<250; i++){
			Delay(50000); //us
		}		
    }
}