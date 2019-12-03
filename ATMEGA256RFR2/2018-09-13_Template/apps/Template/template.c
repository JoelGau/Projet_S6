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

#include "astudio/src/Formulaire/Form.h"
#include "astudio/src/Formulaire/Patient.h"

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
//#define RECEIVER
#define SENDER


/*- Types ------------------------------------------------------------------*/
// Put your type definitions here

/*- Prototypes -------------------------------------------------------------*/
// Put your function prototypes here

void SYS_Init(void);


/*- Variables --------------------------------------------------------------*/
// Put your variables here
uint8_t receivedWireless;	//cette variable deviendra 1 lorsqu'un nouveau paquet aura �t� recu via wireless (et copi� dans "PHY_DataInd_t ind"
							//il faut la mettre a 0 apres avoir g�r� le paquet; tout message recu via wireless pendant que cette variable est a 1 sera jet�
char buff_nom[20] = {};
uint8_t ind2 = 0;
							
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
	
}



/*************************************************************************//**
*****************************************************************************/
int main(void)
{
	board_init();
	TWI_init();
	sei(); // Enable global interrupts
	//short temp[3] = {0,0,0};
	SYS_Init();
	//sysclk_init();

		#ifdef SENDER
		while(1)
		{
			PatientStruct patientInfo;
			QuestionForm questionForm;
			
			//Sync the QuestionForm object with the current state of the patient info
			InitQuestionForm(&questionForm, &patientInfo);
			//Run the form, which acquires the informations if necessary.
			do
			RunQuestionForm(&questionForm);
			while (!ValidateUserInput(&(questionForm.initiatorPatient)));

			char inputPtr[84 * (sizeof(char))] = { 0 }; //questionForm.initiatorPatient.sizeOfStruct
			serializePatient(&(questionForm.initiatorPatient), inputPtr);
			Ecris_Wireless(inputPtr, 84);

			Ecris_UART_string("\n\rEnvoi des informations via sans fil. En attente de la confirmation...");
			char outputPtr[2] = { 0 };
			receivedWirelessBLOQUANT(outputPtr);
			if(*outputPtr == 1)
				Ecris_UART_string("\n\rResultat de l'accuse de reception: Reussi");
			else
				Ecris_UART_string("\n\rResultat de l'accuse de reception: Erreur.");
		}
		#endif

		#ifdef RECEIVER
		while(1)
		{
			PatientStruct receivedPatient;

			Ecris_UART_string("\n\rEn attente d'informations...\n\r");
			char outputPtr[84 * (sizeof(char))] = { 0 };
			receivedWirelessBLOQUANT(outputPtr);
			deserializePatient(&receivedPatient, outputPtr);
			bool receptionReussie = ValidateUserInput(&receivedPatient);
			Ecris_Wireless(&receptionReussie,1);
		}
		#endif
		return 0;
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



