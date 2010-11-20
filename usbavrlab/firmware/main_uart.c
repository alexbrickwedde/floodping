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
 ***********************************************************************************************/

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
#include "isp.h"
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

#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__)
  UDR0 = c;
  while (!(UCSR0A & (1<<UDRE0)));
#else
  UDR = c;
  while (!(UCSRA & (1<<UDRE)));
#endif
}

void Onsendmode(void)
{
  PORTD &= ~(1<<PD7);
}

void Onreceivemode(void)
{
  PORTD |= (1<<PD7);
}

void uartDisconnect(void)
{
  #ifdef HAS_MENUE
  inmenue = 0;
  #endif
  CDC_charrecived = Oncharrecived;
  leds[LED_BLUE].frequency = LED_OFF;
}

void uartReset(void)
{
  leds[LED_BLUE].frequency = LED_ON;
  uint16_t baudrate = (CDC_mode[1]<<8)+CDC_mode[0];
  baudrate = ((F_CPU)/(( baudrate )*16l)-1);
#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__)
  UCSR0B  = 0;
  UBRR0H = (uint8_t)(baudrate>>8);
  UBRR0L = (uint8_t) baudrate;
  UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
#else
  UCSRB  = 0;
  UBRRH = (uint8_t)(baudrate>>8);
  UBRRL = (uint8_t) baudrate;
  UCSRB = (1<<RXEN) | (1<<TXEN) | (1<<RXCIE);
#endif
}

#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__)
ISR(USART_RX_vect)
#else
ISR(USART_RXC_vect)
#endif
{
  leds[LED_GREEN].counter = 10; 
  leds[LED_GREEN].frequency = LED_FLASH;
#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__)
     UART_putc(UDR0);
#else
     UART_putc(UDR);
#endif
}


int main(void)
{
  uint8_t i;
  PORTC |= (1<<PC2);
  PORTD |= (1<<PD0);
  DDRD  |= (1<<PD7);
  PORTD |= (1<<PD7);
  leds[LED_RED].frequency = LED_ON;
  LED_init();
  for (i=0;i<3;i++)
    TIMER_delay(250);
  CDC_charrecived = Oncharrecived;
  CDC_sendmode = Onsendmode;
  CDC_receivemode = Onreceivemode;
  CDC_init();
  leds[LED_RED].frequency = LED_OFF;
  CDC_ondisconnect = uartDisconnect;
  CDC_uartreset = uartReset;  
  while(1)
    {
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
  usbPoll();
}

