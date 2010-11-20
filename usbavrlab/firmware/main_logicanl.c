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
#include "usb_uart.h"
#include "isp.h"
#include "led.h"
#include "timer.h"
#include "main.h"

#define FUNC_READ_BUFFER			1
#define FUNC_SET_PARAMS				2

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

uint8_t buffer[860];
uint16_t buffer_put=0;
uint16_t buffer_get=0;

#define CHANNELPORT1 PORTB
#define CHANNELPIN1  PINB
#define CHANNELDDR1  DDRB

#define CHANNEL_1 PB3
#define CHANNEL_2 PB2
#define CHANNEL_3 PB5
#define CHANNEL_4 PB4

#define CHANNELPORT2 PORTD
#define CHANNELPIN2  PIND
#define CHANNELDDR2  DDRD

#define CHANNEL_5 PD0
#define CHANNEL_6 PD1

uint8_t TriggerChannel = 1;
uint8_t channel1trigger = 0x0;
uint8_t channel2trigger = 0x0;

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

  CHANNELDDR1 &= ~((1 << CHANNEL_1) | (1 << CHANNEL_2) | (1 << CHANNEL_3) | (1 << CHANNEL_4));
  CHANNELPORT1 |= ((1 << CHANNEL_1) | (1 << CHANNEL_2) | (1 << CHANNEL_3) | (1 << CHANNEL_4));
  CHANNELDDR2 &= ~((1 << CHANNEL_5) | (1 << CHANNEL_6));
  CHANNELPORT2 |= ((1 << CHANNEL_5) | (1 << CHANNEL_6));

  uint8_t tmp1,tmp1_old; 
  uint8_t tmp2,tmp2_old;
  while(1)
    {
      if (TIMER_timeout == 0)
        {
          if(usbNewDeviceAddr)
            leds[LED_BLUE].frequency = LED_ON;
          TIMER_start(49);
          usbPoll();
          LED_poll();
        }
      tmp1 = CHANNELPIN1; 
      tmp2 = CHANNELPIN2;
	  if ((tmp1 != tmp1_old) || (tmp2 != tmp2_old))
//      if (((channel1trigger & tmp1) == channel1trigger) || ((channel2trigger & tmp2) == channel2trigger))
        {
		  buffer[buffer_put++] = (tmp1 & ((1 << CHANNEL_1) | (1 << CHANNEL_2) | (1 << CHANNEL_3) | (1 << CHANNEL_4)))
		                        +(tmp2 & ((1 << CHANNEL_5) | (1 << CHANNEL_6))); 
	    }
      tmp1_old = tmp1; 
      tmp2_old = tmp2; 
	}
}

static uchar replyBuffer[8];

uint8_t usbFunctionSetup(uint8_t data[8])
{
  uchar len = 0;

  if(data[1] == FUNC_GET_TYPE)
    {
	  replyBuffer[0] = 5;
	  len = 1;
	}
  else if(data[1] == FUNC_START_BOOTLOADER)
    {
      cli();
	  wdt_enable(WDTO_15MS);
      while(1);
	  len = 0;
	}
  else if(data[1] == FUNC_READ_BUFFER)
    {
	  usb_state = STATE_READ;
      len = 0xff;
	}
  else if(data[1] == FUNC_SET_PARAMS)
    {
	  usb_state = STATE_WRITE;
      len = 0xff;
	}
  usbMsgPtr = replyBuffer;
  return len;
}

uint8_t usbFunctionRead( uint8_t *data, uint8_t len )
{
  if (usb_state != STATE_READ)
    return 0xff;
  
  uint8_t asize = 0;
  while (asize<len)
    {
	  if (buffer_put == buffer_get) break;
      data[asize++] = buffer[buffer_get++];
	}
  return asize;
}

uint8_t usbFunctionWrite( uint8_t *data, uint8_t len )
{
  if (usb_state != STATE_WRITE)
    return 0xff;
  if (len > 0) channel1trigger = *data++;
  if (len > 1) channel2trigger = *data++;
  return len;
}
