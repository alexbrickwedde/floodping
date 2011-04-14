//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                                  _            _     
//                                 | |          | |    
//      ___ _ __ ___  ___ _   _ ___| |_ ___  ___| |__  
//     / _ \ '_ ` _ \/ __| | | / __| __/ _ \/ __| '_ \. 
//    |  __/ | | | | \__ \ |_| \__ \ ||  __/ (__| | | |
//     \___|_| |_| |_|___/\__, |___/\__\___|\___|_| |_|
//                         __/ |                       
//                        |___/    Engineering
//
// Filename:    uart.h
// Description: UART for AVR Mega
//              
// Author:      Martin Steppuhn
// History:     17.09.2008 Initial version
//------------------------------------------------------------------------------

#ifndef UART_H
#define UART_H

/**** Includes ****************************************************************/

#include "std_c.h"
#include <avr/pgmspace.h>
#include <stdio.h>

/**** Preprocessing directives (#define) **************************************/

#define uart_puts_p(__s)   uart_puts_P(PSTR(__s))

/**** Type definitions (typedef) **********************************************/

/**** Global constants (extern) ***********************************************/

/**** Global variables (extern) ***********************************************/

/**** Global function prototypes **********************************************/

extern	void uart_init(void);
extern	bool uart_kbhit(void);
extern	void uart_putc(uint8 c);
extern	void uart_puts(uint8 *s);
extern  void uart_puts_P(const char *s);
extern	uint8 uart_getc(void);

#endif
