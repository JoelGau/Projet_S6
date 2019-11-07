/*
 * Form.c
 *
 * Created: 2019-11-05 10:29:23 AM
 *  Author: charles-frederick
 */ 

#include "Form.h"
#include "Patient.h"
#include "astudio/includes/temperature.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
/*
QuestionForm::QuestionForm(PatientStruct* inputPatient)
{
	//Acquire the patient struct used to create the appropriate form
	initiatorPatient = inputPatient;	
	
	if(inputPatient->isInitialized == true)
	{
		//The patient object already has the main informations entered.
		hasPatientInfo = true;
	}
	else
	{
		//Patient object has not been completed yet. Flag for acquisition
		hasPatientInfo = false;
	}
	
	//Inquire for the temperature data
	if(inputPatient->Temperature->isInitialized == true)
	{
		//Already has temperature values, which is odd.
		hasTemperatureInfo = true;
	}
	else
	{
		//Do not have temperature values, flag for acquisition
		hasTemperatureInfo = false;
	}
}*/

void initQuestionForm(QuestionForm *q, PatientStruct *p)
{
	//Acquire the patient struct used to create the appropriate form
	q->initiatorPatient = p;
	
	if(p->isInitialized == true)
	{
		//The patient object already has the main informations entered.
		q->hasPatientInfo = true;
	}
	else
	{
		//Patient object has not been completed yet. Flag for acquisition
		q->hasPatientInfo = false;
	}
	
	//Inquire for the temperature data
	if(p->Temperature->isInitialized == true)
	{
		//Already has temperature values, which is odd.
		q->hasTemperatureInfo = true;
	}
	else
	{
		//Do not have temperature values, flag for acquisition
		q->hasTemperatureInfo = false;
	}
}
/*
unsigned QuestionForm::Run()
{
	if(hasPatientInfo)
		//Ecris_wireless_string("Dossier client complet.");
	else
	{
		inquirePatientInfo();
		//Ecris_wireless_string("Dossier client remplis.");
	}
	
	if(hasTemperatureInfo)
		//Ecris_wireless_string("Temperature deja prise (Wut).");
	else
	{
		inquireTemperatureInfo;
		//Ecris_wireless_string("Temperature acquise.");
	}
	
}*/

