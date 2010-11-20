/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2
 ***********************************************************************************************/

#ifndef __avr910protocol_h_included__
#define __avr910protocol_h_included__

#include <stdint.h>

#define PGM_STATUS_PROGRAMMING 1
#define PGM_STATUS_IDLE        2    

extern uint8_t    	AVR910_Status;

void (*PGM_statuschanged)(uint8_t); 
void AVR910_byterecived(uint8_t data);
void AVR910_init();

#endif /* __stk500protocol_h_included__ */
