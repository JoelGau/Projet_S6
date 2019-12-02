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
#include "../includes/temperature.h"
#include "../includes/at30ts.h"
#include "../includes/CUMmunication.h"
#include "../src/Formulaire/Form.h"

#include <stdint-gcc.h>
#include <delay.h>
#include <sysclk.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <atmega256rfr2_xplained_pro/atmega256rfr2_xplained_pro.h>
#include <atmega256rfr2_xplained_pro/led.h>
#include <stdarg.h>



/*- Definitions ------------------------------------------------------------*/
// Put your preprocessor definitions here

/*- Types ------------------------------------------------------------------*/
// Put your type definitions here

/*- Prototypes -------------------------------------------------------------*/
// Put your function prototypes here

void SYS_Init(void);


/*- Variables --------------------------------------------------------------*/
// Put your variables here
uint8_t receivedWireless;	//cette variable deviendra 1 lorsqu'un nouveau paquet aura été recu via wireless (et copié dans "PHY_DataInd_t ind"
							//il faut la mettre a 0 apres avoir géré le paquet; tout message recu via wireless pendant que cette variable est a 1 sera jeté
							
// PoC envois chaine de charactere	(envoi just une chaine (un nom) pour l'instant)					


PHY_DataInd_t ind; //cet objet contiendra les informations concernant le dernier paquet qui vient de rentrer


//debug (0 = pas debug, 1= 
int debug = 1;


/*- Implementations --------------------------------------------------------*/

// Put your function implementations here

/*************************************************************************//**
*****************************************************************************/
static void APP_TaskHandler(void)
{
	//QuestionForm formulaire_patient;
	//PatientStruct patient;
	
	//initQuestionForm(formulaire_patient, patient);
	
	//RunQuestionForm(formulaire_patient);
		
	char buff_nom[100] = {0};
	uint8_t ind2 = 0;
	
	init_buff(buff_nom);
	
	ind2 = Lis_UART_string(buff_nom); // lis les informations du clavier, et les met dans la variable global "buff_nom" et incrémente la variable globale "ind_buff"
	ind2 = ind2-1;
	
	// envoi la variable gloable "buff_nom" et la variable globale "ind_buff"
	if ((buff_nom[ind2] == 13))
	{
		Ecris_UART_string("\n\r");
		Ecris_UART_string(buff_nom);
		Ecris_UART_string("\n\r");
		Ecris_Wireless(buff_nom, ind2+1);
		init_buff(buff_nom);
	}

	// reception d'une chaine de caractere
  if(receivedWireless == 1) //est-ce qu'un paquet a été recu sur le wireless? 
  {
	uint8_t received_data[100] = {0};
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
}
//