void RunQuestionForm(QuestionForm* q)
{
	unsigned a,b;
	if(q->hasPatientInfo)
		a = 1;
	//Ecris_wireless_string("Dossier client complet.");
	else
	{
		inquirePatientInfo(q);
		//Ecris_wireless_string("Dossier client remplis.");
	}
	
	if(q->hasTemperatureInfo)
		b = 1;
	//Ecris_wireless_string("Temperature deja prise (Wut).");
	else
	{
		inquireTemperatureInfo(q);
		//Ecris_wireless_string("Temperature acquise.");
	}
}
/*
 void QuestionForm::inquirePatientInfo()
{
	//This function is in charge of acquiring the generic patient information to fill the profile.
	bool NAMacquired = false;
	while(!NAMacquired)
	{
		//Ecris_wireless_string("Veuillez indiquer votre numero d''assurance maladie:");
		//Acquire the information
		char* inputArray = 0;//lis_wireless_string();
		if(strlen(inputArray) == 12)
		{
			strcpy(inputArray,initiatorPatient->ID);
			NAMacquired = true
		}
		else
			//Ecris_wireless_string("Numero invalide.\n");
	}
	
	bool NameAcquired = false;
	while(!NameAcquired)
	{
		//Ecris_wireless_string("Veuillez indiquer votre nom en caracteres standards:");
		//Acquire the information
		char* inputArray = 0;//lis_wireless_string();
		if(strlen(inputArray) <= 32)
		{
			strcpy(inputArray,initiatorPatient->Name);
			NameAcquired = true
		}
		else
		//Ecris_wireless_string("Nom invalide (32 caracteres maximum).\n");
	}
	
	bool AgeAcquired = false;
	while(!AgeAcquired)
	{
		//Ecris_wireless_string("Veuillez indiquer votre age:");
		//Acquire the information
		char* inputArray = 0;//lis_wireless_string();
		if(strlen(inputArray) <= 3)
		{
			unsigned age = 0;
			sscanf(inputArray,"%d", &age);
			strcpy(age,initiatorPatient->Age);
			AgeAcquired = true
		}
		else
			//Ecris_wireless_string("Age invalide (3 caracteres maximum).\n");
	}

	bool WeightAcquired = false;
	while(!WeightAcquired)
	{
		//Ecris_wireless_string("Veuillez indiquer votre poid en entier (lbs):");
		//Acquire the information
		char* inputArray = 0;//lis_wireless_string();
		if(strlen(inputArray) <= 3)
		{
			unsigned weight = 0;
			sscanf(inputArray,"%d", &weight);
			strcpy(weight,initiatorPatient->Weight);
			WeightAcquired = true
		}
		else
			//Ecris_wireless_string("Poids invalide (3 caracteres maximum).\n");
	}
}
*/
void inquirePatientInfo(QuestionForm* q)
{
	//This function is in charge of acquiring the generic patient information to fill the profile.
	bool NAMacquired = false;
	unsigned a,b,c,d;
	while(!NAMacquired)
	{
		//Ecris_wireless_string("Veuillez indiquer votre numero d''assurance maladie:");
		//Acquire the information
		char* inputArray = 0;//lis_wireless_string();
		if(strlen(inputArray) == 12)
		{
			strcpy(inputArray,q->initiatorPatient->ID);
			NAMacquired = true;
		}
		else
			a = 1;
		//Ecris_wireless_string("Numero invalide.\n");
	}
	
	bool NameAcquired = false;
	while(!NameAcquired)
	{
		//Ecris_wireless_string("Veuillez indiquer votre nom en caracteres standards:");
		//Acquire the information
		char* inputArray = 0;//lis_wireless_string();
		if(strlen(inputArray) <= 32)
		{
			strcpy(inputArray,q->initiatorPatient->Name);
			NameAcquired = true;
		}
		else
			b = 1;
		//Ecris_wireless_string("Nom invalide (32 caracteres maximum).\n");
	}
	
	bool AgeAcquired = false;
	while(!AgeAcquired)
	{
		//Ecris_wireless_string("Veuillez indiquer votre age:");
		//Acquire the information
		char* inputArray = 0;//lis_wireless_string();
		if(strlen(inputArray) <= 3)
		{
			unsigned age = 0;
			sscanf(inputArray,"%d", &age);
			q->initiatorPatient->Age = age;
			AgeAcquired = true;
		}
		else
			c = 1;
		//Ecris_wireless_string("Age invalide (3 caracteres maximum).\n");
	}

	bool WeightAcquired = false;
	while(!WeightAcquired)
	{
		//Ecris_wireless_string("Veuillez indiquer votre poid en entier (lbs):");
		//Acquire the information
		char* inputArray = 0;//lis_wireless_string();
		if(strlen(inputArray) <= 3)
		{
			unsigned weight = 0;
			sscanf(inputArray,"%d", &weight);
			q->initiatorPatient->Weight = weight;
			WeightAcquired = true;
		}
		else
			d = 1;
		//Ecris_wireless_string("Poids invalide (3 caracteres maximum).\n");
	}	
}

/*
void QuestionForm::inquireTemperatureInfo()
{
	//This function is in charge of acquiring the patient's temperature information to fill the profile.
	bool TemperatureAcquired = false;
	while(!TemperatureAcquired)
	{
		//Ecris_wireless_string("Veuillez mettre votre doigts sur le capteur et appuyez sur Enter");
		char inputVal =0;// lis_wireless()[1];
		if(inputVal == 13)
		{
			TemperatureAcquired = true;
			
			float temperatureVal = 0;
			getTemperatureCelsiusStd(temperatureVal);			
		}			
	}
}
*/

void inquireTemperatureInfo(QuestionForm *q)
{
	//This function is in charge of acquiring the patient's temperature information to fill the profile.
	bool TemperatureAcquired = false;
	while(!TemperatureAcquired)
	{
		//Ecris_wireless_string("Veuillez mettre votre doigts sur le capteur et appuyez sur Enter");
		char inputVal =0;// lis_wireless()[1];
		if(inputVal == 13)
		{
			TemperatureAcquired = true;
			
			float temperatureVal = 0;
			getTemperatureCelsiusStd(&temperatureVal);
			NewTemperatureMeasurement(q->initiatorPatient->Temperature,temperatureVal);
		}
	}
}