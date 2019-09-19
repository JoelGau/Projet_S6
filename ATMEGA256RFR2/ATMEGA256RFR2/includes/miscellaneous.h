/*
 * miscellaneous.h
 *
 * Created: 2019-09-19 16:29:47
 *  Author: jgaud
 *
 * Created: 6/17/2013 12:45:11 PM
 *  Author: Scott_Schmit
 */ 


#ifndef MISCELLANEOUS_H_
#define MISCELLANEOUS_H_

#include <stdint-gcc.h>

void Board_Init(void);
void Timer_Init(void);
void LED_Toggle(void);
void Delay(uint16_t us);
void wdt_disable(void);



#endif /* MISCELLANEOUS_H_ */