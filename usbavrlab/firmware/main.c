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
 *	2007-11-21
 *	    updated usb driver, fixed some bugs, corercted voltage measurement	
 *  2007-11-20
 *		maked Debug switchable with defines
 *  2007-09-25
 *		added USBasp compatible firmware
 *  2007-09-22								V1.0
 *		corrected AVR910 protocol
 *		Bootloader stuff added  
 *  2007-07-12
 *      AVR910 protocol by Jens Aehle
 *	2007-05-25
 *	    Atmega88 compatibility
 *		CDC Rewrite
 *	    fix of RDY/BSY polling
 *  2007-05-03
 *		RS232 Hardwareinit corrected
 *	2007-04-28
 *		New USB Driver Version
 *		RS232 Logging
 *		Removed Menue for Bootloader Support 
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
#ifdef HASMENUE
  #include "vt100.h"
  #include "menue.h"
#endif
#include "isp.h"
#include "led.h"
#include "timer.h"
#include "stk500protocol.h"
#include "avr910protocol.h"
#include "main.h"

#define PROTOCOL_STK500 0
#define PROTOCOL_AN910  1

uint8_t ee_mem[] EEMEM =
{
   [eeispSpeed] = 0x00,
   [eeSoftwareMajor]  = 0x02,
   [eeSoftwareMinor]  = 0x0a,   
   [eeProtocolType]  = PROTOCOL_STK500
};

#if defined(HAS_STK500_PROTOCOL) && defined(HAS_AVR910_PROTOCOL)
uint8_t ProtocolType;
#endif

#ifdef HASMENUE
void ShowInfo(void);
#ifdef HAS_ISP_SPEEDSETTING
  void opSetSpeed(void) {ISP_Speed = MENUE_entry-4;eeprom_write_byte(&ee_mem[eeispSpeed],ISP_Speed);MENUE_prevlevel();}
  void opAutodetectSpeed(void);
#endif
#ifdef HAS_STK500_PROTOCOL
void SetSTK500Ver(void);
#endif

const struct menueentry_t menue[] PROGMEM = 
	{
	  {0,"Menu"},
#ifdef HAS_INFO
		{1,"Show Info",ShowInfo},
#endif
#ifdef HAS_ISP_SPEEDSETTING
        {1,"ISP Speed"},
  	      {2,"Autodetect",opAutodetectSpeed},
	      {2,"1 khz",opSetSpeed},
	      {2,"93,75 khz",opSetSpeed},
	      {2,"187,5 khz",opSetSpeed},
	      {2,"375 khz",opSetSpeed},
	      {2,"750 khz",opSetSpeed},
	      {2,"1,5 Mhz",opSetSpeed},
	      {2,"3 Mhz",opSetSpeed},
#endif
#ifdef HAS_STK500_PROTOCOL
		  {1,"STK500 SW Ver",SetSTK500Ver},
#endif
	};

const int MENUE_size = sizeof(menue);

#endif

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

#if defined(HASMENUE)
uint8_t inmenue = 0;
#endif
uint8_t inboot = 0;

void Oncharrecived(uint8_t c)
{
  leds[LED_BLUE].counter = 10; 
  leds[LED_BLUE].frequency = LED_FLASH_NEG;
 #if defined(HAS_STK500_PROTOCOL)
   if (STK500_Status == PGM_STATUS_IDLE)
 #endif
 #if defined(HAS_AVR910_PROTOCOL)
   if (AVR910_Status == PGM_STATUS_IDLE)
 #endif
     {
#if defined(HASMENUE)
       if      ((inmenue == 0) && (c == 'm')) inmenue++;
       else if ((inmenue == 1) && (c == 'e')) inmenue++;
       else if ((inmenue == 2) && (c == 'n')) inmenue++;
       else if ((inmenue == 3) && (c == 'u')) inmenue++;
       else if ((inmenue == 4) && (c == 'e')) inmenue++;
       else if ((inmenue == 5) && (c == 0xD))
         {
           inmenue++;
           MENUE_init();
           MENUE_update();
           CDC_charrecived = NULL;
           leds[LED_BLUE].frequency = 100;
         }
       else
         inmenue = 0;
#endif
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
     }  
#ifdef HAS_STK500_PROTOCOL
   STK500_byterecived(c);
#endif
#ifdef HAS_AVR910_PROTOCOL
   AVR910_byterecived(c);
#endif
#if defined(HAS_STK500_PROTOCOL)
  if (STK500_Status == PGM_STATUS_IDLE)
#endif
#if defined(HAS_AVR910_PROTOCOL)
  if (AVR910_Status == PGM_STATUS_IDLE)
#endif
#ifdef HAS_MENUE
  if (inmenue<6)
#endif 
    {
#ifdef HAS_DEBUGPORT
#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__)
       while (!(UCSR0A & (1<<UDRE0)));
       UDR0 = c;
#else
       while (!(UCSRA & (1<<UDRE)));
       UDR = c;
#endif
#endif
     }
}

