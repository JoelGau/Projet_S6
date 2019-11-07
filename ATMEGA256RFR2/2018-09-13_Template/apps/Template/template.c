/**
 * \file template.c
 *
 * \brief Empty application template
 *
 * Copyright (C) 2012-2014, Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 * Modification and other use of this code is subject to Atmel's Limited
 * License Agreement (license.txt).
 *
 * $Id: template.c 9267 2014-03-18 21:46:19Z ataradov $
 *
 */

/*- Includes ---------------------------------------------------------------*/
#include "sys.h"
#include "phy.h"
#include "astudio/includes/temperature.h"
#include "astudio/includes/at30ts.h"

#include <stdint-gcc.h>
#include <delay.h>
#include <sysclk.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <atmega256rfr2_xplained_pro/atmega256rfr2_xplained_pro.h>
#include <atmega256rfr2_xplained_pro/led.h>
#include <stdarg.h>
//#include <string> 


	

/*- Definitions ------------------------------------------------------------*/
// Put your preprocessor definitions here

/*- Types ------------------------------------------------------------------*/
// Put your type definitions here

/*- Prototypes -------------------------------------------------------------*/
// Put your function prototypes here
char Lis_UART();
void Ecris_UART(char data);
void Ecris_UART_string(char const * data, ...);
void init_UART(void);
void Lis_UART_string(void);
void SYS_Init(void);
void init_buff_nom(void);




/*- Variables --------------------------------------------------------------*/
// Put your variables here
uint8_t receivedWireless;	//cette variable deviendra 1 lorsqu'un nouveau paquet aura été recu via wireless (et copié dans "PHY_DataInd_t ind"
							//il faut la mettre a 0 apres avoir géré le paquet; tout message recu via wireless pendant que cette variable est a 1 sera jeté
// PoC envois chaine de charactere	(envoi just une chaine (un nom) pour l'instant)					
char buff_nom[20];
uint8_t ind_buff = 0;

PHY_DataInd_t ind; //cet objet contiendra les informations concernant le dernier paquet qui vient de rentrer


//debug (0 = pas debug, 1= 
int debug = 1;


/*- Implementations --------------------------------------------------------*/

// Put your function implementations here

/*************************************************************************//**
*****************************************************************************/
static void APP_TaskHandler(void)
{
	Lis_UART_string(); // lis les informations du clavier, et les met dans la variable global "buff_nom" et incrémente la variable globale "ind_buff"
	
	// envoi la variable gloable "buff_nom" et la variable globale "ind_buff"
	if (buff_nom[ind_buff] == 13 && ind_buff > 0)
	{
		if (debug)
		{
			Ecris_UART_string("\n\r");
			Ecris_UART_string(buff_nom);
			Ecris_UART_string("\n\r");
		}
		
		Ecris_Wireless(buff_nom, ind_buff);
		init_buff_nom();
	}


	// reception d'une chaine de caractere
  if(receivedWireless == 1) //est-ce qu'un paquet a été recu sur le wireless? 
  {
	uint8_t received_data[20] = {};
	int i = 0;

	// remplir l'array avec les valeurs recues
	while (i < ind.size)
	{
		received_data[i] = ind.data[i];
		i++;
	}
	
	// affiche le message recu
	Ecris_UART_string("\n\r");
	Ecris_UART_string(received_data);
	Ecris_UART_string( "\n\rnew trame! size: %d, RSSI: %ddBm\n\r", ind.size, ind.rssi );
	Ecris_UART_string("\n\r");
	receivedWireless = 0; 

  }
}



/*************************************************************************//**
*****************************************************************************/
int main(void)
{
	//sysclk_init();
	board_init();
	TWI_init();
	sei(); // Enable global interrupts
	short temp[3] = {0,0,0};
	SYS_Init();
   
	while (1)
	{
		//getTemperatureCelsius(temp);
		//delay_ms(250);
		PHY_TaskHandler(); //stack wireless: va vérifier s'il y a un paquet recu
		APP_TaskHandler(); //l'application principale roule ici
	}
}



//FONCTION D'INITIALISATION
/*************************************************************************//**
*****************************************************************************/
void SYS_Init(void)
{
	receivedWireless = 0;
	wdt_disable(); 
	init_UART();
	PHY_Init(); //initialise le wireless
	PHY_SetRxState(1); //TRX_CMD_RX_ON+
	init_buff_nom();
}
//



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
	//baudrate = 9600bps //s'assurer que la fuse CLKDIV8 n'est pas activée dans les Fuses, sinon ca donne 1200bps
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
