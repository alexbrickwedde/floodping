/************************************************************************************************
 * Project: USB AVR-Lab
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-09-24
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2
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

#define FUNC_READ_BUFFER			2
#define FUNC_WRITE_BUFFER			1

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

void SetLed(unsigned char led, unsigned char mode,unsigned char frequency)
{
  leds[led].status = mode;
  leds[led].frequency = frequency;
}

void avrlab_init(void)
{
  uint8_t i,j;
  /* activate pull-ups except on USB lines */
  USB_CFG_IOPORT   = (uchar)~((1<<USB_CFG_DMINUS_BIT)|(1<<USB_CFG_DPLUS_BIT));
  /* all pins input except USB (-> USB reset) */
#ifdef USB_CFG_PULLUP_IOPORT    /* use usbDeviceConnect()/usbDeviceDisconnect() if available */
  USBDDR    = 0;    /* we do RESET by deactivating pullup */
  usbDeviceDisconnect();
#else
  USBDDR    = (1<<USB_CFG_DMINUS_BIT)|(1<<USB_CFG_DPLUS_BIT);
#endif
  j = 0;
  while(--j){          /* USB Reset by device only required on Watchdog Reset */
      i = 0;
      while(--i);      /* delay >10ms for USB reset */
  }
#ifdef USB_CFG_PULLUP_IOPORT
  usbDeviceConnect();
#else
  USBDDR    = 0;      /*  remove USB reset condition */
#endif
  usbInit();
  sei();
}

void avrlab_poll(void)
{
  usbPoll();
  LED_poll();
}

static uint8_t replyBuffer[10];  

uint8_t usbFunctionSetup(uint8_t data[8])
{
  uchar len = 0;

  if(data[1] == FUNC_GET_TYPE)
    {
	  replyBuffer[0] = 6;
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

