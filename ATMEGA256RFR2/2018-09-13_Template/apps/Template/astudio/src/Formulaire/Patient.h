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
	
} PatientStruct;

unsigned NewTemperatureMeasurement(MeasurementStruct* input, float inputVal);
unsigned NewPatient(PatientStruct* input, char* inputName, char* inputID, unsigned inputAge, unsigned inputWeight);

#endif /* PATIENT_H_ */