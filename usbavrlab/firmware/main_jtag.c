/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2008-12-10
 * Copyright: (c) 2008 by Christian Ulrich
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 *
 * Changes:
 ***********************************************************************************************/

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
#include "jtag.h"

#define FUNC_READ_CHAIN 			1
#define FUNC_WRITE_CHAIN 			2
#define FUNC_TAP_STATE  			3
#define FUNC_GET_TAP_STATE 			4
#define FUNC_OPEN 					5
#define FUNC_CLOSE 					6
#define FUNC_SHIFT1BIT 				7
#define FUNC_CHAINSIZE 				8
#define FUNC_EXECCHAIN				9

#define FUNC_START_BOOTLOADER		30
#define FUNC_GET_TYPE				0xFE

#define STATE_IDLE					0
#define STATE_READ					1
#define STATE_WRITE					2

uint8_t usb_state = STATE_IDLE;

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


#define MAX_CHAINSIZE 	900
unsigned char JTAG_CHAIN[MAX_CHAINSIZE];
unsigned int chainpos = 0;

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

  while(1)
    {
      if(usbNewDeviceAddr)
        leds[LED_BLUE].frequency = LED_ON;
      usbPoll();
      LED_poll();
	}
}

static uchar replyBuffer[8];

uint8_t usbFunctionSetup(uint8_t data[8])
{
  uchar len = 0;

  usb_state = STATE_IDLE;
  if(data[1] == FUNC_GET_TYPE)
    {
	  replyBuffer[0] = 10;
	  len = 1;
	}
  else if(data[1] == FUNC_START_BOOTLOADER)
    {
      cli();
	  wdt_enable(WDTO_15MS);
      while(1);
	  len = 0;
	}
  else if(data[1] == FUNC_READ_CHAIN)
    {
	  chainpos = 0;
	  usb_state = STATE_READ;
      len = 0xff;
	}
  else if(data[1] == FUNC_WRITE_CHAIN)
    {
	  chainpos = 0;
	  usb_state = STATE_WRITE;
      len = 0xff;
	}
  else if(data[1] == FUNC_TAP_STATE)
    {
	  JTAG_goto_tap_state(data[2]);
	  len = 0;
	}
  else if(data[1] == FUNC_GET_TAP_STATE)
    {
	  replyBuffer[0] = JTAG_TAP_STATE;
	  len = 1;
	}
  else if(data[1] == FUNC_OPEN)
    {
	  JTAG_attatch();
	  len = 0;
	}
  else if(data[1] == FUNC_CLOSE)
    {
	  JTAG_detatch();
	  len = 0;
	}
  else if(data[1] == FUNC_SHIFT1BIT)
    {
	  replyBuffer[0] = JTAG_shift_bit(data[2]);
	  len = 1;
	}
  else if(data[1] == FUNC_CHAINSIZE)
    {
	  replyBuffer[0] = chainpos;
	  replyBuffer[1] = chainpos>>8;
	  len = 2;
	}
  else if (data[1] == FUNC_EXECCHAIN)
    {
	  JTAG_shift_bytes(JTAG_CHAIN,chainpos);
	}
  usbMsgPtr = replyBuffer;
  return len;
}

uint8_t usbFunctionRead( uint8_t *data, uint8_t len )
{
  if (usb_state != STATE_READ)
    return 0xff;
  
  uint8_t asize = 0;
  return asize;
}

uint8_t usbFunctionWrite( uint8_t *data, uint8_t len )
{
  if (usb_state != STATE_WRITE)
    return 0xff;
  memcpy(&JTAG_CHAIN[chainpos],data,len);
  chainpos += len;
  return len;
}
