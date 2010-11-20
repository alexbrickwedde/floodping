/************************************************************************************************
 * Project: generic
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2
 ***********************************************************************************************/

#ifndef __timer_h_included__
#define __timer_h_included__

#define TIMER_overflowed() TIMER_timeout==0

extern volatile uint8_t TIMER_timeout;

void TIMER_start(uint8_t timeout);
void TIMER_delay(uint8_t timeout);

#endif
