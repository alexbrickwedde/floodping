// ======================================================================
// USBtiny template application
//
// Copyright 2006-2010 Dick Streefland
//
// This is free software, licensed under the terms of the GNU General
// Public License as published by the Free Software Foundation.
// ======================================================================

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#ifndef cbi
#define cbi(sfr, bit)     (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit)     (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define LED_AN(LED)     (PORTD |=  (1<<(LED)))
#define LED_AUS(LED)    (PORTD &= ~(1<<(LED)))
#define LED_TOGGLE(LED) (PORTD ^=  (1<<(LED)))
#define LED1            PB2
#define LED2            PB3

#include "usb.h"

#define MATCH_ROM       0x55
#define SKIP_ROM        0xCC
#define SEARCH_ROM      0xF0

#define CONVERT_T       0x44            // DS1820 commands
#define READ            0xBE
#define WRITE           0x4E
#define EE_WRITE        0x48
#define EE_RECALL       0xB8

#define SEARCH_FIRST    0xFF            // start new search
#define PRESENCE_ERR    0xFF
#define DATA_ERR        0xFE
#define LAST_DEVICE     0x00            // last device found
//                      0x01 ... 0x40: continue searching

#ifndef cbi
#define cbi(sfr, bit)     (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit)     (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define W1_PIN  PB1
#define W1_IN   PINB
#define W1_OUT  PORTB
#define W1_DDR  DDRB

#define uchar unsigned char
#define uint unsigned int
#define bit uchar
#define idata
#define code

bit w1_reset(void) {
	bit err;

	W1_OUT &= ~(1 << W1_PIN);
	W1_DDR |= 1 << W1_PIN;
	_delay_us(480); // 480 us
	cli();
	W1_DDR &= ~(1 << W1_PIN);
	_delay_us(66);
	err = W1_IN & (1 << W1_PIN); // no presence detect
	sei();
	_delay_us(480 - 66);
	if ((W1_IN & (1 << W1_PIN)) == 0) // short circuit
		err = 1;
	return err;
}

uchar w1_bit_io(bit b) {
	cli();
	W1_DDR |= 1 << W1_PIN;
	_delay_us(1);
	if (b)
		W1_DDR &= ~(1 << W1_PIN);
	_delay_us(15 - 1);
	if ((W1_IN & (1 << W1_PIN)) == 0)
		b = 0;
	_delay_us(60 - 15);
	W1_DDR &= ~(1 << W1_PIN);
	sei();
	return b;
}

uint w1_byte_wr(uchar b) {
	uchar i = 8, j;
	do {
		j = w1_bit_io(b & 1);
		b >>= 1;
		if (j)
			b |= 0x80;
	} while (--i);
	return b;
}

uint w1_byte_rd(void) {
	return w1_byte_wr(0xFF);
}

uchar w1_rom_search(uchar diff, uchar idata *id) {
	uchar i, j, next_diff;
	bit b;

	if (w1_reset())
		return PRESENCE_ERR; // error, no device found
	w1_byte_wr(SEARCH_ROM); // ROM search command
	next_diff = LAST_DEVICE; // unchanged on last device
	i = 8 * 8; // 8 bytes
	do {
		j = 8; // 8 bits
		do {
			b = w1_bit_io(1); // read bit
			if (w1_bit_io(1)) { // read complement bit
				if (b) // 11
					return DATA_ERR; // data error
			} else {
				if (!b) { // 00 = 2 devices
					if (diff > i || ((*id & 1) && diff != i)) {
						b = 1; // now 1
						next_diff = i; // next pass 0
					}
				}
			}
			w1_bit_io(b); // write bit
			*id >>= 1;
			if (b) // store bit
				*id |= 0x80;
			i--;
		} while (--j);
		id++; // next byte
	} while (i);
	return next_diff; // to continue search
}

void w1_command(uchar command, uchar idata *id) {
	uchar i;
	w1_reset();
	if (id) {
		w1_byte_wr(MATCH_ROM); // to a single device
		i = 8;
		do {
			w1_byte_wr(*id);
			id++;
		} while (--i);
	} else {
		w1_byte_wr(SKIP_ROM); // to all devices
	}
	w1_byte_wr(command);
}

void start_meas(void) {
	if (W1_IN & 1 << W1_PIN) {
		w1_command(CONVERT_T, 0);
		W1_OUT |= 1 << W1_PIN;
		W1_DDR |= 1 << W1_PIN; // parasite power on
	}
}

unsigned long x1 = 0;
unsigned char xdata[8];

// ----------------------------------------------------------------------
// Handle a non-standard SETUP packet.
// ----------------------------------------------------------------------
extern byte_t usb_setup(byte_t data[8]) {
	x1 = data[1];
	if(x1==3)
	{
		for (int z=0;z<7;z++)
			data[z] = xdata[z];
		return 7;
	}
	return 2;
}

// ----------------------------------------------------------------------
// Handle an IN packet. (USBTINY_CALLBACK_IN==1)
// ----------------------------------------------------------------------
extern byte_t usb_in(byte_t* data, byte_t len) {
	return 0;
}

// ----------------------------------------------------------------------
// Handle an OUT packet. (USBTINY_CALLBACK_OUT==1)
// ----------------------------------------------------------------------
extern void usb_out(byte_t* data, byte_t len) {
}

// ----------------------------------------------------------------------
// Main
// ----------------------------------------------------------------------
int main(void) {
	uchar id[8], diff;
	uchar i = 0;

	usb_init();
	for (;;) {
		usb_poll();

		if (x1 == 1) {
			x1 = 0;
			start_meas();
		} else if (x1 == 2) {
			x1 = 0;
			i = 0;

			for (diff = SEARCH_FIRST; diff != LAST_DEVICE && i < 6;) {
				diff = w1_rom_search(diff, id);
				xdata[3] = diff;

				if (diff >= DATA_ERR) {
					xdata[0] = 0x00;
					break;
				}
				if (id[0] == 0x28 || id[0] == 0x10) {
					w1_byte_wr(READ);
					xdata[i+1] = w1_byte_rd();
					xdata[i+2] = w1_byte_rd();
					i+=2;
					xdata[0] = i>>1;
				}
			}
		}
	}
}
