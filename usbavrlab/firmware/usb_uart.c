/************************************************************************************************
 * Project: generic
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 ***********************************************************************************************/


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <string.h>

#include "oddebug.h"
#include "usb_uart.h"
#include "usbconfig.h"
#include "usbdrv.h"
#include "buffer.h"

enum {
    SEND_ENCAPSULATED_COMMAND = 0,
    GET_ENCAPSULATED_RESPONSE,
    SET_COMM_FEATURE,
    GET_COMM_FEATURE,
    CLEAR_COMM_FEATURE,
    SET_LINE_CODING = 0x20,
    GET_LINE_CODING,
    SET_CONTROL_LINE_STATE,
    SEND_BREAK
};


/* Size of bulk transfer packets. The standard demands 8 bytes, but we may
 * be better off with less. Try smaller values if the communication hangs.
 */

#define HW_CDC_PACKET_SIZE      8

/* UART buffer */
//uint8_t rxinptr,rxoutptr;
//uint8_t rx_buf[RX_BUFSIZE];
//uint8_t tx_buf[HW_CDC_PACKET_SIZE2];
//uint8_t txptr = 0;
uint8_t rxbuf_bd[RX_BUFSIZE];
uint8_t txbuf_bd[HW_CDC_PACKET_SIZE];
BUF_t rxbuffer;
BUF_t txbuffer;

uint8_t CDC_mode[7] = {0x80, 0x25, 0, 0, 0, 0, 8};  /* default: 9600 bps, 8n1 */ 

static PROGMEM char deviceDescrCDC[] = {    /* USB device descriptor */
    18,         /* sizeof(usbDescriptorDevice): length of descriptor in bytes */
    USBDESCR_DEVICE,        /* descriptor type */
    0x01, 0x01,             /* USB version supported */
    0x02,                   /* device class: CDC */
    0,                      /* subclass */
    0,                      /* protocol */
    8,                      /* max packet size */
    USB_CFG_VENDOR_ID,      /* 2 bytes */
    USB_CFG_DEVICE_ID,      /* 2 bytes: shared PID for CDC-ACM devices */
    USB_CFG_DEVICE_VERSION, /* 2 bytes */
    1,                      /* manufacturer string index */
    2,                      /* product string index */
    0,                      /* serial number string index */
    1,                      /* number of configurations */
};

static PROGMEM char configDescrCDC[] = {   /* USB configuration descriptor */
    9,          /* sizeof(usbDescrConfig): length of descriptor in bytes */
    USBDESCR_CONFIG,    /* descriptor type */
    67,
    0,          /* total length of data returned (including inlined descriptors) */
    2,          /* number of interfaces in this configuration */
    1,          /* index of this configuration */
    0,          /* configuration name string index */
#if USB_CFG_IS_SELF_POWERED
    USBATTR_SELFPOWER,  /* attributes */
#else
    USBATTR_BUSPOWER,   /* attributes */
#endif
    USB_CFG_MAX_BUS_POWER/2,            /* max USB current in 2mA units */

    /* interface descriptor follows inline: */
    9,          /* sizeof(usbDescrInterface): length of descriptor in bytes */
    USBDESCR_INTERFACE, /* descriptor type */
    0,          /* index of this interface */
    0,          /* alternate setting for this interface */
    USB_CFG_HAVE_INTRIN_ENDPOINT,   /* endpoints excl 0: number of endpoint descriptors to follow */
    USB_CFG_INTERFACE_CLASS,
    USB_CFG_INTERFACE_SUBCLASS,
    USB_CFG_INTERFACE_PROTOCOL,
    0,          /* string index for interface */

    /* CDC Class-Specific descriptor */
    5,           /* sizeof(usbDescrCDC_HeaderFn): length of descriptor in bytes */
    0x24,        /* descriptor type */
    0,           /* header functional descriptor */
    0x10, 0x01,

    4,           /* sizeof(usbDescrCDC_AcmFn): length of descriptor in bytes */
    0x24,        /* descriptor type */
    2,           /* abstract control management functional descriptor */
    0x02,        /* SET_LINE_CODING,    GET_LINE_CODING, SET_CONTROL_LINE_STATE    */

    5,           /* sizeof(usbDescrCDC_UnionFn): length of descriptor in bytes */
    0x24,        /* descriptor type */
    6,           /* union functional descriptor */
    0,           /* CDC_COMM_INTF_ID */
    1,           /* CDC_DATA_INTF_ID */

    5,           /* sizeof(usbDescrCDC_CallMgtFn): length of descriptor in bytes */
    0x24,        /* descriptor type */
    1,           /* call management functional descriptor */
    3,           /* allow management on data interface, handles call management by itself */
    1,           /* CDC_DATA_INTF_ID */

    /* Endpoint Descriptor */
    7,           /* sizeof(usbDescrEndpoint) */
    USBDESCR_ENDPOINT,  /* descriptor type = endpoint */
    0x83,        /* IN endpoint number 3 */
    0x03,        /* attrib: Interrupt endpoint */
    8, 0,        /* maximum packet size */
    100,         /* in ms */

    /* Interface Descriptor  */
    9,           /* sizeof(usbDescrInterface): length of descriptor in bytes */
    4,           /* descriptor type */
    1,           /* index of this interface */
    0,           /* alternate setting for this interface */
    2,           /* endpoints excl 0: number of endpoint descriptors to follow */
    0x0A,        /* Data Interface Class Codes */
    0,
    0,           /* Data Interface Class Protocol Codes */
    0,           /* string index for interface */

    /* Endpoint Descriptor */
    7,           /* sizeof(usbDescrEndpoint) */
    USBDESCR_ENDPOINT,  /* descriptor type = endpoint */
    0x01,        /* OUT endpoint number 1 */
    0x02,        /* attrib: Bulk endpoint */
    HW_CDC_BULK_OUT_SIZE, 0,        /* maximum packet size */




    0,           /* in ms */

    /* Endpoint Descriptor */
    7,           /* sizeof(usbDescrEndpoint) */
    USBDESCR_ENDPOINT,  /* descriptor type = endpoint */
    0x81,        /* IN endpoint number 1 */
    0x02,        /* attrib: Bulk endpoint */
    HW_CDC_BULK_IN_SIZE, 0,        /* maximum packet size */
    0,           /* in ms */
};

