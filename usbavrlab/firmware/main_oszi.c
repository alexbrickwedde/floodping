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
#define FUNC_SET_PARAMS				2
#define FUNC_STOP   				3
#define FUNC_START					4
#define FUNC_WRITE_EEP				5
#define FUNC_READ_EEP				6

#define FUNC_START_BOOTLOADER		30
#define FUNC_GET_TYPE				0xFE

#define STATE_IDLE					0
#define STATE_READ					1
#define STATE_WRITE					2

#define STATE_STOPPED				3
#define STATE_RUNNING				4

uint8_t usb_state = STATE_IDLE;
uint8_t oszi_state = STATE_STOPPED;

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

uint8_t buffer_data[900];
BUF_t   abuffer;

int main(void)
{
  extern uchar usbNewDeviceAddr;
  uint8_t i;
  BUF_init(&abuffer,buffer_data,sizeof(buffer_data));
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
  LED_poll();
  
  PORTC &= ~(1<<PC1);							   //Pullup aus	
  ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);    // Frequenzvorteiler 
                               					   // setzen auf 8 (1) und ADC aktivieren (1)
  ADMUX = 1;                     				   // Kanal waehlen
  ADMUX |= (1<<REFS1) | (1<<REFS0); 			   // interne Referenzspannung nutzen 
  ADCSRA |= (1<<ADSC);              			   // eine ADC-Wandlung 
  while ( ADCSRA & (1<<ADSC));

  leds[LED_RED].frequency = LED_ON;
  while(1)
    {
      if(usbNewDeviceAddr)
        leds[LED_BLUE].frequency = LED_ON;
      LED_poll();
      usbPoll();
	  if ((oszi_state != STATE_STOPPED) && (abuffer.n < abuffer.size))
	    {
		  oszi_state = oszi_state = STATE_RUNNING;
          ADCSRA |= (1<<ADSC);            // eine Wandlung "single conversion"    
          while ( ADCSRA & (1<<ADSC));
          BUF_put(ADCW,&abuffer);
        }
	}
}

static uchar replyBuffer[8];

uint8_t usbFunctionSetup(uint8_t data[8])
{
  uchar len = 0;

  if(data[1] == FUNC_GET_TYPE)
    {
	  replyBuffer[0] = 9;
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
      len = 0;
	}
  else if(data[1] == FUNC_START)
    {
	  oszi_state = STATE_RUNNING;
      leds[LED_GREEN].frequency = LED_ON;
      leds[LED_RED].frequency = LED_OFF;
      len = 0;
	}
  else if(data[1] == FUNC_STOP)
    {
	  oszi_state = STATE_STOPPED;
      leds[LED_RED].frequency = LED_ON;
      leds[LED_GREEN].frequency = LED_OFF;
      len = 0;
	}
  else if(data[1] == FUNC_READ_EEP)
    {
	  replyBuffer[0] = eeprom_read_byte(data[2]+20);
      len = 1;
	}
  else if(data[1] == FUNC_WRITE_EEP)
    {
	  eeprom_write_byte(data[2]+20,data[3]);
      len = 0;
	}
  usbMsgPtr = replyBuffer;
  return len;
}

uint8_t usbFunctionRead( uint8_t *data, uint8_t len )
{
  if (usb_state != STATE_READ)
    return 0xff;
  int value;
  uint8_t asize = 0;
  while (asize<len)
    {
	  value = BUF_get(&abuffer);
	  if (value == -1) break; 
      data[asize++] = value;
	}
  return asize;
}

uint8_t usbFunctionWrite( uint8_t *data, uint8_t len )
{
  if (usb_state != STATE_WRITE)
    return 0xff;
  return len;
}
