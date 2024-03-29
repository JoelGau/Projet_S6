// FormConsole.cpp : Defines the entry point for the console application.
//

#include "Formulaire/Form.h"

//extern "C"
//{
//	PatientStruct patientInfo;
//	QuestionForm questionForm;
//}

int main()
{
	//Initialize an empty patient object and the question form.

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

	PatientStruct receivedPatient;
	char* outputPtr = inputPtr;
	deserializePatient(&receivedPatient, outputPtr);
	ValidateUserInput(&receivedPatient);
	return 0;
}

