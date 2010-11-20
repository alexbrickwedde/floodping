/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2
 ***********************************************************************************************/

#ifndef __main_h_included__
#define __main_h_included__

#define LED_RED 	0
#define LED_GREEN 	1
#define LED_BLUE 	2

#define LED_PORT 	PORTC
#define LED_DDR 	DDRC

#define   eeispSpeed 		0x000
#define   eeSoftwareMajor	0x001  // Eine Bytevariable  
#define   eeSoftwareMinor	0x002  // Eine Wordvariable (Lowbyte)
#define   eeProtocolType 	0x003  // Eine Wordvariable (Highbyte)

void MAIN_tasks(void);
void MAIN_critical_tasks(void);

#endif
