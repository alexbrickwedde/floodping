#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "em4100.h"
#include "lcd.h"
#include <avr/eeprom.h>
#include <util/delay.h>

uint8_t KEYS[20][5] EEMEM =
{
{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 },

{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 },

{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 },

{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 },

{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00, 0x00, 0x00 }, };

uint8_t TYP[11] EEMEM =
{ " Floodping" };

int checkKey(uint8_t *d)
{
	if (d[0] == 0x00 && d[1] == 0x00 && d[2] == 0x00 && d[3] == 0x00 && d[4]
			== 0x00)
		return -1;
	uint8_t i;

	for (i = 0; i < 20; i++)
	{
		if (d[0] != eeprom_read_byte(&KEYS[i][0]))
			continue;
		if (d[1] != eeprom_read_byte(&KEYS[i][1]))
			continue;
		if (d[2] != eeprom_read_byte(&KEYS[i][2]))
			continue;
		if (d[3] != eeprom_read_byte(&KEYS[i][3]))
			continue;
		if (d[4] != eeprom_read_byte(&KEYS[i][4]))
			continue;
		return i;
	}
	return -1;
}

int saveKey(uint8_t *d)
{
	int8_t i = checkKey(d);
	if (i > -1)
		return -1;
	for (i = 0; i < 20; i++)
	{
		if (eeprom_read_byte(&KEYS[i][0]) != 0x00)
			continue;
		if (eeprom_read_byte(&KEYS[i][1]) != 0x00)
			continue;
		if (eeprom_read_byte(&KEYS[i][2]) != 0x00)
			continue;
		if (eeprom_read_byte(&KEYS[i][3]) != 0x00)
			continue;
		if (eeprom_read_byte(&KEYS[i][4]) != 0x00)
			continue;

		eeprom_write_block(d, &KEYS[i], 5);

		return 1;
	}
	return -1;
}
int deleteKey(uint8_t *d)
{
	int8_t i = checkKey(d);
	if (i < 0)
		return -1;
	d[0] = 0x00;
	d[1] = 0x00;
	d[2] = 0x00;
	d[3] = 0x00;
	d[4] = 0x00;
	eeprom_write_block(d, &KEYS[i], 5);
	return 0;
}

int main(void)
{
	uint8_t j;
	uint8_t tag[5];

	lcd_init();

	DDRD = 1 << DDD2;
	PORTD = 1 << PD2;

	DDRB |= (1 << DDB6) | (1 << DDB7);

	if (bit_is_set(PIND, PD4) && bit_is_set(PIND, PD5) && bit_is_set(PIND, PD6))
	{
		uint8_t tmp[] =
		{ 0x00, 0x00, 0x00, 0x00, 0x00 };
		uint8_t i;
		for (i = 0; i < 20; i++)
		{
			eeprom_write_block(tmp, &KEYS[i], 5);
			PORTB ^= (1 << PB6);
			PORTB ^= (1 << PB7);
			_delay_ms(50);
			//for (d=0; d<5000UL; d++);
		}
	}

	TCCR0B = 1 << CS01 | 1 << CS00; //Timer/Counter0 prescaler 64
	MCUCR |= 1 << ISC10; //Any logical change on INT1 generates an interrupt request
	GIMSK |= 1 << INT1; //External interrupt request 1 enable (demod_out from RFID chip)

	sei();

	while (1)
	{
		lcd_command(HOME);
		for (j = 0; j < 10; j++)
		{
			lcd_data(eeprom_read_byte(&TYP[j]));
		}
		if (bit_is_set(PIND, PD4) && bit_is_set(PIND, PD5) && bit_is_clear(PIND, PD6))
		{		PORTB |= (1 << PB6);
		  _delay_ms(500);
		  continue;
		}
		if (u2270_read_tag(tag))
		{
			if (bit_is_set(PIND, PD4) && bit_is_clear(PIND, PD5)
					&& bit_is_set(PIND, PD6))
				saveKey(tag);

			if (bit_is_clear(PIND, PD4) && bit_is_set(PIND, PD5)
					&& bit_is_set(PIND, PD6))
				deleteKey(tag);

			if (checkKey(tag) > -1)
				PORTB |= (1 << PB6);
			else
				PORTB |= (1 << PB7);

			lcd_command(HOME);
			for (j = 0; j < 5; j++)
			{
				uint8_t nibble = (tag[j] >> 4) & 0x0f;
				if (nibble > 9)
					nibble += 'A' - 10;
				else
					nibble += '0';
				lcd_data(nibble);

				nibble = tag[j] & 0x0f;
				if (nibble > 9)
					nibble += 'A' - 10;
				else
					nibble += '0';
				lcd_data(nibble);
			}
			_delay_ms(250);
		}
		_delay_ms(50);
		PORTB &= ~(1 << PB7);
		PORTB &= ~(1 << PB6);
	}
}
