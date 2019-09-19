/*
 * 
 */ 


#include "../includes/miscellaneous.h"

#include <stdint-gcc.h>
#include <avr/interrupt.h>

int main(void)
{
	uint8_t i;
	Board_Init();
	Timer_Init();
	
	sei(); // Enable global interrupts
	
    while(1)
    {
        LED_Toggle();
		// Wait 0.5 seconds
		for(i=0; i<250; i++){
			Delay(50000); //us
		}
    }
}