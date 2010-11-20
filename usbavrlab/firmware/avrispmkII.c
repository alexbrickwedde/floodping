/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-09-19
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 *
 * Changes:
 ***********************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <string.h>
#include <util/delay.h>
#include <stk500protocol.h>
#include <led.h>
#include <config.h>
#include "main.h"

#include "usb_uart.h"
#include "usbconfig.h"
#include "usbdrv.h"
#include "buffer.h"

#define FUNC_START_BOOTLOADER		30
#define FUNC_GET_TYPE				0xFE

#define USB_EP_SIZE 				8

/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

PROGMEM char usbDescriptorConfiguration[] = {
	9,
	USBDESCR_CONFIG,
	18 + 7 * 2 * USB_CFG_HAVE_INTRIN_ENDPOINT + (USB_CFG_DESCR_PROPS_HID & 0xff), 0,
	1,
	1,
	0,
#if USB_CFG_IS_SELF_POWERED
	USBATTR_SELFPOWER,
#else
	USBATTR_BUSPOWER,
#endif
	USB_CFG_MAX_BUS_POWER/2,
	9,
	USBDESCR_INTERFACE,
	0,
	0,
	2 * USB_CFG_HAVE_INTRIN_ENDPOINT,
	USB_CFG_INTERFACE_CLASS,
	USB_CFG_INTERFACE_SUBCLASS,
	USB_CFG_INTERFACE_PROTOCOL,
	0,
	7,
	USBDESCR_ENDPOINT,
	0x82,
	0x02,
	8, 0,
	USB_CFG_INTR_POLL_INTERVAL,
	7,
	USBDESCR_ENDPOINT,
	0x02,
	0x02,
	8, 0,
	USB_CFG_INTR_POLL_INTERVAL,
};

static uchar replyBuffer[8];

uchar usbFunctionSetup(uchar data[8])
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


  usbMsgPtr = replyBuffer;
  return len;
}

uchar usbFunctionDescriptor(usbRequest_t *rq) 
{
  usbMsgPtr = (uchar *)usbDescriptorConfiguration;
  return sizeof(usbDescriptorConfiguration);
}

void usbFunctionWriteOut( uint8_t *data, uint8_t len )
{
  leds[LED_BLUE].counter = 10; 
  leds[LED_BLUE].frequency = LED_FLASH_NEG;
  memcpy(STK500_Buffer+STK500_rxPos,data,len);
  STK500_rxPos += len;
  if((len < USB_EP_SIZE) 
  ||(((STK500_Buffer[0] == 0x13) 
  ||(STK500_Buffer[0] == 0x15)) && ((((uint16_t)(STK500_Buffer[1] & 1) << 8) | STK500_Buffer[2]) == (STK500_rxPos - 10))) 
  ||((STK500_Buffer[0] == 0x1D) && (STK500_Buffer[1] == (STK500_rxPos - 4))) )
	{
	  STK500_rxLen = STK500_rxPos;
	  STK500_rxPos = 0;
	}
}

void AVRISP_init(void)
{
  STK500_init();
  uint8_t i;
//Reconnect USB
  usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
  i = 0;
  while(--i)
     _delay_ms(2);
  usbDeviceConnect();
  usbSetInterrupt(0, 0);		/* the host eats the first packet -- don't know why... */
  usbInit();
  sei();
}

uint16_t STK500_txLen_tmp = 0;
uint16_t RSP_Pkg_Len;


void AVRISP_poll(void)
{
  extern uchar usbNewDeviceAddr;
  usbPoll();
  if ((STK500_rxLen))
    {
      STK500_processmessage();
      STK500_rxLen = 0; 
	}
  if(usbNewDeviceAddr)
    leds[LED_BLUE].frequency = LED_ON;

  if ((STK500_txLen) && (usbInterruptIsReady()))
    {
	  RSP_Pkg_Len = STK500_txLen - STK500_txLen_tmp;
	  if(RSP_Pkg_Len > USB_EP_SIZE)
		RSP_Pkg_Len = USB_EP_SIZE;
	  usbSetInterrupt((uchar*)STK500_Buffer + STK500_txLen_tmp,RSP_Pkg_Len);
		STK500_txLen_tmp += RSP_Pkg_Len;
      if(RSP_Pkg_Len < USB_EP_SIZE)
		{
	 	  STK500_txLen = 0;
		  STK500_txLen_tmp = 0;
		}
    }
}
