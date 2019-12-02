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
#include "sys.h"
#include "phy.h"

 // PoC envois chaine de charactere	(envoi just une chaine (un nom) pour l'instant)
extern char buff_nom[100];
extern uint8_t ind2;
extern PHY_DataInd_t ind;

 
 
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
 

 uint8_t Lis_UART_string(char *buff, uint8_t ind)
 {
	char receivedUart;
	receivedUart = '0';
	uint8_t ind_buff = ind;

	while (receivedUart != 13)
	{
		if(UCSR1A & (0x01 << RXC1))
		{
			receivedUart = UDR1;
			buff[ind_buff] = receivedUart;
			ind_buff++;
			Ecris_UART(receivedUart); // echo vers le terminal	
		}
	}
	
	Ecris_UART_string("\n\r");
	Ecris_UART_string(buff);
	Ecris_UART_string("\n\r");
	return ind_buff;
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
	 //baudrate = 9600bps //s'assurer que la fuse CLKDIV8 n'est pas activée dans les Fuses, sinon ca donne 1200bps
	 UBRR1H = 0x00;
	 UBRR1L = 53;
	 
	 UCSR1A = 0x00;
	 UCSR1B = 0x18; //receiver, transmitter enable, no parity
	 UCSR1C = 0x06; //8-bits per character, 1 stop bit
 }

 // Fonctions Wireless
 void init_buff(char* buff)
 {
	 for (int i = 0; i < 100; i++) {
		 buff[i] = '\0';
	 }
 }
 
 
 void receivedWirelessBLOQUANT(uint8_t * received_data)
 {
 	while (receivedWireless != 1)
 	{
	 	PHY_TaskHandler(); //stack wireless: va vérifier s'il y a un paquet recu
 	}
 		
 	int i = 0;

 	// remplir l'array avec les valeurs recues
 	while (i < ind.size)
 	{
	 	received_data[i] = ind.data[i];
	 	i++;
 	}
	receivedWireless = 0;	
 }