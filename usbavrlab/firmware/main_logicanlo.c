/************************************************************************************************
 * Project: USB AVR-ISP Logic-Analyzer
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 ***********************************************************************************************/

#include "config.h"

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include "led.h"
#include "main.h"
#include "timer.h"
#include "usbdrv.h"
#include "usbconfig.h"
#include "usb_uart.h"
#include "isp.h"

led_t leds[] =  {{4,LED_OFF,LED_OFF},
                 {3,LED_OFF,LED_OFF},
                 {5,LED_OFF,LED_OFF}}; 
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

#define CHANNEL_5 PD0
#define CHANNEL_6 PD1

#define DATA_SIZE 850

uint8_t data[DATA_SIZE];
uint16_t data_ptr = 0;

uint8_t LOG_on = 0;

uint8_t TriggerChannel = 1;
uint8_t channel1trigger = 0;
uint8_t channel2trigger = 0;

uint8_t DATA_trigger(void)
{
  uint8_t tmp1 = CHANNELPIN1; 
  uint8_t tmp2 = CHANNELPIN1;
  TIMER_start(40); //we must poll usb every 50ms 
 
  while (TIMER_timeout)
    {
      if (((channel1trigger & tmp1) == channel1trigger) || ((channel2trigger & tmp2) == channel2trigger))
        return 1;
      tmp1 = CHANNELPIN1;
	  tmp2 = CHANNELPIN2;
    }
  return 0;
}

void DATA_collect(void)
{

}

void DATA_send(void)
{
  uint16_t i;
  for (i = 0;i<DATA_SIZE;i++)
    {
      UART_putc(data[i]);
	  CDC_poll();
	}
}

void uartDisconnect(void)
{
  leds[LED_BLUE].frequency = LED_OFF;
}

void uartReset(void)
{
  leds[LED_BLUE].frequency = LED_ON;
}

uint8_t cmdidx = 0;

void Oncharrecived(uint8_t c)
{
}

int main(void)
{
  uint8_t i;
  for (i=0;i<3;i++)
    TIMER_delay(250);
  CDC_init();
  //Initialize ports

//  LED_init();
//  leds[LED_GREEN].frequency = LED_ON;

/*  CHANNELDDR1 &= ~((1 << CHANNEL_1) | (1 << CHANNEL_2) | (1 << CHANNEL_3) | (1 << CHANNEL_4));
  CHANNELPORT1 |= ((1 << CHANNEL_1) | (1 << CHANNEL_2) | (1 << CHANNEL_3) | (1 << CHANNEL_4));
  CHANNELDDR2 &= ~((1 << CHANNEL_5) | (1 << CHANNEL_6));
  CHANNELPORT2 |= ((1 << CHANNEL_5) | (1 << CHANNEL_6));*/

//  CDC_ondisconnect = uartDisconnect;
//  CDC_uartreset = uartReset;
//  CDC_charrecived = Oncharrecived;
  
  while(1)
    MAIN_tasks();
}

void MAIN_tasks(void)
{
  LED_poll();
  CDC_poll();
/*  if (DATA_trigger())
    {
      leds[LED_RED].counter = 10; 
      leds[LED_RED].frequency = LED_FLASH;
	  DATA_collect();
	  DATA_send();
	}*/
}

uint8_t usbFunctionSetup(uint8_t data[8])
{
  return CDC_usbFunctionSetup(data);
}

uint8_t usbFunctionRead( uint8_t *data, uint8_t len )
{
  return CDC_usbFunctionRead(data,len);
}

uint8_t usbFunctionWrite( uint8_t *data, uint8_t len )
{
  return CDC_usbFunctionWrite(data,len);
}

void usbFunctionWriteOut( uint8_t *data, uint8_t len )
{
  return CDC_usbFunctionWriteOut(data,len);
}

uint8_t usbFunctionDescriptor(usbRequest_t *rq)
{
  return CDC_usbFunctionDescriptor(rq);
}
