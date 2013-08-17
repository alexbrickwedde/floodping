#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "rf12.h"
#include "bma.h"
#include "main.h"

#include <util/delay.h>

#define AIRID "0101"
#define xDEBUG 1

unsigned int volatile WDTcounter = 0;

ISR(WDT_OVERFLOW_vect) {
	cli();
	WDTCSR |= _BV(WDIE);// | _BV(WDP2) | _BV(WDP1) | _BV(WDP0);
	WDTcounter++;
	sei();
}

signed int x;
signed int y;
signed int z;

void measure() {
	signed long x1 = 0;
	signed long y1 = 0;
	signed long z1 = 0;

	for(int u = 0; u < 16; u++)
	{
		signed int mx;
		signed int my;
		signed int mz;

		int l = (BMA_trans(0x8200) & 0xff) >> 6;
		int m = (BMA_trans(0x8300) & 0xff) << 2;
		mx = ( m | l);

		l = (BMA_trans(0x8400) & 0xff) >> 6;
		m = (BMA_trans(0x8500) & 0xff) << 2;
		my = ( m | l);

		l = (BMA_trans(0x8600) & 0xff) >> 6;
		m = (BMA_trans(0x8700) & 0xff) << 2;
		mz = ( m | l);

		if (mx & 0x0200) {
			mx |= 0xfe00;
		}
		if (my & 0x0200) {
			my |= 0xfe00;
		}
		if (mz & 0x0200) {
			mz |= 0xfe00;
		}
		x1 += mx;
		y1 += my;
		z1 += mz;
	}

	x = x1 >> 4;
	y = y1 >> 4;
	z = z1 >> 4;

	x -= 30;
	y += 0;
	z += 6;

#ifdef DEBUG
	TransmitByte('x');
	TransmitIntAsAscii(x);
	TransmitByte('\r');
	TransmitByte('\n');
	TransmitByte('y');
	TransmitIntAsAscii(y);
	TransmitByte('\r');
	TransmitByte('\n');
	TransmitByte('z');
	TransmitIntAsAscii(z);
	TransmitByte('\r');
	TransmitByte('\n');
#endif

}

void send() {
  char buf[16];// = "g123456789012345678901234567890\0\0\0";
  buf[0] = 'g';
  memcpy(buf + 1, &x, 2);
  memcpy(buf + 3, &y, 2);
  memcpy(buf + 5, &z, 2);
  buf[7] = 0;
  memcpy(buf + 8, &x, 2);
  memcpy(buf + 10, &y, 2);
  memcpy(buf + 12, &z, 2);
  buf[14] = 0;

  rf12_init();
  rf12_setall(RF12FREQ868(868.3), 4, 1, 4, 666, 0, 6);

  rf12_txdata(buf, 15);

  rf12_trans(0x8201);
  rf12_trans(0x0);
}

//#define MAXCOUNT 30
//
//int
//main111111111111(void)
//{
//  rf12_preinit(AIRID);
//
//  send();
//
//  cli();
//  wdt_reset();
//  wdt_enable (WDTO_1S);
//  WDTCSR |= _BV(WDIE) | _BV(WDP2) | _BV(WDP1) | _BV(WDP0);
//  sei();
//
//  for (;;)
//  {
//    if (WDTcounter >= MAXCOUNT)
//    {
//      send();
//      WDTcounter = 0;
//    }
//
//    wdt_reset();
//
//    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//    sleep_enable();
//
//    sleep_cpu ();
//    sleep_disable ();
//    wdt_reset();
//  }
//}
//

#ifdef DEBUG
void InitUART(unsigned char baudrate) {
	_delay_ms(10);
	UBRRL = baudrate;
	UCSRB = (1 << TXEN);
	UCSRC = (1 << UCSZ1) | (1 << UCSZ0);
}

void TransmitByte(unsigned char data) {
	while (!(UCSRA & (1 << UDRE)))
		;
	UDR = data;
	_delay_ms(10);
}

void TransmitIntAsAscii(unsigned int data)
{
	int e1 = data % 10;
	data /= 10;
	int e10 = data % 10;
	data /= 10;
	int e100 = data % 10;
	data /= 10;
	int e1000 = data % 10;
	data /= 10;
	int e10000 = data % 10;

	TransmitByte(e10000 + '0');
	TransmitByte(e1000 + '0');
	TransmitByte(e100 + '0');
	TransmitByte(e10 + '0');
	TransmitByte(e1 + '0');
	TransmitByte(' ');
}
#endif

#define c_State_Boot 0
#define c_State_Idle 1
#define c_State_DoSend_Init 2
#define c_State_DoSend_Init2 3
#define c_State_DoSend_Measure 4
#define c_State_DoSend_Send 5

int uiState;

int main(void) {

#ifdef DEBUG
	InitUART(47); //95 = 9600 bei 14,7   47 = 9600 bei 7,3       12 = 38400 bei 8mhz

	TransmitByte('I');
	TransmitByte('\r');
	TransmitByte('\n');
#endif

	BMA_uninit(0);
	uiState = c_State_Boot;
	rf12_preinit(AIRID);

	cli();
	wdt_reset();
	WDTCSR |= _BV(WDIE);// | _BV(WDP2) | _BV(WDP1) | _BV(WDP0);
	sei();

	for (;;) {
		if (uiState == c_State_Boot) {
			if (WDTcounter >= 100) {
				uiState = c_State_DoSend_Init;
			}
		}

		if (uiState == c_State_DoSend_Init) {
			BMA_init();
			uiState = c_State_DoSend_Init2;
		} else if (uiState == c_State_DoSend_Init2) {
			BMA_init2();
			uiState = c_State_DoSend_Measure;
		} else if (uiState == c_State_DoSend_Measure) {
			measure();
			BMA_uninit(1);
			uiState = c_State_DoSend_Send;

		}

		if (uiState == c_State_DoSend_Send) {
			send();
			uiState = c_State_Idle;
			WDTcounter = 0;
		}

		if (uiState == c_State_Idle) {
#ifdef DEBUG
			if (WDTcounter >= 300) {
#else
			if (WDTcounter >= 5000) {
#endif
				uiState = c_State_DoSend_Init;
				WDTcounter = 0;
			}
		}

		wdt_reset();
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		sleep_enable();
		sleep_cpu ();
		sleep_disable ();
		wdt_reset();
	}
}
