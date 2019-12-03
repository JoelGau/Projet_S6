/*
 * Form.h
 *
 * Created: 2019-11-05 10:42:06 AM
 *  Author: charles-frederick
 */ 

#pragma once
#include "Patient.h"

typedef struct _QuestionForm
{
	PatientStruct initiatorPatient;
	bool hasPatientInfo;
	bool hasTemperatureInfo;
} QuestionForm;


int InitQuestionForm(QuestionForm *q, PatientStruct *p);

void InquirePatientInfo(QuestionForm *q);
void InquireTemperatureInfo(QuestionForm *q);

void RunQuestionForm(QuestionForm *q);
bool ValidateUserInput(PatientStruct *p);


//#endif /* FORM_H_ */