void Onispstatuschanged(uint8_t status)
{
  leds[LED_GREEN].frequency = LED_OFF;
  leds[LED_RED].frequency = LED_OFF;
  if (status == ISP_STATUS_CONNECTED_OK)
    leds[LED_GREEN].frequency = LED_ON;
  if (status == ISP_STATUS_CONNECTED_NOT_OK)
    leds[LED_RED].frequency = 50;
}

void OnPGMstatuschanged(uint8_t status)
{
  if (status == PGM_STATUS_PROGRAMMING)
    {
	  eeprom_write_byte(&ee_mem[eeispSpeed],ISP_Speed);
	  leds[LED_RED].frequency = 30;
	  leds[LED_GREEN].frequency = LED_OFF;
    }
  else
    Onispstatuschanged(ISP_Status);	  
}

void uartDisconnect(void)
{
  #ifdef HAS_MENUE
  inmenue = 0;
  #endif
  CDC_charrecived = Oncharrecived;
  leds[LED_BLUE].frequency = LED_OFF;
}

#ifdef HAS_DEBUGPORT
#ifndef ISAVRISPMKII
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
 #if defined(HAS_STK500_PROTOCOL)
   if (STK500_Status == PGM_STATUS_IDLE)
 #endif
 #if defined(HAS_AVR910_PROTOCOL)
   if (AVR910_Status == PGM_STATUS_IDLE)
 #endif
 #ifdef HAS_MENUE  
   if (inmenue<6)
 #endif
#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__)
     UART_putc(UDR0);
#else
     UART_putc(UDR);
#endif
}
#endif
#endif

int main(void)
{
  uint8_t i;
  PORTC |= (1<<PC2);
  PORTD |= (1<<PD0);
#if defined(HAS_STK500_PROTOCOL) && defined(HAS_AVR910_PROTOCOL)
  ProtocolType = eeprom_read_byte(&ee_mem[eeProtocolType]);
#endif
  ISP_Speed = eeprom_read_byte(&ee_mem[eeispSpeed]);
  if ((ISP_Speed < 1) | (ISP_Speed > 7))
    ISP_Speed = 5;
#if defined(HAS_AVR910_PROTOCOL) && defined(HAS_STK500_PROTOCOL)
  if (ProtocolType == PROTOCOL_AN910)
#endif
#if defined(HAS_AVR910_PROTOCOL)
    AVR910_init();
#endif
#if defined(HAS_AVR910_PROTOCOL) && defined(HAS_STK500_PROTOCOL)
  else
#endif
#if defined(HAS_STK500_PROTOCOL)
    STK500_init();
#endif
  leds[LED_RED].frequency = LED_ON;
  LED_init();
  for (i=0;i<3;i++)
    TIMER_delay(250);
#ifndef ISAVRISPMKII
  CDC_charrecived = Oncharrecived;
#ifndef ISUSBASP
  CDC_init();
#else
  USBASP_init();
#endif
#else
  AVRISP_init();
#endif
  ISP_statuschanged = Onispstatuschanged;
  PGM_statuschanged = OnPGMstatuschanged;
  leds[LED_RED].frequency = LED_OFF;
#ifdef HAS_DEBUGPORT
#ifndef ISAVRISPMKII
  CDC_ondisconnect = uartDisconnect;
  CDC_uartreset = uartReset;  
#endif
#endif
  while(1)
    {
	  MAIN_tasks();
	}
}

void MAIN_tasks(void)
{
#ifdef HASMENUE
  uint16_t c;
#endif
  MAIN_critical_tasks();
  ISP_checkstatus();
  LED_poll();
#ifdef HASMENUE
  if (inmenue == 6)
    {
      c = UART_getc();
      if (c >> 8 == 0)
        MENUE_task(c);
    }
#endif
}

void MAIN_critical_tasks(void)
{
#ifndef ISAVRISPMKII
  #ifndef ISUSBASP
    CDC_poll(); 
  #else
    usbPoll();
  #endif
#else
  AVRISP_poll();
#endif
}

#ifdef HASMENUE

#ifdef HAS_STK500_PROTOCOL
void PrintSTK500Ver(void)
{
  char version[3];
  Term_Set_Cursor_Position(13,39);
  itoa(STK500_Param.s.softwareVersionMajor,version,16);
  if (strlen(version) == 1)
    UART_putc(0x20);
  UART_puts(version);
  UART_puts_P(PSTR ("."));
  itoa(STK500_Param.s.softwareVersionMinor,version,16);
  if (strlen(version) == 1)
    UART_putc('0');
  UART_puts(version);
}

