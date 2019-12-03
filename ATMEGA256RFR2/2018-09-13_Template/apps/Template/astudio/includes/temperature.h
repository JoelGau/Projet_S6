/*
 * temperature.h
 *
 * Created: 2019-10-09 11:30:16
 *  Author: jgaud
 */ 


#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

void TWI_init();
void AT30TSE758_init();
short getTemperatureRaw();
void getTemperatureCelsius(short* celsius);
void getTemperatureCelsiusStd(float* celsius);

#endif /* TEMPERATURE_H_ */