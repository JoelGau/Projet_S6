/*
 * miscellaneous.c
 *
 * Created: 2019-09-19 18:16:56
 *  Author: jgaud
 */ 

 #include "../includes/miscellaneous.h"

 #include <stdint-gcc.h>
 #include <avr/io.h>
 #include <avr/interrupt.h>

 volatile uint8_t CTC_flag;

 ISR(TIMER1_COMPA_vect) {
	 CTC_flag = 1;
 }

 void Board_Init(void) {
	 
	 cli();
	 wdt_disable();
	 
	 DDRB = 0x10; //PB4 output
	 PORTB |= 0x10; //Turn off LED
 }

 void Timer_Init(void) {
	 
	 TIMSK1 = 0x00; //Disable timer interrupts
	 TCCR1A = 0x00; //Timer not connected to any pins
	 TCCR1B = 0x09; //CTC mode; Timer_Rate = System_CLK = 1MHz
	 // 1 tick = 1 us
 }

 void LED_Toggle(void) {
	 PORTB ^= 0x10; //Toggle PB4
 }

 void Delay(uint16_t us) {
	 CTC_flag = 0; //Clear CTC Interrupt flag
	 TCNT1 = 0x0000; //Clear timer
	 OCR1A = us; //Load compare value with desired delay in us
	 TIMSK1 = 0x02; //Enable OCIE1A Interrupt
	 while(!CTC_flag); //wait for the designated number of us
 }

 void wdt_disable(void) {
	 // Disable watchdog timer
	 asm("wdr");
	 MCUSR = 0;
	 WDTCSR |= (1 << WDCE) | (1 << WDE);
	 WDTCSR = 0x00;
 }