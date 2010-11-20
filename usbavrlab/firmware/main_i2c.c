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
#include "buffer.h"

#define FUNC_READ_BUFFER			1
#define FUNC_SEND_I2C				2

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

uint8_t buffer[256];
uint8_t buffer_put=0;
uint8_t buffer_get=0;

#define I2C_PORT 		PORTB
#define I2C_PIN			PINB
#define I2C_DDR 	 	DDRB

#define I2C_SDA			PB3
#define I2C_SCL			PB2

uint8_t I2C_STATE,I2C_NSTATE;

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

  I2C_DDR  &= ~(1<<I2C_SCL);
  I2C_DDR  &= ~(1<<I2C_SDA);
  I2C_DDR  &= ~(1<<PB4);
  I2C_DDR  &= ~(1<<PB5);

  I2C_PORT |= (1<<I2C_SCL);
  I2C_PORT |= (1<<I2C_SDA);
  I2C_PORT |= (1<<PB4);
  I2C_PORT |= (1<<PB5);

  while(1)
    {
      I2C_NSTATE = I2C_PIN >> I2C_SCL;
      if (I2C_NSTATE != I2C_STATE) //Änderung auf den I2C Leitungen ?
        {
          buffer[buffer_put++]=I2C_NSTATE;
	      I2C_STATE = I2C_NSTATE;
	    }
      if (TIMER_timeout == 0)
        {
          if(usbNewDeviceAddr)
            leds[LED_BLUE].frequency = LED_ON;
          TIMER_start(50);
          usbPoll();
          LED_poll();
        }
	}
}

static uchar replyBuffer[10];

uint8_t usbFunctionSetup(uint8_t data[8])
{
  uchar len = 0;

  if(data[1] == FUNC_GET_TYPE)
    {
	  replyBuffer[0] = 3;
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
  else if(data[1] == FUNC_SEND_I2C)
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

#define I2C_SDA_PORT  I2C_PORT
#define I2C_SCL_PORT  I2C_PORT
#define I2C_SDA_DDR   I2C_DDR
#define I2C_SCL_DDR   I2C_DDR
#define I2C_SDA_INPUT I2C_PIN
#define I2C_SDA_PIN   PB3
#define I2C_SCL_PIN	  PB2

#define HDEL    _delay_us(2);

#define I2C_SDA_LO       I2C_SDA_PORT &= ~(1<<I2C_SDA_PIN);
#define I2C_SDA_HI       I2C_SDA_PORT |= (1<<I2C_SDA_PIN);

#define I2C_SCL_LO       I2C_SCL_PORT &= ~(1<<I2C_SCL_PIN);
#define I2C_SCL_HI       I2C_SCL_PORT |= (1<<I2C_SCL_PIN);

#define I2C_SCL_TOGGLE   HDEL; I2C_SCL_HI; HDEL; I2C_SCL_LO;
#define I2C_START        I2C_SDA_LO; HDEL; I2C_SCL_LO; 
#define I2C_STOP         HDEL; I2C_SCL_HI; HDEL; I2C_SDA_HI; HDEL;


uint8_t usbFunctionWrite( uint8_t *data, uint8_t len )
{
  if (usb_state != STATE_WRITE)
    return 0xff;
  int a,i = 0;
  unsigned char b; 
  I2C_SCL_DDR |= (1<<I2C_SCL_PIN); //Clock is output
  I2C_SDA_DDR |= (1<<I2C_SDA_PIN); //Data is output
  I2C_START; 
  buffer[buffer_put++]=1;
  buffer[buffer_put++]=0;
  for (a=0;a<len;a++)
    {
	  b = data[a];
      for (i=7;i>=0;i--)
        {
          if ( b & (0x80))
		    {
              I2C_SDA_HI;
              buffer[buffer_put++]=3;
			}
          else
		    {
              I2C_SDA_LO; 
              buffer[buffer_put++]=1;
            }
          b <<= 1;
          I2C_SCL_TOGGLE;     // clock HI, delay, then LO
          buffer[buffer_put++]=0;
        }
      I2C_SDA_HI;                 // leave SDA HI
      buffer[buffer_put++]=2;
      I2C_SDA_DDR &= ~(1<<I2C_SDA_PIN); // change direction to input on SDA line (may not be needed)
      HDEL;
      I2C_SCL_HI;                 // clock back up
      b = I2C_SDA_INPUT & (1<<I2C_SDA_PIN); // get the ACK bit
      buffer[buffer_put++]=(b >> I2C_SCL_PIN) | 1;
      HDEL;
      I2C_SCL_LO;                 // not really ??
      buffer[buffer_put++]=(b >> I2C_SCL_PIN);
      I2C_SDA_DDR |= (1<<I2C_SDA_PIN); // change direction back to output
      HDEL;
      if (b != 0) //Nack
	    {
		  break;
        } 
    }
  I2C_STOP;
  buffer[buffer_put++]=1;
  buffer[buffer_put++]=3;
  I2C_SDA_DDR &= ~(1<<I2C_SDA_PIN); //Data is input
  I2C_SCL_DDR &= ~(1<<I2C_SCL_PIN); //Clock is input
  return len;
}

