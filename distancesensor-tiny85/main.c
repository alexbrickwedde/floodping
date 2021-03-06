/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * main.c - demo main module to test irmp decoder
 *
 * Copyright (c) 2009-2010 Frank Meyer - frank(at)fli4l.de
 *
 * ATMEGA88 @ 8 MHz
 *
 * Fuses: lfuse: 0xE2 hfuse: 0xDC efuse: 0xF9
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include        "usiTwiSlave.h"

// Note: The LSB is the I2C r/w flag and must not be used for addressing!
#define         SLAVE_ADDR_ATTINY       0b00100100

//####################################################################### Macros

#define uniq(LOW,HEIGHT)        ((HEIGHT << 8)|LOW)                       // Create 16 bit number from two bytes
#define LOW_BYTE(x)             (x & 0xff)                                          // Get low byte from 16 bit number
#define HIGH_BYTE(x)            ((x >> 8) & 0xff)                         // Get high byte from 16 bit number
#define sbi(ADDRESS,BIT)        ((ADDRESS) |= (1<<(BIT)))       // Set bit
#define cbi(ADDRESS,BIT)        ((ADDRESS) &= ~(1<<(BIT)))// Clear bit
#define toggle(ADDRESS,BIT)     ((ADDRESS) ^= (1<<BIT)) // Toggle bit
#define bis(ADDRESS,BIT)        (ADDRESS & (1<<BIT))              // Is bit set?
#define bic(ADDRESS,BIT)        (!(ADDRESS & (1<<BIT)))         // Is bit clear?
//#################################################################### Variables

uint8_t byte1, byte2;
uint16_t buffer;
uint8_t high, low = 0; // Variables used with uniq (high and low byte)

uint16_t AdcRead(uint8_t channel) {
	ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC)) {
	}
	return ADCW;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MAIN: main routine
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
int main(void) {

	ADMUX |= (1 << ADLAR) | 0b00000011;
	ADCSRA |= (1 << ADEN) | (0 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // | (1 << ADFR);

	cli();
	usiTwiSlaveInit(SLAVE_ADDR_ATTINY); // TWI slave init
	sei ();

	int uiLightCmd = 0;
	int uiTempLight = 0;
	int uiTimeoutCounter = 0;


	enum State {IDLE, Step1Near, Step1Far, Step2Near, Step2Far, Step3Near, Step3Far};
	enum State uiState = IDLE;

	for (;;) {
		uiTimeoutCounter++;
		_delay_ms(10);
		wdt_reset();

		int uiNewDistance = ((AdcRead(3) >> 6) + (AdcRead(3) >> 6)
				+ (AdcRead(3) >> 6) + (AdcRead(3) >> 6)) >> 2;

		if (uiNewDistance < 64) {
		} else if (uiNewDistance < 128) {
			uiTimeoutCounter = 0;
			switch(uiState)
			{
			case IDLE:
				uiState = Step1Far;
				break;
			case Step1Near:
				uiState = Step2Far;
				break;
			case Step2Near:
			case Step3Near:
				uiState = Step3Far;
				uiTempLight = 1;
				break;
			default:
				break;
			}
		} else if (uiNewDistance < 256) {
		} else if (uiNewDistance < 512) {
			uiTimeoutCounter = 0;
			switch(uiState)
			{
			case IDLE:
				uiState = Step1Near;
				break;
			case Step1Far:
				uiState = Step2Near;
				break;
			case Step2Far:
			case Step3Far:
				uiState = Step3Near;
				uiTempLight = 2;
				break;
			default:
				break;
			}
		} else {
		}

		if(uiTimeoutCounter > 100)
		{
			uiTempLight = 0;
			switch(uiState)
			{
			case Step3Far:
				uiLightCmd = 1;
				break;
			case Step3Near:
				uiLightCmd = 2;
				break;
			default:
				break;
			}
			uiState = IDLE;
			uiTimeoutCounter = 100;
		}


		cli();
		if (rxbuffer[3] == 0xaa) {
			rxbuffer[3] = 0;
			uiLightCmd = 0;
			uiState = IDLE;
		}

		txbuffer[0] = uiLightCmd;
		txbuffer[1] = uiTempLight;
//		txbuffer[2] = uiLightCmd;
//		txbuffer[3] = uiTempLight;

		sei();

	}
}