static uint8_t        intr3Status;    /* used to control interrupt endpoint transmissions */

/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

uint8_t usbFunctionDescriptor(usbRequest_t *rq)
{
uint8_t *p = NULL, len = 0;

    if(rq->wValue.bytes[1] == USBDESCR_DEVICE)
	  {
        p = (uint8_t *)deviceDescrCDC;
        len = sizeof(deviceDescrCDC);
      }
	else
	  {  /* must be config descriptor */
        p = (uint8_t *)configDescrCDC;
        len = sizeof(configDescrCDC);
      }
    usbMsgPtr = p;
    return len;
}

uint8_t usbFunctionSetup(uint8_t data[8])
{
  usbRequest_t    *rq = (void *)data;
  if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS)
    {    /* class request type */
      if ( rq->bRequest==GET_LINE_CODING || rq->bRequest==SET_LINE_CODING )
	    {
          return 0xff;
          /*    GET_LINE_CODING -> usbFunctionRead()    */
          /*    SET_LINE_CODING -> usbFunctionWrite()    */
        }
      if(rq->bRequest == SET_CONTROL_LINE_STATE)
	    {
          /* Report serial state (carrier detect). On several Unix platforms,
           * tty devices can only be opened when carrier detect is set.
          */
          intr3Status = 2;
        }
    }
  return 0;
}


/*---------------------------------------------------------------------------*/
/* usbFunctionRead                                                          */
/*---------------------------------------------------------------------------*/

uint8_t usbFunctionRead( uint8_t *data, uint8_t len )
{
  memcpy(data, CDC_mode, 7); 
  return 7;
}


/*---------------------------------------------------------------------------*/
/* usbFunctionWrite                                                          */
/*---------------------------------------------------------------------------*/

uint8_t usbFunctionWrite( uint8_t *data, uint8_t len )
{
  /* enforce DATA0 token for next transfer */
  USB_SET_DATATOKEN1(USBPID_DATA1);

  memcpy(CDC_mode, data, 7);
  if (*CDC_uartreset != NULL)
    CDC_uartreset();
  return 1;
}


void usbFunctionWriteOut( uint8_t *data, uint8_t len )
{
//  usbDisableAllRequests();
  for( ; len; len-- ) 
    BUF_put(*data++,&rxbuffer);
//  usbEnableAllRequests();
}

void CDC_init(void)
{
  uint8_t    i;
  
  BUF_init(&rxbuffer,rxbuf_bd,RX_BUFSIZE);
  BUF_init(&txbuffer,txbuf_bd,HW_CDC_PACKET_SIZE);

//Reconnect USB

  usbDeviceDisconnect();  // enforce re-enumeration, do this while interrupts are disabled! 
  i = 0;
  while(--i)
    TIMER_delay(2);
  usbDeviceConnect();

  usbSetInterrupt(0, 0);  /* the host eats the first packet -- don't know why... */
  usbInit();
  sei();
}

void CDC_poll(void)
{
//  wdt_reset();
  usbPoll();
  /*    usb -> rs232c:  ready to receive?    */
//  if( usbAllRequestsAreDisabled() /*&& uartRxBytesFree()>=8 */) //TODo
//     usbEnableAllRequests();

  if( usbInterruptIsReady() ) 
    {
	  static uchar sendEmptyFrame = 1;
      if ( txbuffer.n || sendEmptyFrame ) 
	    {
	      usbSetInterrupt((uchar *)txbuffer.buf, txbuffer.n);
		  /* send an empty block after last data block to indicate transfer end */
          sendEmptyFrame = txbuffer.n==HW_CDC_PACKET_SIZE? 1:0;
	 	}
      BUF_flush(&txbuffer);
    }
  /*rs232 -> usb*/
  if (*CDC_sendmode != NULL)
    CDC_sendmode();
  if (rxbuffer.n > 0)
    if (*CDC_charrecived != NULL)
	  CDC_charrecived(BUF_get(&rxbuffer));
  if (*CDC_receivemode != NULL)
    CDC_receivemode();
  /* We need to report rx and tx carrier after open attempt */
  if(intr3Status != 0 && usbInterruptIsReady3())
    {
      static uint8_t serialStateNotification[10] = {0xa1, 0x20, 0, 0, 0, 0, 2, 0, 3, 0};
      if(intr3Status == 2)
        usbSetInterrupt3(serialStateNotification, 8);
      else
        usbSetInterrupt3(serialStateNotification+8, 2);
      intr3Status--;
      if (*CDC_ondisconnect != NULL)
	    CDC_ondisconnect(); 
    }
}


void UART_putc(uint8_t data)
{
  BUF_put(data,&txbuffer);
  while (txbuffer.n == 8)
    CDC_poll();
}

void UART_puts(const char *s )
{
  while (*s) 
    UART_putc(*s++);
}

void UART_puts_P(const char *s )
{
  char c;
  while ((c = pgm_read_byte(s++)) ) 
    {
      UART_putc(c);
    }
}

uint16_t UART_getc(void)
{    
  if (rxbuffer.n)
    return BUF_get(&rxbuffer);
  else
    return UART_NO_DATA;
}


