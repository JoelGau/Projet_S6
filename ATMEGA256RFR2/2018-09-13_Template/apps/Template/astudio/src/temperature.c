/*
 * temperature.c
 *
 * Created: 2019-10-09 11:30:39
 *  Author: jgaud
 */ 

 #include "../includes/temperature.h"
 #include "../includes/at30ts.h"
 
 #include <string.h>
 #include <stdlib.h>
 #include <stdio.h>

 #include <twi_master.h>
 #include <twi_megarf.h>
 #include <twi_slave.h>
 #include <conf_twi.h>
 #include <delay.h>

 #include <atmega256rfr2_xplained_pro.h>
 #include <util/delay.h>
 #include <stdint-gcc.h>
 
 // TWI interface global variables
 #define TWI_BULLSHIT  &TWBR
 twi_master_options_t opt;
 twi_package_t package;


const uint8_t AT30TSE758_TempWrite [SLAVE_MEM_ADDR_LENGTH] = {
	0x96,
};

const uint8_t AT30TSE758_TempRead [SLAVE_MEM_ADDR_LENGTH] = {
	0x97,
};

 void TWI_init() {
	// Defines ATMEGA256RFR2 as TWI Master
	twi_master_options_t opt = {
		.speed = TWI_SPEED_HZ,		// Baud rate
		.chip  = SLAVE_BUS_ADDR		// Master adress
	};
	opt.baud_reg = TWI_CLOCK_RATE(sysclk_get_cpu_hz(), opt.speed);
	/* Enable the peripheral clock for TWI module */
	sysclk_enable_peripheral_clock(TWI_BULLSHIT);
	/* Initialize the TWI master driver. */
	twi_master_init(TWI_BULLSHIT, &opt);			
	delay_ms(100);					// waits 100 ms
	attach_device(0x96,AT30TSE758);
 }

 short getTemperatureRaw() {
	sensor_data_t data;
	read_temperature(&data);
	return data.temperature.raw_value;
 }
 
 void getTemperatureCelsius(short celsius[3]){
	sensor_data_t data;
	read_temperature(&data);
	celsius[0] = (uint16_t) data.temperature.sign;
	celsius[1] = (uint16_t) data.temperature.itemp;
	celsius[2] = data.temperature.ftemp;
 }
 
 void getTemperatureCelsiusStd(float* celsius)
 {
	 sensor_data_t data;
	 read_temperature(&data);
	 int tempVal = 0;
	 if((uint16_t) data.temperature.sign < 0)
		 tempVal = 0 - (uint16_t) data.temperature.itemp;
	 else
		 tempVal = (uint16_t) data.temperature.itemp;
	 
	 char tempString[40];
	 sprintf(tempString, "%d.%d",tempVal,(uint16_t)data.temperature.ftemp);
	 float decimalVal = atof(tempString); 
 }