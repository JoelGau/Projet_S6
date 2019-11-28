/*
 * CUMmunication.c
 *
 * Created: 2019-11-28 9:58:49 AM
 *  Author: Berthie
 */ 

#include <stdint-gcc.h>
#include <delay.h>
#include <sysclk.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <atmega256rfr2_xplained_pro/atmega256rfr2_xplained_pro.h>
#include <atmega256rfr2_xplained_pro/led.h>
#include <stdarg.h>

#include "../includes/CUMmunication.h"
 
 // PoC envois chaine de charactere	(envoi just une chaine (un nom) pour l'instant)
 extern char buff_nom[];
 extern uint8_t ind_buff;
 
 
 
 //FONCTIONS POUR L'UART

 char Lis_UART()
 {
	 char data = 0;

	 if(UCSR1A & (0x01 << RXC1))
	 {
		 data = UDR1;
	 }
	 return data;
 }

 void Lis_UART_string()
 {
	 char receivedUart = 0;

	 receivedUart = Lis_UART();
	 if (receivedUart)	{
		 Ecris_UART(receivedUart); // echo vers le terminal
		 buff_nom[ind_buff] = receivedUart;
		 if (receivedUart != 13)
		 {
			 ind_buff++;
		 }
		 receivedUart = 0;
	 }
 }


 void Ecris_UART(char data)
 {
	 UDR1 = data;
	 while(!(UCSR1A & (0x01 << UDRE1)));
 }

 void Ecris_UART_string(char const * data, ...)
 {
	 va_list args;
	 char buf[256];
	 unsigned int index = 0;
	 
	 va_start(args, data);
	 vsprintf(buf, data, args);
	 
	 while(buf[index] != 0x00 && index<256)
	 {
		 Ecris_UART(buf[index]);
		 index++;
	 }
	 
	 va_end(args);
 }

 void init_UART(void)
 {
	 //baud rate register = Fcpu / (16*baud rate - 1)
	 //baudrate = 9600bps //s'assurer que la fuse CLKDIV8 n'est pas activ�e dans les Fuses, sinon ca donne 1200bps
	 UBRR1H = 0x00;
	 UBRR1L = 53;
	 
	 UCSR1A = 0x00;
	 UCSR1B = 0x18; //receiver, transmitter enable, no parity
	 UCSR1C = 0x06; //8-bits per character, 1 stop bit
 }

 // Fonctions Wireless
 void init_buff_nom(void)
 {
	 for (int i = 0; i < 20; i++) {
		 buff_nom[i] = 0;
	 }
	 ind_buff = 0;
 }