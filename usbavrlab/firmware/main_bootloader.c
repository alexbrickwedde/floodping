/************************************************************************************************
 * Project: USB AVR-ISP Bootloader
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 *
 *based on AVRUSBBoot by Thomas Fischl <tfischl@gmx.de> 
 *Changes:
 *	2008/11/21 Modified for 20 Mhz, new usb driver
 ***********************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/boot.h>
#include <util/delay.h>

#include "config.h"
#include "usbdrv.h" 

#define FUNC_GET_TYPE				0xFE
#define FUNC_WRITE_EEP  			4
#define FUNC_WRITE_PAGE 			2
#define FUNC_LEAVE_BOOT 			1
#define FUNC_GET_PAGESIZE 			3		 
#define FUNC_GET_CONTROLLER			5		 
#define FUNC_GET_MCUCSR				6		 

#define CONTROLLER_ATMEGA8			1
#define CONTROLLER_ATMEGA88			2
#define CONTROLLER_ATMEGA168		3

#define CONTROLLER_ATMEGA8_20		11
#define CONTROLLER_ATMEGA88_20		12
#define CONTROLLER_ATMEGA168_20		13

#define STATE_IDLE 0
#define STATE_WRITE_PAGE 1 
#define STATE_WRITE_EEP  2 

static uchar replyBuffer[8];
static uchar state = STATE_IDLE;
static unsigned int page_address;
static unsigned int page_offset; 

void MAIN_tasks(void);

void (*jump_to_app)(void) = 0x0000; 

void StartApplication(void) 
{
  cli();
  boot_rww_enable();
#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) 
  MCUCR = (1 << IVCE);  /* enable change of interrupt vectors */
  MCUCR = (0 << IVSEL); /* move interrupts to boot flash section */
#else
  GICR = (1 << IVCE);  /* enable change of interrupt vectors */
  GICR = (0 << IVSEL); /* move interrupts to boot flash section */
#endif
  jump_to_app();
} 

int main(void)
{
  uchar    i;
  PORTC |= (1<<PC2);

  if (!(
     ((PINC & (1<<PC2)) == 0)   			//Bootloader Jumper setted ?
  || ((pgm_read_byte(0) == 0xFF) && (pgm_read_byte(1) == 0xFF) && (pgm_read_byte(2) == 0xFF))			//already Programmed ? 
#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) 
  || (MCUSR & (1<<WDRF))					//Watchdog reset from Application
#else
  || (MCUCSR & (1<<WDRF))					//Watchdog reset from Application
#endif
     ))
	{ 
#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) 
	  MCUSR &= 0xE0;  
#else
	  MCUCSR &= 0xE0;  
#endif
      StartApplication();
    }

#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) 
	  MCUSR &= 0xE0;  
#else
	  MCUCSR &= 0xE0;  
#endif
#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) 
  MCUCR = (1 << IVCE);  // enable change of interrupt vectors 
  MCUCR = (1 << IVSEL); // move interrupts to boot flash section
  wdt_disable(); 
#else
  GICR = (1 << IVCE);  // enable change of interrupt vectors
  GICR = (1 << IVSEL); // move interrupts to boot flash section
#endif
//Reconnect USB
  usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
  i = 0;
  while(--i)
     _delay_ms(2);
  usbDeviceConnect();
  usbInit();
  sei();
//LED Status
#ifndef USBASP_COMPATIBLE
  DDRC = (1<<PC3)|(1<<PC4)|(1<<PC5);
  PORTC &= ~(1<<PC3); //Green led on
  PORTC &= ~(1<<PC4); //Green red on
  PORTC |= (1<<PC5);  //Green blue off
#else
  DDRC = (1<<PC1)|(1<<PC3);
  PORTC &= ~(1<<PC1); //Green led on
  PORTC |= (1<<PC3);  //Green red off
#endif

  while(1)
    usbPoll();
}

uint8_t usbFunctionSetup(uint8_t data[8])
{
    uchar len = 0;
    
    if (data[1] == FUNC_LEAVE_BOOT) 
	  {
	    StartApplication();
      } 
	else if (data[1] == FUNC_WRITE_PAGE) 
	  {
        state = STATE_WRITE_PAGE;
        page_address = (data[3] << 8) | data[2]; /* page address */
        page_offset = 0;
        eeprom_busy_wait();
        cli();
        boot_page_erase(page_address); /* erase page */
        sei();
        boot_spm_busy_wait(); /* wait until page is erased */
        len = 0xff; /* multiple out */
      } 
	else if (data[1] == FUNC_WRITE_EEP) 
	  {
        eeprom_write_byte(data[2],data[3]);
      } 
	else if (data[1] == FUNC_GET_PAGESIZE) 
	  {
        replyBuffer[0] = SPM_PAGESIZE >> 8;
        replyBuffer[1] = SPM_PAGESIZE & 0xff;
        len = 2;
      }
	else if (data[1] == FUNC_GET_CONTROLLER) 
	  {

#if USB_CFG_CLOCK_KHZ == 12000
#if defined(__AVR_ATmega8__) 
        replyBuffer[0] = CONTROLLER_ATMEGA8;
#endif
#if defined(__AVR_ATmega88__) 
        replyBuffer[0] = CONTROLLER_ATMEGA88;
#endif
#if defined(__AVR_ATmega168__) 
        replyBuffer[0] = CONTROLLER_ATMEGA168;
#endif
#elif USB_CFG_CLOCK_KHZ == 20000
#if defined(__AVR_ATmega8__) 
        replyBuffer[0] = CONTROLLER_ATMEGA8_20;
#endif
#if defined(__AVR_ATmega88__) 
        replyBuffer[0] = CONTROLLER_ATMEGA88_20;
#endif
#if defined(__AVR_ATmega168__) 
        replyBuffer[0] = CONTROLLER_ATMEGA168_20;
#endif
#else
#   error "USB_CFG_CLOCK_KHZ is not one of the supported rates!"
#endif
        len = 1;
      }
	else if (data[1] == FUNC_GET_TYPE) 
	  {
        replyBuffer[0] = 1; //Bootloader
        len = 1;
      }
    usbMsgPtr = replyBuffer;
    return len; 
}

uint8_t usbFunctionWrite( uint8_t *data, uint8_t len )
{
  uchar i;
  /* check if we are in correct state */
  if (state == STATE_WRITE_PAGE)
    {
      for (i = 0; i < len; i+=2) 
        {
          cli();    
          boot_page_fill(page_address + page_offset, data[i] | (data[i + 1] << 8));
          sei();
          page_offset += 2;
          /* check if we are at the end of a page */
          if (page_offset >= SPM_PAGESIZE) 
	        {
              /* write page */
              cli();
              boot_page_write(page_address);
              sei();
              boot_spm_busy_wait();
              state = STATE_IDLE;
              return 1;
            }

        }
    }
  else if (state == STATE_WRITE_EEP)
    {
      for (i = 0; i < len; i++) 
        eeprom_write_byte(page_address + i,data[i]);
      return 1;
	}
  else
    return 0xff;
  return 0;
}

