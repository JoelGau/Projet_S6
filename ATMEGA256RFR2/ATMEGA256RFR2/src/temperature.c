/*
 * temperature.c
 *
 * Created: 2019-10-09 11:30:39
 *  Author: jgaud
 */ 

 #include "../includes/temperature.h"
 #include "../includes//miscellaneous.h"
 #include <twi_master.h>
 #include <twi_megarf.h>
 #include <twi_slave.h>
 #include <conf_twi.h>

 #include <atmega256rfr2_xplained_pro.h>
 #include <util/delay.h>
 #include <stdint-gcc.h>
 
 // TWI interface global variables
 #define TWI_BULLSHIT  &TWBR
 twi_master_options_t opt;
 twi_package_t package;


 void TWI_init() {
	// Defines ATMEGA256RFR2 as TWI Master
	twi_master_options_t opt = {
		.speed = TWI_SPEED_HZ,		// Baud rate
		.chip  = 0x50				// Master adress
	};
	opt.baud_reg = TWI_CLOCK_RATE(sysclk_get_cpu_hz(), opt.speed);
	/* Enable the peripheral clock for TWI module */
	sysclk_enable_peripheral_clock(TWI_BULLSHIT);
	twi_master_init(TWI_BULLSHIT, &opt);			
	Delay(1000);					// waits 1 ms
	// Sets AT30TSE758
	const uint8_t command[] = {0x60,0x00,0x00}; // 12 bits resolution temperature
	twi_package_t packet_write = {
		.addr         = 0b1001011,				// TWI slave memory address data
		.addr_length  = sizeof (uint8_t),		// TWI slave memory address data size
		.chip         = SLAVE_BUS_ADDR,			// TWI slave bus address
		.buffer       = (void *)command,		// transfer data source buffer
		.length       = sizeof(command)			// transfer data size (bytes)
	};
	while (twi_master_write(TWI_BULLSHIT, &packet_write) != TWI_SUCCESS);
 }

 short getTemperature() {
	 uint8_t data_received[2];
	 twi_package_t packet_read = {
		 .addr         = 0x4B,				// TWI slave memory address data
		 .addr_length  = sizeof (uint8_t),		// TWI slave memory address data size
		 .chip         = SLAVE_BUS_ADDR,		// TWI slave bus address
		 .buffer       = data_received,			// transfer data destination buffer
		 .length       = 2						// transfer data size (bytes)
	 };

	 while (twi_master_read(TWI_BULLSHIT, &packet_read) != TWI_SUCCESS) {
	 }
	uint16_t temperature = data_received[0] & data_received[1];
	temperature = temperature >> 4;
	return temperature;
 }
