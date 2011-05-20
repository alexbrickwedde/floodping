#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "can.h"

#ifndef cbi
#define cbi(sfr, bit)     (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit)     (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void uartPutc(char c) {
	while (!(UCSRA & _BV(UDRE)))
		;
	UDR = c;
}

void uartPuts(char *s) {
	int x = 0;
	while (s[x]) {
		uartPutc(s[x]);
		x++;
	}
}

prog_uint8_t can_filter[] = {
// Group 0
		MCP2515_FILTER(0), // Filter 0
	MCP2515_FILTER(0)								, // Filter 1

// Group 1
	MCP2515_FILTER_EXTENDED(0)								, // Filter 2
	MCP2515_FILTER_EXTENDED(0)								, // Filter 3
	MCP2515_FILTER_EXTENDED(0)								, // Filter 4
	MCP2515_FILTER_EXTENDED(0)								, // Filter 5

		MCP2515_FILTER(0), // Mask 0 (for group 0)
	MCP2515_FILTER_EXTENDED(0)								, // Mask 1 (for group 1)
}		;

#define UART_MAXSTRLEN 100

volatile uint8_t uart_str_complete = 0;
volatile uint8_t uart_str_count = 0;
volatile char uart_string[UART_MAXSTRLEN + 1] = "";

ISR(SIG_UART_RECV)
{
	unsigned char nextChar;

	nextChar = UDR;
	if (uart_str_complete == 0) {
		if (nextChar != '\n' && nextChar != '\r' && uart_str_count
				< UART_MAXSTRLEN - 1) {
			uart_string[uart_str_count] = nextChar;
			uart_str_count++;
		} else {
			uart_string[uart_str_count] = '\0';
			uart_str_count = 0;
			uart_str_complete = 1;
		}
	}
}

int hex2dez_c(char h) {
	int res = -1;
	if (h >= '0' && h <= '9') {
		res = (h - '0');
	} else if (h >= 'A' && h <= 'F') {
		res = (h - 'A' + 10);
	} else if (h >= 'a' && h <= 'f') {
		res = (h - 'a' + 10);
	}
	return res;
}

int hex2dez(char *h) {
	int res1 = hex2dez_c(h[0]);
	int res2 = hex2dez_c(h[1]);
	if (res1 < 0 || res2 < 0)
		return -1;
	return (res1 << 4) + res2;
}

int main() {
	wdt_reset();
	cli();
	UCSRB |= _BV(TXEN) | _BV(RXEN) | _BV(RXCIE);
	UCSRC |= _BV(URSEL) | _BV(UCSZ1) | _BV(UCSZ0);

	uint16_t ubrr = (uint16_t) ((uint32_t) F_CPU / (16 * 115200) - 1);
	UBRRH = (uint8_t) (ubrr >> 8);
	UBRRL = (uint8_t) (ubrr);

	uartPuts(
			"\r\n\r\n\r\n\r\n\r\n\r\n\r\nWordClock V0.1 initializing...\r\n\r\n");

	uartPuts("\r\nReset-Cause:");
	switch (MCUCSR & 0x1f) {
	case 1:
		uartPuts("Power-On Reset\r\n");
		break;
	case 2:
		uartPuts("External Reset\r\n");
		break;
	case 4:
		uartPuts("Brown-Out Reset\r\n");
		break;
	case 8:
		uartPuts("Watchdog Reset\r\n");
		break;
	case 16:
		uartPuts("JTAG Reset\r\n");
		break;
	default:
		uartPuts("unknown\r\n");
		break;
	}
	MCUCSR = 0;

	while (1) {

		uartPutc('.');
		_delay_ms(500);
		uartPutc('.');
		_delay_ms(500);
		uartPutc('.');
		_delay_ms(500);
		uartPuts("\r\n");

		if (can_init(BITRATE_500_KBPS)) {
			uartPuts("CAN initialized\r\n");

			can_static_filter(can_filter);

			int uiC = 0;
			while (1) {
				can_wakeup();
				uartPutc('.');
				uiC++;
				if (uiC > 60) {
					uiC = 0;
					uartPuts("\r\n");
				}
				_delay_ms(500);
				can_t msg;
				if (can_check_message()) {
					switch (can_get_message(&msg)) {
					case 0:
						uartPuts("No MSG\r\n");
						break;
					default: {
						char s[100];
						sprintf(s, "MSG, id:%d length:%d\r\n", msg.id,
								msg.length);
						uartPuts(s);
					}
						break;
					}
				} else {
					msg.flags.rtr = 0;
					msg.flags.extended = 1;
					msg.id = uiC;
					msg.length = 1;
					msg.data[0] = 0x31;
					can_send_message(&msg);
				}
			}
		} else {
			uartPuts("CAN NOT initialized\r\n");
		}

	}
}
