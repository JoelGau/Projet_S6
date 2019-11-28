/*
 * CUMmunication.h
 *
 * Created: 2019-11-28 10:00:15 AM
 *  Author: Berthie
 */ 


#ifndef CUMMUNICATION_H_
#define CUMMUNICATION_H_

/*- Prototypes -------------------------------------------------------------*/
char Lis_UART();
void Ecris_UART(char data);
void Ecris_UART_string(char const * data, ...);
void init_UART(void);
void Lis_UART_string(void);
void init_buff_nom(void);

#endif /* CUMMUNICATION_H_ */