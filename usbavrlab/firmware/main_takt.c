/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-09-24
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 *
 * Changes:
 ***********************************************************************************************/

#include "config.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include "usbdrv.h"
#include "usbconfig.h"
#include "led.h"
#include "timer.h"
#include "main.h"
#include "buffer.h"

#define FUNC_START_BOOTLOADER		30
#define FUNC_GET_TYPE				0xFE

#ifndef USBASP_COMPATIBLE
led_t leds[] =  {{4,LED_OFF,LED_OFF},
                 {3,LED_OFF,LED_OFF},
                 {5,LED_OFF,LED_OFF}}; 
#else
led_t leds[] =  {{0,LED_OFF,LED_OFF},
                 {1,LED_OFF,LED_OFF},
                 {3,LED_OFF,LED_OFF}}; 
#endif
const uint8_t led_count = sizeof(leds)/sizeof(led_t);


int main(void)
{
  extern uchar usbNewDeviceAddr;
  uint8_t i;
//Reconnect USB
  usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
  i = 0;
  while(--i)
     _delay_ms(2);
  usbDeviceConnect();
  usbInit();
  sei();

  leds[LED_RED].frequency = LED_ON;
  LED_init();
  for (i=0;i<3;i++)
    TIMER_delay(250);
  leds[LED_RED].frequency = LED_OFF;
  leds[LED_GREEN].frequency = 1;


  while(1)
    {
      if (TIMER_timeout == 0)
        {
          if(usbNewDeviceAddr)
            leds[LED_BLUE].frequency = LED_ON;
          PORTD ^= (1<<PD7);
          TIMER_start(1);
          usbPoll();
          LED_poll();
        }
	}
}

static uchar replyBuffer[8];

uint8_t usbFunctionSetup(uint8_t data[8])
{
  uchar len = 0;

  if(data[1] == FUNC_GET_TYPE)
    {
	  replyBuffer[0] = 8;
	  len = 1;
	}
  else if(data[1] == FUNC_START_BOOTLOADER)
    {
      cli();
	  wdt_enable(WDTO_15MS);
      while(1);
	  len = 0;
	}


  usbMsgPtr = replyBuffer;
  return len;
}

uint8_t usbFunctionRead( uint8_t *data, uint8_t len )
{
  return 0xff;
}

uint8_t usbFunctionWrite( uint8_t *data, uint8_t len )
{
  return 0xff;
}

