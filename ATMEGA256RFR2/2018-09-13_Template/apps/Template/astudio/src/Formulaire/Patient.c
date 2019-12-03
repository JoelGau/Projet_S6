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

unsigned NewTemperatureMeasurement(struct MeasurementStruct *input, float inputVal)//, const char* inputName)
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
	input->isInitialized = false;
	
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

unsigned NewPatient(struct PatientStruct* input, char* inputName, char* inputID, unsigned inputAge, unsigned inputWeight)
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
	
	//input->sizeOfStruct += sizeof(input->sizeOfStruct);
	//input->sizeOfStruct += sizeof(input->isInitialized);
	//input->sizeOfStruct += sizeof(input->ID);// should be 12.
	//input->sizeOfStruct += sizeof(input->Name);// should be 32.
	//input->sizeOfStruct += 2*sizeof(input->Age);// age and weight
	//Has to be completed with the size of the measurement structure.
	return returnVal;
};
/// Returns the size of the serialized structure.
unsigned serializePatient(struct PatientStruct* patientStruct, char* serializedPtr)
{
	//Requires the sizeOfStruct to be completed, but the inputPtr is not instanciated.
	serializedPtr = malloc(patientStruct->sizeOfStruct*sizeof(char));//new char[patientStruct->sizeOfStruct]();
	unsigned i = 0;

	//Serialize the sizeOfStruct
	unsigned tempVal = patientStruct->sizeOfStruct;
	for(; i < sizeof(patientStruct->sizeOfStruct)/sizeof(char);i++)
	{
		serializedPtr[i] = tempVal & 0xff;
		tempVal >> sizeof(char);
	}
	bool tempVal = patientStruct->isInitialized;
	for(unsigned j = 0; j < sizeof(tempVal)/sizeof(char); j++,i++)
	{
		serializedPtr[i] = tempVal & 0xff;
		tempVal >> sizeof(char);
	}
	for(unsigned j = 0; j < 12;i++, j++)
	{
		serializedPtr[i] = patientStruct->ID[j];
	}
	for(unsigned j = 0; j < 32;i++, j++)
	{
		serializedPtr[i] = patientStruct->Name[j];
	}
	unsigned tempVal = patientStruct->Age;
	for(unsigned j = 0; j < sizeof(patientStruct->Age)/sizeof(char); j++,i++)
	{
		serializedPtr[i] = tempVal & 0xff;
		tempVal >> sizeof(char);
	}
	unsigned tempVal = patientStruct->Weight;
	for(unsigned j = 0; j < sizeof(patientStruct->Weight)/sizeof(char); j++,i++)
	{
		serializedPtr[i] = tempVal & 0xff;
		tempVal >> sizeof(char);
	}
	serializeMeasurementTemperature(patientStruct->Temperature,serializedPtr,i);
}

unsigned deserializePatient(struct PatientStruct* patientStruct, char* serializedPtr)
{
	unsigned i = 0;

	//Deserialize the sizeOfStruct
	unsigned tempVal = 0;//patientStruct->sizeOfStruct
	for(; i < sizeof(unsigned)/sizeof(char);i++)
	{
		if(i != 0)
			tempVal << sizeof(char);
		tempVal += serializedPtr[i];
	}
	patientStruct->sizeOfStruct = tempVal;

	for(unsigned j = 0; j < sizeof(bool)/sizeof(char); j++,i++)
	{
		if(j != 0)
			tempVal << sizeof(char);
		tempVal = serializedPtr[i];
	}
	bool tempVal = patientStruct->isInitialized;

	for(unsigned j = 0; j < 12;i++, j++)
	{
		patientStruct->ID[j] = serializedPtr[i];
	}
	for(unsigned j = 0; j < 32;i++, j++)
	{
		patientStruct->Name[j] = serializedPtr[i];
	}
	unsigned tempVal = 0;
	for(unsigned j = 0; j < sizeof(patientStruct->Age)/sizeof(char); j++, i++)
	{
		if(j != 0)
			tempVal << sizeof(char);
		tempVal +=serializedPtr[i];
	}
	unsigned tempVal = 0;
	for(unsigned j = 0; j < sizeof(patientStruct->Weight)/sizeof(char);j++,i++)
	{
		if(j != 0)
			tempVal << sizeof(char);
		tempVal +=serializedPtr[i];
	}
	deserializeMeasurementTemperature(patientStruct->Temperature,serializedPtr,i);
}

unsigned serializeMeasurementTemperature(struct MeasurementStruct measurementStruct, char* serializedPtr, unsigned currentIndex)
{
	unsigned i = currentIndex;
	unsigned tempVal = measurementStruct->sizeOfStruct;
	for(unsigned j = 0; j < sizeof(measurementStruct->sizeOfStruct)/sizeof(char); j++, i++)
	{
		serializedPtr[i] = tempVal & 0xff;
		tempVal >> sizeof(char);
	}
	bool tempVal2 = measurementStruct->isInitialized;
	for(unsigned j = 0; i < sizeof(measurementStruct->isInitialized)/sizeof(char); j++, i++)
	{
		tempVal2 += serializedPtr[i];
		tempVal2 >> sizeof(char);
	}
	bool tempVal = measurementStruct->isInitialized;
	for(unsigned j = 0; i < sizeof(tempVal)/sizeof(char); j++, i++)
	{
		serializedPtr[i] = tempVal & 0xff;
		tempVal >> sizeof(char);
	}
	for(unsigned j = 0; j < 32;i++, j++)
	{
		serializedPtr[i] = measurementStruct->MeasName[j];
	}
	float tempVal = measurementStruct->MeasVal;
	for(; i < sizeof(measurementStruct->MeasVal)/sizeof(char);i++)
	{
		serializedPtr[i] = tempVal & 0xff;
		tempVal >> sizeof(char);
	}
}

unsigned deserializeMeasurementTemperature(struct MeasurementStruct* measurementStruct, char* serializedPtr, unsigned currentIndex)
{
	unsigned i = currentIndex;

	unsigned tempVal = 0;//measurementStruct->sizeOfStruct;
	for(; i < sizeof(measurementStruct->sizeOfStruct)/sizeof(char);i++)
	{
		if(i != 0)
			tempVal << sizeof(char);
		tempVal += serializedPtr[i];
	}
	measurementStruct->sizeOfStruct = tempVal; 

	bool tempVal2 = 0;
	for(; i < sizeof(tempVal2)/sizeof(char);i++)
	{
		if(i != 0)
			tempVal2 << sizeof(char);
		tempVal2 += serializedPtr[i];
	}
	measurementStruct->isInitialized = tempVal2;

	for(unsigned j = 0; j < 32;i++, j++)
	{
		 measurementStruct->MeasName[j] =serializedPtr[i];
	}

	float tempVal3 = 0;
	for(; i < sizeof(measurementStruct->MeasVal)/sizeof(char);i++)
	{
		if(i != 0)
			tempVal3 << sizeof(char);
		tempVal3 += serializedPtr[i];;
	}
	measurementStruct->MeasVal =tempVal3;
}
