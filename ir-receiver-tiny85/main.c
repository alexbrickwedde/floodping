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
#include "irmp.h"

#include        "usiTwiSlave.h"

// Note: The LSB is the I2C r/w flag and must not be used for addressing!
#define         SLAVE_ADDR_ATTINY       0b00110100

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

#ifndef F_CPU
#error F_CPU unkown
#endif

#define F_INTERRUPT   10000                                                     // 10000 interrupts per second
void timer_init(void) {
#define PRESCALER 8
	TCCR0A = (1 << WGM01); /* IR polling timer */
	TCCR0B = (1 << CS01); // switch CTC Mode on, set prescaler to 1

	// may adjust IR polling rate here to optimize IR receiving:
	OCR0A = (F_CPU / F_INTERRUPT / PRESCALER) - 1; // compare value: 1/10000 of CPU frequency

	// enable Timer1 for IR polling
	TIMSK = 1 << OCIE0A; // Timer0A ISR activate

}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * timer 1 compare handler, should be called every 1/10000 sec
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void TIMER0_COMPA_vect(void) __attribute__((interrupt));
void TIMER0_COMPA_vect(void) {
	irmp_ISR();
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * MAIN: main routine
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
int main(void) {
	cli();

	usiTwiSlaveInit(SLAVE_ADDR_ATTINY); // TWI slave init

	IRMP_DATA irmp_data;
	irmp_init(); // initialize rc5
	timer_init();

	sei ();

	for (;;) {

		_delay_ms(1);

		cli();
		if(rxbuffer[3] == 0xaa)
		{
			cli();
			rxbuffer[3] = 0;
			txbuffer[0] = 0;
			txbuffer[1] = 0;
			txbuffer[2] = 0;
			txbuffer[3] = 0;
			sei();
		}
		sei();

		if (irmp_get_data(&irmp_data)) {
			cli();
			txbuffer[0] = irmp_data.command >> 8;
			txbuffer[1] = irmp_data.command & 0xff;
			txbuffer[2] = irmp_data.address >> 8;
			txbuffer[3] = irmp_data.address & 0xff;
			sei();
			_delay_ms(500);
		}
	}
	return 0;
}
