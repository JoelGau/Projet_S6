/*
 * CUMmunication.h
 *
 * Created: 2019-11-28 10:00:15 AM
 *  Author: Berthie
 */ 


#ifndef CUMMUNICATION_H_
#define CUMMUNICATION_H_
#include <stdint-gcc.h>

/*- Prototypes -------------------------------------------------------------*/
char Lis_UART();
void Ecris_UART(char data);
void Ecris_UART_string(char const * data, ...);
void init_UART(void);
uint8_t Lis_UART_string(char* buff, uint8_t ind);
void init_buff(char* buff);

#endif /* CUMMUNICATION_H_ */