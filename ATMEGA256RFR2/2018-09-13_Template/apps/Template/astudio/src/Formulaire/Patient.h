/*
 * Patient.h
 *
 * Created: 2019-11-05 9:52:05 AM
 *  Author: charles-frederick
 */ 
#ifndef PATIENT_H_
#define PATIENT_H_

#include <stdbool.h>

//struct _MeasurementStruct, _PatientStruct;
typedef struct _MeasurementStruct
{
	unsigned sizeOfStruct = sizeof(isInitialized)+sizeof(float)+32;
	bool isInitialized;// = false;
	char MeasName[32];
	float MeasVal;
} MeasurementStruct;

typedef struct _PatientStruct
{
	bool isInitialized;// = false;
	char ID[12];
	char Name[32];
	unsigned Age;
	unsigned Weight;
	
	//Measurements stored. Should not initialy have values before the form requires it.
	MeasurementStruct* Temperature;
	unsigned sizeOfStruct = sizeof(isInitialized)+2*sizeof(Age)+12+32;
	
} PatientStruct;

unsigned NewTemperatureMeasurement(struct MeasurementStruct* input, float inputVal);
unsigned NewPatient(struct PatientStruct* input, char* inputName, char* inputID, unsigned inputAge, unsigned inputWeight);

unsigned serializePatient(struct PatientStruct patientStruct, char* serializedPtr);
unsigned deserializePatient(struct PatientStruct* patientStruct, char* serializedPtr);
unsigned serializeMeasurementTemperature(struct MeasurementStruct measurementStruct, char* serializedPtr, unsigned currentIndex);
unsigned deserializeMeasurementTemperature(struct MeasurementStruct* measurementStruct, char* serializedPtr, unsigned currentIndex);
#endif /* PATIENT_H_ */
