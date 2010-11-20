/************************************************************************************************
 * Project: generic
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 ***********************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "led.h"

volatile uint8_t TIMER_timeout;

ISR(SIG_OVERFLOW0)
{
  cli();
  TCNT0 = 50;
  TIMER_timeout--;
  if (TIMER_timeout == 0)
#if defined(__AVR_ATmega8__)||defined(__AVR_ATmega16__)||defined(__AVR_ATmega32__)
    TCCR0 = 0; //timer aus
#elif defined(__AVR_ATmega168__) || defined(__AVR_ATmega88__)
    TCCR0B = 0; //timer aus
#endif
  sei();
}

void TIMER_delay(uint8_t timeout)
{
  TIMER_start(timeout);
  while (TIMER_timeout > 0);
}

void TIMER_start(uint8_t timeout)
{
// 12MHz/64 = 187.5kHz --> 5.333us
// overflow every 256 counts = 732.422Hz --> 1.365ms
  sei();
  TIMER_timeout = timeout;
  TCNT0 = 50;
#if defined(__AVR_ATmega8__)||defined(__AVR_ATmega16__)||defined(__AVR_ATmega32__)
  TCCR0 |= (1<<CS00)|(1<<CS01);
  TIMSK |= (1 << TOIE0);
#elif defined(__AVR_ATmega168__) || defined(__AVR_ATmega88__)
  TCCR0B |= (1<<CS00)|(1<<CS01);
  TIMSK0 |= (1 << TOIE0);
#endif
}
