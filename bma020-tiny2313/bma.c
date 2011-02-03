#include "global.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <util/delay.h>


#define BMA_PORT	PORTD
#define BMA_DDR		DDRD
#define BMA_PIN		PIND

#define SDI		4
#define SCK		3
#define CS		2
#define SDO    5
#define FSK    1

unsigned int BMA_trans(unsigned int wert)
{
	unsigned int werti = 0;
	unsigned char i;

	sbi(BMA_PORT, SCK);
	cbi(BMA_PORT, CS);
	cbi(BMA_PORT, SCK);
	for (i = 0; i < 16; i++)
	{
		if (wert & 0x8000)
			sbi(BMA_PORT, SDI);
		else
			cbi(BMA_PORT, SDI);
		_delay_us(0.1);
		werti <<= 1;
		if (BMA_PIN & (1 << SDO))
			werti |= 1;
		sbi(BMA_PORT, SCK);
		wert <<= 1;
		_delay_us(0.3);
		cbi(BMA_PORT, SCK);
//		_delay_us(0.3);
	}
	_delay_us(0.1);
	sbi(BMA_PORT, CS);
	return werti;
}

void BMA_uninit(void)
{
	BMA_trans(0x0A01);
	BMA_DDR = (1 << SDI) | (1 << SCK) | (1 << CS) | (1 << FSK) | (1 << SDO);

	cbi(BMA_PORT, FSK);

	sbi(BMA_PORT, SDI);
	sbi(BMA_PORT, SCK);
	sbi(BMA_PORT, CS);
	sbi(BMA_PORT, SDO);
}

void BMA_init(void)
{
	BMA_DDR = (1 << SDI) | (1 << SCK) | (1 << CS) | (1 << FSK);

	sbi(BMA_PORT, CS);
	sbi(BMA_PORT, FSK);

	cbi(BMA_PORT, SDI);
	cbi(BMA_PORT, SCK);
	cbi(BMA_PORT, SDO);

	_delay_ms(10); // wait until POR done
	BMA_trans(0x0A00);

	_delay_ms(10); // wait until POR done

	BMA_trans(0x1580);
}


//int x(){
//	BMA_init();
//	while(1)
//	{
//		char buf[16];
//		int x = ( (BMA_trans(0x8200) & 0xff) | ( (BMA_trans(0x8300) & 0xff) << 8) ) >> 6;
//		if(x & 0x0200)
//		{
//			x |= 0xfe00;
//		}
//		x -= 36;
////		dtostrf((x*1.0) / 230, 10, 2,buf );
//
//		int y = ( (BMA_trans(0x8400) & 0xff) | ( (BMA_trans(0x8500) & 0xff) << 8) ) >> 6;
//		if(y & 0x0200)
//		{
//			y |= 0xfe00;
//		}
//		y += 32;
////		dtostrf((y*1.0) / 235, 10, 2,buf );
//
//		int z = ( (BMA_trans(0x8600) & 0xff) | ( (BMA_trans(0x8700) & 0xff) << 8) ) >> 6;
//		if(z & 0x0200)
//		{
//			z |= 0xfe00;
//		}
//		z -= 8;
////		itoa(z,buf,10);
////		uart_puts(",");
////		uart_puts(buf);
//
////		dtostrf((z*1.0) / 230, 10, 2,buf );
//
//		_delay_ms(10);
//	}
//}
