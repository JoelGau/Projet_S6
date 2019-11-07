/*
 * Patient.c
 *
 * Created: 2019-11-05 9:51:54 AM
 *  Author: charles-frederick
 */ 
#include "Patient.h"
#include <stdio.h>
#include <string.h>
//#include <stdbool.h>

unsigned NewTemperatureMeasurement(MeasurementStruct *input, float inputVal)//, const char* inputName)
{
	unsigned returnVal = 0;
	strcpy(input->MeasName,"Temperature");
	/*
	if(strcmp(("Temperature",input)))
	{
		memset(input->MeasName, '\0', sizeof(input->MeasName));
		strcpy(input->MeasName, inputName); //Should be "Temperature"
		returnVal = 0;
	}
	else
		returnVal = 1;*/
	if(inputVal > 0 && inputVal < 50)
	{
		input->MeasVal = inputVal; //In degree C
		returnVal = 0;
	}
	else
		returnVal = 1;
	input->isInitialized = true;
	
	return returnVal;
}

/*
unsigned NewPatient(PatientStruct *input)
{
	//Initialize the parameters to 0, awaiting further details
	if(input->isInitialized == false)
	{
		input->ID = 0;
		input->Age = 0
		input->Weight = 0;
		return 0;
	}
	else
		return 1;
};*/

unsigned NewPatient(PatientStruct* input, char* inputName, char* inputID, unsigned inputAge, unsigned inputWeight)
{
	//Initialize the parameters to values given
	unsigned returnVal = 0;
	if(input->isInitialized == false)
	{
		strcpy(input->Name,inputName);
		strcpy(input->ID,inputID);
		input->Age = inputAge;
		input->Weight = inputWeight;
		input->isInitialized = true;
		returnVal = 0;
	}
	else
		returnVal = 1;
		
	return returnVal;
};
