/*
 * Form.c
 *
 * Created: 2019-11-05 10:29:23 AM
 *  Author: charles-frederick
 */ 

//#include "../stdafx.h"
#include "Form.h"
//#include "Patient.h"

//#include "astudio/includes/temperature.h"

//Define FORM_CONSOLE_TEST to 1 when we want to test the console output/interactions
#define FORM_CONSOLE_TEST 1
//#define  WRITE_UART 1
//#define  WRITE_WIRELESS 1

//#include <stdbool.h>
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

//How we should use the form in the main
/*
void main()
{
	//Initialize an empty patient object and the question form.
	PatientStruct patientInfo;
	QuestionForm questionForm;

	//Sync the QuestionForm object with the current state of the patient info
	InitQuestionForm(&questionForm, &patientInfo);
	//Run the form, which acquires the informations if necessary.
	RunQuestionForm(&questionForm);
}

*/

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

int size(char *ptr)
{
	//variable used to access the subsequent array elements.
	int offset = 0;
	//variable that counts the number of elements in your array
	int count = 0;

	//While loop that tests whether the end of the array has been reached
	while (*(ptr + offset) != '\0')
	{
		//increment the count variable
		++count;
		//advance to the next element of the array
		++offset;
	}
	//return the size of the array
	return count;
}

static int getLine (char *prmpt, char *buff, size_t sz) 
{
	int ch, extra;

	// Get line with buffer overrun protection.
	if (prmpt != NULL) {
		printf ("%s", prmpt);
		fflush (stdout);
	}
	if (fgets (buff, sz, stdin) == NULL)
	return NO_INPUT;

	// If it was too long, there'll be no newline. In that case, we flush
	// to end of line so that excess doesn't affect the next call.
	if (buff[strlen(buff)-1] != '\n') {
		extra = 0;
		while (((ch = getchar()) != '\n') && (ch != EOF))
		extra = 1;
		return (extra == 1) ? TOO_LONG : OK;
	}

	// Otherwise remove newline and give string back to caller.
	buff[strlen(buff)-1] = '\0';
	return OK;
}

