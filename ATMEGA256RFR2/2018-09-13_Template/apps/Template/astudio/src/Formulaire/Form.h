/*
 * Form.h
 *
 * Created: 2019-11-05 10:42:06 AM
 *  Author: charles-frederick
 */ 

#ifndef FORM_H_
#define FORM_H_

#include <stdbool.h>
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

typedef struct _QuestionForm
{
	PatientStruct* initiatorPatient;
	bool hasPatientInfo;
	bool hasTemperatureInfo;
} QuestionForm;

void initQuestionForm(QuestionForm *q, PatientStruct *p);

void inquirePatientInfo(QuestionForm *q);
void inquireTemperatureInfo(QuestionForm *q);

void RunQuestionForm(QuestionForm *q);

#endif /* FORM_H_ */