/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 *
 * Changes:
 *  2008-04-02 
 *    Initial Version
 ************************************************************************************************/

#include "config.h"

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "usbdrv.h"
#include "usbconfig.h"
#include "usb_uart.h"
#include "led.h"
#include "timer.h"
#include "main.h"

#ifndef USBASP_COMPATIBLE
  #ifndef CCCB_COMPATIBLE
led_t leds[] =  {{4,LED_OFF,LED_OFF},
                 {3,LED_OFF,LED_OFF},
                 {5,LED_OFF,LED_OFF}}; 
  #else //CCCB_COMPATIBLE
led_t leds[] =  {{2,LED_OFF,LED_OFF},
                 {3,LED_OFF,LED_OFF}, //not there
                 {5,LED_OFF,LED_OFF}};//not there 
  #endif
#else 
led_t leds[] =  {{0,LED_OFF,LED_OFF},
                 {1,LED_OFF,LED_OFF},
                 {3,LED_OFF,LED_OFF}}; 
#endif
const uint8_t led_count = sizeof(leds)/sizeof(led_t);

uint8_t inboot = 0;

void Oncharrecived(uint8_t c)
{
  leds[LED_BLUE].counter = 10; 
  leds[LED_BLUE].frequency = LED_FLASH_NEG;
       if      ((inboot == 0) && (c == 'b')) inboot++;
       else if ((inboot == 1) && (c == 'o')) inboot++;
       else if ((inboot == 2) && (c == 'o')) inboot++;
       else if ((inboot == 3) && (c == 't')) inboot++;
       else if ((inboot == 4) && (c == 0xD)) inboot++;
       else if ((inboot == 5) && (c == 0xD))
         {
           cli();
		   wdt_enable(WDTO_15MS);
		   while(1);
         }
       else
         inboot = 0;
   JTAGICE_byterecived(c);
}

void uartDisconnect(void)
{
  CDC_charrecived = Oncharrecived;
  leds[LED_BLUE].frequency = LED_OFF;
}

int main(void)
{
  extern uchar usbNewDeviceAddr;
  uint8_t i;

  PORTD |= (1<<PD0);
  leds[LED_RED].frequency = LED_ON;
  LED_init();
  for (i=0;i<3;i++)
    TIMER_delay(250);
  CDC_charrecived = Oncharrecived;
  CDC_init();
  leds[LED_RED].frequency = LED_OFF;
  while(1)
    {
      if(usbNewDeviceAddr)
        leds[LED_BLUE].frequency = LED_ON;
	  MAIN_tasks();
	}
}

void MAIN_tasks(void)
{
  MAIN_critical_tasks();
  LED_poll();
}

void MAIN_critical_tasks(void)
{
  CDC_poll(); 
}



