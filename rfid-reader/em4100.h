/*
Title:	C header file for U2270 RFID reader IC
Original Author:	Stefan Seegel / dahamm@gmx.net
Date:	30.08.2006
Version:1.0
Free for noncommercial use
*/

#define F_RFID 125000UL	//RFID carrier frequency
#ifndef F_CPU
  #define F_CPU 8000000UL
#endif

#define TIMER0_PRESCALER 64 //Needed for manchester decoding

extern uint8_t u2270_read_tag(uint8_t *d);

extern int uart_putc(char c);
extern void Usart_SendHexChar(uint8_t val);
