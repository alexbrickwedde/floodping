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
 *	 2008/11/21 1.2 updated usb firmware
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

#define CHANNEL_5 PD1
#define CHANNEL_6 PD0

uint8_t DATA;

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
  leds[LED_GREEN].frequency = LED_ON;

  //Input with pullups
  CHANNELDDR1 &= ~((1 << CHANNEL_1) | (1 << CHANNEL_2) | (1 << CHANNEL_3) | (1 << CHANNEL_4));
  CHANNELPORT1 |= ((1 << CHANNEL_1) | (1 << CHANNEL_2) | (1 << CHANNEL_3) | (1 << CHANNEL_4));
  CHANNELDDR2 &= ~((1 << CHANNEL_5) | (1 << CHANNEL_6));
  CHANNELPORT2 |= ((1 << CHANNEL_5) | (1 << CHANNEL_6));
  
  //Preset data with actual pin states
  DATA = 0;
  if (CHANNELPIN1 & (1<<CHANNEL_1))
    DATA = 1;
  if (CHANNELPIN1 & (1<<CHANNEL_2))
    DATA = 2;
  if (CHANNELPIN1 & (1<<CHANNEL_3))
    DATA = 4;
  if (CHANNELPIN1 & (1<<CHANNEL_4))
    DATA = 8;
  if (CHANNELPIN2 & (1<<CHANNEL_5))
    DATA = 16;
  if (CHANNELPIN2 & (1<<CHANNEL_6))
    DATA = 32;
  
  //Set actual Pinstates as Output
  CHANNELPORT1 = CHANNELPIN1;
  CHANNELPORT2 = CHANNELPIN2;
  CHANNELDDR1 |= ((1 << CHANNEL_1) | (1 << CHANNEL_2) | (1 << CHANNEL_3) | (1 << CHANNEL_4));
  CHANNELDDR2 |= ((1 << CHANNEL_5) | (1 << CHANNEL_6));
  

  while(1)
    {
      if (TIMER_timeout == 0)
        {
          if(usbNewDeviceAddr)
            leds[LED_BLUE].frequency = LED_ON;
          TIMER_start(10);
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
	  replyBuffer[0] = 4;
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
	  replyBuffer[0] = DATA;
      len = 1;
	}
  else if(data[1] == FUNC_WRITE_BUFFER)
    {
	  DATA = data[2];
	  if (DATA & (1<<0))  
	    CHANNELPORT1 |= (1<<CHANNEL_1);
      else  
	    CHANNELPORT1 &= ~(1<<CHANNEL_1);

	  if (DATA & (1<<1))  
	    CHANNELPORT1 |= (1<<CHANNEL_2);
      else  
	    CHANNELPORT1 &= ~(1<<CHANNEL_2);
	  if (DATA & (1<<2))  
	    CHANNELPORT1 |= (1<<CHANNEL_3);
      else  
	    CHANNELPORT1 &= ~(1<<CHANNEL_3);
	  if (DATA & (1<<3))  
	    CHANNELPORT1 |= (1<<CHANNEL_4);
      else  
	    CHANNELPORT1 &= ~(1<<CHANNEL_4);
	  if (DATA & (1<<4))  
	    CHANNELPORT2 |= (1<<CHANNEL_5);
      else  
	    CHANNELPORT2 &= ~(1<<CHANNEL_5);
	  if (DATA & (1<<5))  
	    CHANNELPORT2 |= (1<<CHANNEL_6);
      else  
	    CHANNELPORT2 &= ~(1<<CHANNEL_6);
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

