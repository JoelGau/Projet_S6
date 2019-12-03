/*
 * Form.h
 *
 * Created: 2019-11-05 10:42:06 AM
 *  Author: charles-frederick
 */ 

#pragma once
#include "Patient.h"
/*
class QuestionForm
{
	public:
		//Public variables
		
		
		//Public functions	
		QuestionForm(PatientStruct *inputPatient)
		unsigned Run();
	private:
		//Private variables
	PatientStruct* initiatorPatient;
	bool hasPatientInfo = false;
	bool hasTemperatureInfo = false;
		
		//Private Functions
		void inquirePatientInfo();
		void inquireTemperatureInfo();	
};*/

//typedef struct _testStruct
//{
//	int a;
//	innerStruct theInnerStruct;
//} testStruct;
//
//void aTest(testStruct *theStruct, innerStruct *theStruct2) {};

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