void SetSTK500Ver(void)
{
  uint16_t c;
  Term_Set_Display_Colour(COL_BACKGROUND,COL_BLUE);
#ifdef HAS_ISP_SPEEDSETTING
  Term_Draw_Window(menue[12].name,29,10,14,3);
#else
  Term_Draw_Window(menue[3].name,29,10,14,3);
#endif
  Term_Set_Cursor_Position(13,30);
  UART_puts_P(PSTR ("Version:"));
  PrintSTK500Ver();
  while (inmenue == 6)
    {
	  c = UART_getc();
      if ((c & 0xFF00) >> 8 == 0)
	    {
		  c = MENUE_is_key(c);
		  if (c == KEY_next)
		    {
			  if (STK500_Param.s.softwareVersionMinor < 0xff)
			    STK500_Param.s.softwareVersionMinor++;
              else 
			    {
  			      STK500_Param.s.softwareVersionMajor++;
   			      STK500_Param.s.softwareVersionMinor = 0;
				}
              PrintSTK500Ver();
			}
		  else if (c == KEY_back)
		    {
			  if (STK500_Param.s.softwareVersionMinor > 0)
			    STK500_Param.s.softwareVersionMinor--;
              else 
			    {
  			      STK500_Param.s.softwareVersionMajor--;
   			      STK500_Param.s.softwareVersionMinor = 0xff;
				}
              PrintSTK500Ver();
			}
		  else if (c == KEY_ok)
		  	{
			  STK500_save();
              return;
			} 	 
		}
      CDC_poll();
	}
}
#endif

#ifdef HAS_INFO

uint8_t ISP_readsignaturebyte(uint8_t addr)
{
  ISP_transmit(0x30);
  ISP_transmit(0x00);
  ISP_transmit(addr);
  return ISP_transmit(0x00);
}

void ShowInfo(void)
{
  uint8_t signature[3];
  uint8_t i;
  char out[3];
  Term_Set_Display_Colour(COL_BACKGROUND,COL_BLUE);
  Term_Draw_Window(PSTR ("Target Information:"),20,7,40,5);
  Term_Set_Cursor_Position(10,21);
  signature[1] = 0x79;
  UART_puts_P(PSTR ("Device bits:"));
  ISP_connect();
  if (ISP_enterprogrammingmode() == 1)
    {
	  UART_puts_P(PSTR ("no device !"));
	}
  else
    {
	  for (i=0;i<3;i++)
	    {
		  signature[i] = ISP_readsignaturebyte(i);
          itoa(signature[i],out,16);
          UART_puts(out);
		  if (i!=2)
            UART_puts_P(PSTR (","));
        }
      Term_Set_Cursor_Position(11,21);
      UART_puts_P(PSTR ("Manufacturer:"));
      if (signature[0] ==0x1e)
	    UART_puts_P(PSTR ("Atmel"));
      else
        UART_puts_P(PSTR ("Unknown"));
      Term_Set_Cursor_Position(12,21);
      UART_puts_P(PSTR ("Flash Memory:"));
      itoa(1<<(signature[1]-0x90),out,10);
      UART_puts(out);
      UART_puts_P(PSTR ("k"));
    }
  ISP_disconnect();  
#ifdef HAS_ISP_SPEEDSETTING
  Term_Draw_Window(PSTR ("Programmer Information"),20,17,40,3);
  Term_Set_Cursor_Position(20,21);
  UART_puts_P(PSTR ("ISP Frequency:"));
  UART_puts_P(menue[4+ISP_Speed].name);
#endif
  while (((UART_getc() & 0xFF) != 0xD) && (inmenue == 6))
    CDC_poll();
}

#endif

#ifdef HAS_ISP_SPEEDSETTING

uint8_t TryISPSpeed(uint8_t speed)
{
  ISP_Speed = speed;
  ISP_connect();
  if (ISP_enterprogrammingmode() == 1)
    {
	  UART_puts_P(PSTR ("failed !"));
      ISP_disconnect();  
	  return 1;
	}
  else
    {
	  UART_puts_P(PSTR ("ok !"));
	  eeprom_write_byte(&ee_mem[eeispSpeed],ISP_Speed);
      ISP_disconnect();  
	  return 0;
    }
}

char strtrying[] PROGMEM = "Trying "; 

void opAutodetectSpeed(void)
{
  uint8_t i;
  Term_Set_Display_Colour(COL_BACKGROUND,COL_BLUE);
  Term_Draw_Window(menue[3].name,20,8,40,10);
  Term_Set_Cursor_Position(8,21);
  for (i=7;i>0;i--)
    {
      Term_Set_Cursor_Position(11+(7-i),21);
      UART_puts_P(strtrying);
      UART_puts_P(menue[4+i].name);
      UART_putc(0x20);
      if (TryISPSpeed(i) == 0) break; 
    } 
  CDC_charrecived = NULL;
  while (((UART_getc() & 0xFF) != 0xD) && (inmenue == 6))
    CDC_poll();
} 

#endif

#endif

