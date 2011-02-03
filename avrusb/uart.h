/* vim: set sw=8 ts=8 si et: */
/*************************************************************************
 Title:   C include file for uart
 Target:    atmega8
 Copyright: GPL
***************************************************************************/
#ifndef UART_H
#define UART_H
#include <avr/pgmspace.h>

extern void uart_init(void);
extern void uart_sendchar(char c);
extern void uart_sendstr(char *s);
extern void uart_sendstr_p(const prog_char *progmem_s);
extern unsigned char uart_getchar(unsigned char kickwd);
extern void uart_flushRXbuf(void);

/*
** macros for automatically storing string constant in program memory
*/
#ifndef P
#define P(s) ({static const char c[] __attribute__ ((progmem)) = s;c;})
#endif
#define uart_sendstr_P(__s)         uart_sendstr_p(P(__s))

#endif /* UART_H */
