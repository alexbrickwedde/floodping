/*
Title:	C source code file for U2270 RFID reader IC
Original Author:	Stefan Seegel / dahamm@gmx.net
Date:	30.08.2006
Version: 1.0
Free for noncommercial use
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "em4100.h"

static unsigned char data[8];
static volatile uint8_t flag;

#define MANCHESTER_LONG (F_CPU / F_RFID * 64 / TIMER0_PRESCALER)
#define MANCHESTER_SHORT (F_CPU / F_RFID * 64 / TIMER0_PRESCALER / 2)
#define MANCHESTER_MIDDLE (MANCHESTER_LONG + MANCHESTER_SHORT) / 2

SIGNAL (SIG_INTERRUPT1)
{
	static uint16_t sync;
	static uint8_t bitcount;
	static uint8_t insync = 0;
	static uint8_t old_cnt;
	static uint8_t parity = 0;
	static uint8_t vparity1 = 0;
	static uint8_t vparity2 = 0;
	static uint8_t vparity3 = 0;
	static uint8_t vparity4 = 0;
	if ((uint8_t)(TCNT0 - old_cnt) > MANCHESTER_MIDDLE)
	{
		old_cnt = TCNT0;

		sync <<= 1;
		bitcount++;
		
		if (bit_is_clear(PIND, PD3))
			sync |= 1;

		if ((sync & 0x3FF) == 0x1FF)
		{
			data[0] = 0xFF;
			bitcount = 1;
			insync = 1;
			parity = 0;
			vparity1 = 0;
			vparity2 = 0;
			vparity3 = 0;
			vparity4 = 0;
		}

		if (insync)
		{
			uint8_t bitcountMod = bitcount % 5;
			uint8_t syncBit = sync & 0x01;

			// Set Parity Values
			if (bitcount <= 50)
			{
				if (bitcountMod != 1)  parity  ^= syncBit; // Horizontal Parity
				if (bitcountMod == 2) vparity1 ^= syncBit; // Vertical Parity Bit 1
				if (bitcountMod == 3) vparity2 ^= syncBit; // Vertical Parity Bit 2
				if (bitcountMod == 4) vparity3 ^= syncBit; // Vertical Parity Bit 3
				if (bitcountMod == 0) vparity4 ^= syncBit; // Vertical Parity Bit 4
			}
			
			// Check Horizontal Parity
			if (bitcountMod == 1 && bitcount >= 6 && bitcount <= 51)
			{
				if (parity != syncBit)
					insync = 0;
				parity = 0;
			}

			// Check Vertical Parity Bit 1
			if (bitcount == 52)
			{
				if (vparity1 != syncBit)
					insync = 0;
				vparity1 = 0;
			}
			
			// Check Vertical Parity Bit 2
			if (bitcount == 53)
			{
				if (vparity2 != syncBit)
					insync = 0;
				vparity2 = 0;
			}
			
			// Check Vertical Parity Bit 3
			if (bitcount == 54)
			{
				if (vparity3 != syncBit)
					insync = 0;
				vparity3 = 0;
			}

			// Check Vertical Parity Bit 4
			if (bitcount == 55)
			{
				if (vparity4 != syncBit)
					insync = 0;
				vparity4 = 0;
			}

			if ((bitcount % 8) == 0)
			{
				data[bitcount / 8] = sync & 0xFF;

				if (bitcount == 56)
				{
					flag = 1;
					insync = 0;
					GIMSK &= ~(1<<INT1);
				}
			}
		}
	}
}

uint8_t u2270_read_tag(uint8_t *d)
{
	uint8_t timeout = 50;

	do
	{
		if (bit_is_set(TIFR, TOV0))
		{
			timeout--;
			TIFR |= 1<<TOV0; //Clear Overflow Flag
		}

	} while ((!flag) && (timeout > 0));
	

	if (!flag)
		return 0;


	flag = 0;
	uint8_t temp[8];
	memcpy(temp, data, 8);
	memset(data, 0, 8);
	GIMSK |= 1<<INT1;

	if (((temp[0] << 8 | temp[1]) & 0xFF80) != 0xFF80) //Check startbits
		return 0;
	
	if ((temp[7] & 0x01)) //Check stopbit
		return 0;

//11111111 11000110 00101111 10001100 01010011 00010000 00100101 00110110
//          DDDD DD DD DDDD  DDDD DDD D DDDD D DDD DDDD  DDDD DD DD DDDD
//          0000 00 00 1111  1111 222 2 2222 3 333 3333  4444 44 44

	d[0] = (temp[1] & 0x78) << 1 | (temp[1] & 0x03) << 2 | (temp[2] & 0xC0) >> 6;
	d[1] = (temp[2] & 0x1E) << 3 | (temp[3] & 0xF0) >> 4;
	d[2] = (temp[3] & 0x07) << 5 | (temp[4] & 0x80) >> 3 | (temp[4] & 0x3C) >> 2;
	d[3] = (temp[4] & 0x01) << 7 | (temp[5] & 0xE0) >> 1 | (temp[5] & 0x0F);
	d[4] = (temp[6] & 0x78) << 1 | (temp[6] & 0x03) << 2 | (temp[7] & 0xC0) >> 6;

	return 1;
}
