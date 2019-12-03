/*
 * Patient.c
 *
 * Created: 2019-11-05 9:51:54 AM
 *  Author: charles-frederick
 */ 

#define _CRT_SECURE_NO_WARNINGS

#include "Patient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdbool.h>

unsigned char * serialize_float(unsigned char *buffer, float value)
{
	unsigned int ivalue = *((unsigned int*)&value); // warning assumes 32-bit "unsigned int"
	buffer[0] = ivalue >> 24;
	buffer[1] = ivalue >> 16;
	buffer[2] = ivalue >> 8;
	buffer[3] = ivalue;
	return buffer + 4;
}

void deserialize_float(unsigned char* buffer, float* value)
{
	unsigned int ivalue = 0;
	ivalue += buffer[3];
	ivalue = (ivalue << 8) +buffer[2];
	ivalue = (ivalue << 8) + buffer[1];
	ivalue = (ivalue << 8) + buffer[0];
	*value = *((float*)&ivalue);
}

unsigned NewTemperatureMeasurement(MeasurementStruct *input, uint8_t inputVal)//, const char* inputName)
{
	input->sizeOfStruct = sizeof(input->isInitialized) + sizeof(float) + 32;
	unsigned returnVal = 0;
	strcpy(input->MeasName,"Temperature");
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

unsigned NewPatient(PatientStruct* input, char* inputName, char* inputID, unsigned inputAge, unsigned inputWeight)
{
	input->sizeOfStruct = sizeof(input->isInitialized) + 2 * sizeof(input->Age) + 12 + 32;
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
/// Returns the size of the serialized structure.
unsigned serializePatient(PatientStruct* patientStruct, char* serializedPtr)
{
	//Requires the sizeOfStruct to be completed, but the inputPtr is not instanciated.
	//serializedPtr = malloc(( patientStruct->sizeOfStruct) * (sizeof(char)) );//new char[patientStruct->sizeOfStruct]();
	unsigned i = 0;

	//Serialize the sizeOfStruct
	unsigned tempVal = patientStruct->sizeOfStruct;
	for(; i < sizeof(patientStruct->sizeOfStruct)/sizeof(char);i++)
	{
		serializedPtr[i] = tempVal & 0xff;
		tempVal = tempVal >> sizeof(char);
	}
	bool tempVal1 = patientStruct->isInitialized;
	for(unsigned j = 0; j < sizeof(tempVal1)/sizeof(char); j++,i++)
	{
		serializedPtr[i] = tempVal1 & 0xff;
		tempVal1 = tempVal1 >> sizeof(char);
	}
	for(unsigned j = 0; j < 12;i++, j++)
	{
		serializedPtr[i] = patientStruct->ID[j];
	}
	for(unsigned j = 0; j < 32;i++, j++)
	{
		serializedPtr[i] = patientStruct->Name[j];
	}
	tempVal = patientStruct->Age;
	//for(unsigned j = 0; j < sizeof(unsigned)/sizeof(char); j++,i++)
	//{
		//serializedPtr[i] = (tempVal & 0xff);
		//tempVal = tempVal >> sizeof(char);
	//}
	//tempVal = patientStruct->Weight;
	//for(unsigned j = 0; j < sizeof(unsigned)/sizeof(char); j++,i++)
	//{
		//serializedPtr[i] = (tempVal & 0xff);
		//tempVal = tempVal >> sizeof(char);
	//}
	serializedPtr[i] = (char)patientStruct->Age;
	i++;
	serializedPtr[i] = (char)patientStruct->Weight;
	i++;
	serializeMeasurementTemperature(&(patientStruct->Temperature),serializedPtr,i);
	return 0;
}

unsigned deserializePatient(PatientStruct* patientStruct, char* serializedPtr)
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

	bool tempVal1 = false;
	for(unsigned j = 0; j < sizeof(bool)/sizeof(char); j++,i++)
	{
		if(j != 0)
			tempVal1 << sizeof(char);
		tempVal1 += serializedPtr[i];
	}
	patientStruct->isInitialized = tempVal1;

	for(unsigned j = 0; j < 12;i++, j++)
	{
		patientStruct->ID[j] = serializedPtr[i];
	}
	for(unsigned j = 0; j < 32;i++, j++)
	{
		patientStruct->Name[j] = serializedPtr[i];
	}
	tempVal = 0;

	tempVal = (uint8_t)serializedPtr[i];
	i++;
	patientStruct->Age = tempVal;
	tempVal = 0;

	patientStruct->Weight = (uint8_t)serializedPtr[i];// tempVal;
	i++;
	deserializeMeasurementTemperature(&(patientStruct->Temperature),serializedPtr,i);
	return 0;
}

unsigned serializeMeasurementTemperature(MeasurementStruct* measurementStruct, char* serializedPtr, unsigned currentIndex)
{
	unsigned i = currentIndex;
	//unsigned tempVal = measurementStruct->sizeOfStruct;
	//for(unsigned j = 0; j < sizeof(measurementStruct->sizeOfStruct)/sizeof(char); j++, i++)
	//{
		//serializedPtr[i] = tempVal & 0xff;
		//tempVal >> sizeof(char);
	//}
	//bool tempVal2 = measurementStruct->isInitialized;
	//for(unsigned j = 0; i < sizeof(measurementStruct->isInitialized)/sizeof(char); j++, i++)
	//{
		//tempVal2 += serializedPtr[i];
		//tempVal2 >> sizeof(char);
	//}
	//for(unsigned j = 0; j < 32;i++, j++)
	//{
		//serializedPtr[i] = measurementStruct->MeasName[j];
	//}
	serializedPtr[i] = measurementStruct->MeasVal;
	i++;
	return 0;
}

unsigned deserializeMeasurementTemperature(MeasurementStruct* measurementStruct, char* serializedPtr, unsigned currentIndex)
{
	unsigned i = currentIndex;

	//unsigned tempVal = 40;//measurementStruct->sizeOfStruct;
	//for(; i < sizeof(measurementStruct->sizeOfStruct)/sizeof(char);i++)
	//{
		//if(i != 0)
			//tempVal << sizeof(char);
		//tempVal += serializedPtr[i];
	//}
	//measurementStruct->sizeOfStruct = tempVal; 
//
	//bool tempVal2 = 0;
	//for(; i < sizeof(tempVal2)/sizeof(char);i++)
	//{
		//if(i != 0)
			//tempVal2 << sizeof(char);
		//tempVal2 += serializedPtr[i];
	//}
	//measurementStruct->isInitialized = tempVal2;
//
	//for(unsigned j = 0; j < 32;i++, j++)
	//{
		 //measurementStruct->MeasName[j] =serializedPtr[i];
	//}
	measurementStruct->MeasVal = serializedPtr[i];
	i++;
	return 0;
}
