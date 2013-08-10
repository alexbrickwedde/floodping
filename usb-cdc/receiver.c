/* Name: receiver.c
 * Project: Remote Sensor; receiver based on AVR USB driver
 * Author: Christian Starkjohann
 * Creation Date: 2005-03-20
 * Tabsize: 4
 * Copyright: (c) 2005 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt) or proprietary (CommercialLicense.txt)
 * This Revision: $Id: receiver.c 311 2007-03-29 17:14:50Z cs $
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "usbdrv.h"
#include "oddebug.h"

static uchar rxBuffer[12];
static uchar rxIndex;

#define FIFO_SIZE   4   /* must be power of 2 */
#define FIFO_MASK   (FIFO_SIZE - 1)

static uchar rxFifo[FIFO_SIZE][8];
static uchar fifoWp, fifoRp, fifoIsFull;

/* ------------------------------------------------------------------------- */

static void fifoWrite(uchar *buffer) {
	uchar i, *src, *dest;

	if (!fifoIsFull) {
		src = buffer;
		dest = (uchar *) rxFifo + fifoWp;
		for (i = 8; i; i--)
			*dest++ = *src++;
		fifoWp = (fifoWp + 8) & (FIFO_MASK << 3);
		fifoIsFull = fifoWp == fifoRp;
	}
}

static uchar fifoSize(void) {
	uchar size;

	if (fifoIsFull)
		return 4;
	/* enforce byte wide arithmetic: */
	size = (fifoWp - fifoRp);
	size >>= 3;
	size &= FIFO_MASK;
	return size;
}

static void fifoRead(uchar *buffer) {
	uchar i, *src, *dest;

	if (fifoSize()) {
		src = (uchar *) rxFifo + fifoRp;
		dest = buffer;
		for (i = 8; i; i--)
			*dest++ = *src++;
		fifoRp = (fifoRp + 8) & (FIFO_MASK << 3);
		fifoIsFull = 0;
	}
}

/* ------------------------------------------------------------------------- */
/* The receiver module returns random data (noise) if no carrier is received.
 * In order to ignore that babble, we do the following checks:
 *  - abort reception on byte framing errors
 *  - bytes must be received within tight time frame (40ms)
 *  - 16 bits start of frame signature must match
 *  - 4 bits value count must match
 *  - 16 bits CRC must match.
 * These checks provide at least 36 bits of security against false packets.
 */

static void usartTimeout(void) {
	rxIndex = 0;
}

static void usartPoll(void) {
	uchar c, e;

	e = UCSRA; /* for error checking */
	c = UDR;
	rxBuffer[rxIndex++] = c;
	if (rxIndex >= 12) { /* complete frame received */
		fifoWrite(rxBuffer);
		usbSetInterrupt(0, 0); /* NULL message on interrupt socket */
		rxIndex = 0;
	}
	UDR = c;
}

/* ------------------------------------------------------------------------- */

static uchar replyBuffer[8];
/* we don't need to store much status because we don't implement multiple
 * chunks in read/write transfers
 */

uchar usbFunctionSetup(uchar data[8]) {
	uchar len = 0;

	if (data[1] == 0) { /* ECHO */
		len = 2;
		replyBuffer[0] = data[2];
		replyBuffer[1] = data[3];
	} else if (data[1] == 1) { /* poll data available */
		len = 1;
		replyBuffer[0] = fifoSize();
	} else if (data[1] == 2) { /* read data */
		if (fifoSize()) {
			len = 8;
			fifoRead(replyBuffer);
		}
	}
	usbMsgPtr = replyBuffer;
	return len;
}

/* These are for testing only -- we don't enable USB_CFG_IMPLEMENT_FN_* */
#if USB_CFG_IMPLEMENT_FN_WRITE
uchar usbFunctionWrite(uchar *data, uchar len)
{
	return 0;
}
#endif
#if USB_CFG_IMPLEMENT_FN_READ
uchar usbFunctionRead(uchar *data, uchar len)
{
	return 0;
}
#endif

/* ------------------------------------------------------------------------- */

int main(void) {
	wdt_enable(WDTO_1S);
	odDebugInit();
	DDRD = ~((1 << 2) | 1); /* all outputs except PD2 = INT0 and PD0 = RxD */
	PORTD = 0;
	PORTB = 0; /* no pullups on USB pins */
	DDRB = ~0; /* output SE0 for USB reset */
	_delay_ms(100);
	DDRB = ~USBMASK; /* all outputs except USB data */
	usbInit();
	sei();

	UCSRB |= (1 << RXEN);
	UCSRB |= (1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); // Asynchron 8N1

#define BAUD 9600UL
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
	UBRRH = UBRR_VAL >> 8;
	UBRRL = UBRR_VAL & 0xFF;

	TCCR1B = 3; /* prescaler = 1/64 -> 1 count = 5.33333 us */
	for (long xx = 0;; xx++) { /* main event loop */
		wdt_reset();
		usbPoll();
		if (UCSRA & (1 << RXC)) { /* USART RX complete */
			usartPoll(); /* must be polled at least every 6 ms */
		}
		if (TIFR & (1 << OCF1A)) {
			TIFR = 1 << OCF1A;
//			usartTimeout();
		}
	}
	return 0;
}

/* ------------------------------------------------------------------------- */
