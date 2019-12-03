/*
 * Patient.h
 *
 * Created: 2019-11-05 9:52:05 AM
 *  Author: charles-frederick
 */ 
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdint.h>

typedef struct _innerStruct
{
	int b;
} innerStruct;

unsigned char * serialize_float(unsigned char *buffer, float value);
void deserialize_float(unsigned char* buffer, float* value);

//struct _MeasurementStruct, _PatientStruct;
typedef struct _MeasurementStruct
{
	unsigned sizeOfStruct;// = sizeof(isInitialized) + sizeof(float) + 32;
	bool isInitialized;// = false;
	char MeasName[32];
	char MeasVal[10];
} MeasurementStruct;

typedef struct _PatientStruct
{
	bool isInitialized;// = false;
	char ID[12];
	char Name[32];
	unsigned Age;
	unsigned Weight;
	
	//Measurements stored. Should not initialy have values before the form requires it.
	MeasurementStruct Temperature;
	unsigned sizeOfStruct;// = sizeof(isInitialized) + 2 * sizeof(Age) + 12 + 32;
	
} PatientStruct;

unsigned NewTemperatureMeasurement(MeasurementStruct* input, char inputVal);
unsigned NewPatient(PatientStruct* input, char* inputName, char* inputID, unsigned inputAge, unsigned inputWeight);

unsigned serializePatient(PatientStruct* patientStruct, char* serializedPtr);
unsigned deserializePatient(PatientStruct* patientStruct, char* serializedPtr);
unsigned serializeMeasurementTemperature(MeasurementStruct* measurementStruct, char* serializedPtr, unsigned currentIndex);
unsigned deserializeMeasurementTemperature(MeasurementStruct* measurementStruct, char* serializedPtr, unsigned currentIndex);
//#endif /* PATIENT_H_ */