int InitQuestionForm(QuestionForm *q, PatientStruct *p)
{
	//Acquire the patient struct used to create the appropriate form
	q->initiatorPatient = *p;
	
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
	if(q->initiatorPatient.Temperature.isInitialized == true)
	{
		//Already has temperature values, which is odd.
		q->hasTemperatureInfo = true;
	}
	else
	{
		//Do not have temperature values, flag for acquisition
		q->hasTemperatureInfo = false;
	}
	return 0;
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
	if(q->hasPatientInfo)
	{
		#ifdef FORM_CONSOLE_TEST
			printf("Dossier client complet.");
		#endif
		#ifdef WRITE_WIRELESS
			//Ecris_wireless_string("Dossier client complet.");
		#endif
		#ifdef WRITE_UART
			Ecris_UART_string("Dossier client complet.");
		#endif
	}
	else
	{
		#ifdef FORM_CONSOLE_TEST
			printf("Dossier client a remplir.\n");
		#endif
		#ifdef WRITE_WIRELESS
			//Ecris_wireless_string("Dossier client a remplir.");
		#endif
		#ifdef WRITE_UART
			Ecris_UART_string("Dossier client a remplir.");
		#endif
		InquirePatientInfo(q);
	}
	
	if(q->hasTemperatureInfo)
	{
		InquireTemperatureInfo(q);
		#ifdef FORM_CONSOLE_TEST
			printf("Temperature deja prise (Wut).");
		#endif
		#ifdef WRITE_WIRELESS
			//Ecris_wireless_string("Temperature acquise.");
		#endif
		#ifdef WRITE_UART
			Ecris_UART_string("Temperature deja prise (Wut).");
		#endif
	}
	else
	{
		#ifdef FORM_CONSOLE_TEST
			bool hasTemperature = false;
			while(!hasTemperature)
			{
				//Acquire the information
				char inputTemp[10];// = lis_wireless_string();
				///////////////////////////
				#ifdef FORM_CONSOLE_TEST
				int rc = getLine("Veuillez indiquer votre temperature (Celsius):", inputTemp, sizeof(inputTemp));
				if (rc == NO_INPUT)
				{
					// Extra NL since my system doesn't output that on EOF.
					printf ("\nNo input\n");
				}
			
				if (rc == TOO_LONG)
				{
					printf("Input too long [%s]\n", inputTemp);
				}
			
				printf ("OK [%s]\n", inputTemp);
				#endif
				#ifdef WRITE_WIRELESS
					//Ecris_wireless_string("Veuillez indiquer votre age:");
					//inputAge = 0;//lis_wireless_string();
				#endif
				//////////////////////////
			
				if(strlen(inputTemp) <= 10)
				{
					float temp = 0;
					sscanf(inputTemp,"%f", &temp);
					NewTemperatureMeasurement(&(q->initiatorPatient.Temperature), temp);
					hasTemperature = true;
				}
				else
					#ifdef FORM_CONSOLE_TEST
								printf("Temperature invalide.");
					#endif
					#ifdef WRITE_WIRELESS
							a = 1;
							//Ecris_wireless_string("Numero invalide.\n");
					#endif
					#ifdef WRITE_UART
							Ecris_UART_string("Temperature deja prise (Wut).");
					#endif
				//Ecris_wireless_string("Age invalide (3 caracteres maximum).\n");
			}
		#endif
	}
}
bool ValidateUserInput(PatientStruct * p)
{
	//Here we print out the patient information to confirm the entered data, if there is a problem offer to reset.
	char inputArray[2];
	#ifdef FORM_CONSOLE_TEST
		printf("\n-------------------------------------------------\nLes informations suivantes sont-elles correctes?\n");
		printf("NAS:\t%.*s\n", 12, p->ID);
		printf("Nom:\t%s\n", p->Name);
		printf("Age:\t%u\n", p->Age);
		printf("Poids:\t%u\n", p->Weight);
		printf("Temp:\t%d\n-------------------------------------------------\n", (uint8_t)p->Temperature.MeasVal);

		bool inputOK = false;
		while(!inputOK)
		{
			int rc = getLine("Correct? (Y/N)", inputArray, sizeof(inputArray));
			if (rc == NO_INPUT) 
			{
				// Extra NL since my system doesn't output that on EOF.
				printf ("\nNo input\n");
			}

			if (rc == TOO_LONG)
			{
				printf("Input too long [%s]\n", inputArray);
			}
			printf ("OK [%s]\n", inputArray);

			if(strlen(inputArray) == 1 && (inputArray[0] == 'Y'|| inputArray[0] == 'N'))
			{
				inputOK = true;
			}
			else
			{
				printf("Reponse invalide.");
			}			
		}
		if (inputArray[0] == 'Y')
		{
			p->sizeOfStruct = sizeof(p->isInitialized) + 2 * sizeof(p->Age) + 12 + 32;
			return true;
		}
		else if (inputArray[0] == 'N')
			return false;
		else
		{
			printf("WutAnswer?");
			return false;
		}
	#endif
	#ifdef WRITE_WIRELESS
		//Ecris_wireless_string("Temperature acquise.");
	#endif
	#ifdef WRITE_UART
		Ecris_UART_string("Les informations suivantes sont-elles correctes?");
	#endif
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
void InquirePatientInfo(QuestionForm* q)
{
	//This function is in charge of acquiring the generic patient information to fill the profile.
	bool NAMacquired = false;
	char inputArray[20];
	while(!NAMacquired)
	{
		#ifdef FORM_CONSOLE_TEST
			int rc = getLine("Veuillez indiquer votre numero d''assurance maladie:", inputArray, sizeof(inputArray));
			if (rc == NO_INPUT) 
			{
				// Extra NL since my system doesn't output that on EOF.
				printf ("\nNo input\n");
			}

			if (rc == TOO_LONG)
			{
				printf("Input too long [%s]\n", inputArray);
			}

			printf ("OK [%s]\n", inputArray);
		#endif
		#ifdef WRITE_WIRELESS
			//Ecris_wireless_string("Veuillez indiquer votre numero d''assurance maladie:");
			//inputArray = 0;//lis_wireless_string();
		#endif
		#ifdef WRITE_UART
			Ecris_UART_string("Temperature deja prise (Wut).");
		#endif

		//printf("%d", size(inputArray));
		if(strlen(inputArray) == 12)
		{
			strcpy(q->initiatorPatient.ID, inputArray);
			NAMacquired = true;
		}
		else
		{
			#ifdef FORM_CONSOLE_TEST
				printf("Numero invalide.");
			#endif
			#ifdef WRITE_WIRELESS
				a = 1;
				//Ecris_wireless_string("Numero invalide.\n");
			#endif
			#ifdef WRITE_UART
				Ecris_UART_string("Numero invalide.");
			#endif
		}			
	}
	
	bool NameAcquired = false;
	while(!NameAcquired)
	{
		//Acquire the information
		/////////////////////////////
		char inputName[32];
		#ifdef FORM_CONSOLE_TEST
			int rc = getLine("Veuillez indiquer votre nom en caracteres standards:", inputName, sizeof(inputName));
			if (rc == NO_INPUT)
			{
				// Extra NL since my system doesn't output that on EOF.
				printf ("\nNo input\n");
			}

			if (rc == TOO_LONG)
			{
				printf("Input too long [%s]\n", inputName);
			}

			printf ("OK [%s]\n", inputName);
		#endif
		#ifdef WRITE_WIRELESS
			//Ecris_wireless_string("Veuillez indiquer votre nom en caracteres standards:");;
			//inputArray = 0;//lis_wireless_string();
		#endif
		#ifdef WRITE_UART
			Ecris_UART_string("Temperature deja prise (Wut).");
		#endif

		/////////////////////////////

		//char* inputArray = 0;//lis_wireless_string();
		if(strlen(inputName) <= 32)
		{
			strcpy(q->initiatorPatient.Name, inputName);
			NameAcquired = true;
		}
		else
			#ifdef FORM_CONSOLE_TEST
						printf("Nom invalide (trop long).");
			#endif
			#ifdef WRITE_WIRELESS
					a = 1;
					//Ecris_wireless_string("Numero invalide.\n");
			#endif
			#ifdef WRITE_UART
					Ecris_UART_string("Temperature deja prise (Wut).");
			#endif
		//Ecris_wireless_string("Nom invalide (32 caracteres maximum).\n");
	}
	
	bool AgeAcquired = false;
	while(!AgeAcquired)
	{
		//Acquire the information
		char inputAge[3];// = lis_wireless_string();
		///////////////////////////
		#ifdef FORM_CONSOLE_TEST
		int rc = getLine("Veuillez indiquer votre age:", inputAge, sizeof(inputAge));
		if (rc == NO_INPUT)
		{
			// Extra NL since my system doesn't output that on EOF.
			printf ("\nNo input\n");
		}

		if (rc == TOO_LONG)
		{
			printf("Input too long [%s]\n", inputAge);
		}

		printf ("OK [%s]\n", inputAge);
		#endif
		#ifdef WRITE_WIRELESS
			//Ecris_wireless_string("Veuillez indiquer votre age:");
			//inputAge = 0;//lis_wireless_string();
		#endif
		//////////////////////////

		if(strlen(inputAge) <= 3)
		{
			unsigned age = 0;
			sscanf(inputAge,"%d", &age);
			q->initiatorPatient.Age = age;
			AgeAcquired = true;
		}
		else
			#ifdef FORM_CONSOLE_TEST
						printf("Age invalide.");
			#endif
			#ifdef WRITE_WIRELESS
					a = 1;
					//Ecris_wireless_string("Numero invalide.\n");
			#endif
			#ifdef WRITE_UART
					Ecris_UART_string("Temperature deja prise (Wut).");
			#endif
		//Ecris_wireless_string("Age invalide (3 caracteres maximum).\n");
	}

	bool WeightAcquired = false;
	while(!WeightAcquired)
	{

		//Acquire the information
		char inputWeight[20];// = lis_wireless_string();
		///////////////////////////
		#ifdef FORM_CONSOLE_TEST
			int rc = getLine("Veuillez indiquer votre poids (lbs):", inputWeight, sizeof(inputWeight));
			if (rc == NO_INPUT)
			{
				// Extra NL since my system doesn't output that on EOF.
				printf ("\nNo input\n");
			}

			if (rc == TOO_LONG)
			{
				printf("Input too long [%s]\n", inputWeight);
			}

			printf ("OK [%s]\n", inputWeight);
		#endif
		#ifdef WRITE_WIRELESS
			//Ecris_wireless_string("Veuillez indiquer votre poid en entier (lbs):");
			//inputWeight = 0;//lis_wireless_string();
		#endif
		//////////////////////////

		if(strlen(inputWeight) <= 3)
		{
			unsigned weight = 0;
			sscanf(inputWeight,"%d", &weight);
			q->initiatorPatient.Weight = weight;
			WeightAcquired = true;
		}
		else
			#ifdef FORM_CONSOLE_TEST
				printf("Poids invalide.");
			#endif
			#ifdef WRITE_WIRELESS
				a = 1;
				//Ecris_wireless_string("Numero invalide.\n");
			#endif
			#ifdef WRITE_UART
				Ecris_UART_string("Temperature deja prise (Wut).");
			#endif
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

void InquireTemperatureInfo(QuestionForm *q)
{
	//This function is in charge of acquiring the patient's temperature information to fill the profile.

	bool TemperatureAcquired = false;
	while(!TemperatureAcquired)
	{
		//Acquire the information
		char inputTemp[3];// = lis_wireless_string();
		char temperatureVal = 0;
		///////////////////////////
		#ifdef FORM_CONSOLE_TEST
			printf("Veuillez entrer votre temperature en valeur decimale:");
			sscanf(inputTemp,"%d", &temperatureVal);
		#endif
		#ifdef WRITE_WIRELESS
			//Ecris_wireless_string("Veuillez mettre votre doigts sur le capteur et appuyez sur Enter");
			
			getTemperatureCelsiusStd(&temperatureVal);
		#endif
		#ifdef WRITE_UART

		#endif
		//////////////////////////
		TemperatureAcquired = true;		
		NewTemperatureMeasurement(&(q->initiatorPatient.Temperature),temperatureVal);
		q->initiatorPatient.sizeOfStruct += q->initiatorPatient.Temperature.sizeOfStruct;
	}
}