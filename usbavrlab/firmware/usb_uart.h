/************************************************************************************************
 * Project: generic
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2
 ***********************************************************************************************/

#ifndef __cdc_usb_h_included__
#define __cdc_usb_h_included__

#include <usbdrv.h>

#define RX_BUFSIZE 64

typedef union {
    unsigned long	dword;
    uint8_t         bytes[4];
} dword_helper_t;

#if UART_CFG_HAVE_USART
#define HW_CDC_BULK_OUT_SIZE     8
#else
#define HW_CDC_BULK_OUT_SIZE     1
#endif
#define HW_CDC_BULK_IN_SIZE      8

extern uint8_t CDC_mode[7];

extern uint8_t tx_buf[HW_CDC_BULK_IN_SIZE];
extern uint8_t rx_buf[RX_BUFSIZE];

void (*CDC_ondisconnect)(void); 
void (*CDC_charrecived)(uint8_t data); 
void (*CDC_uartreset)(); 
void (*CDC_receivemode)(); 
void (*CDC_sendmode)(); 

#define UART_NO_DATA 0x100

uint16_t UART_getc(void);
void UART_putc(unsigned char data);
void UART_puts(const char *s );
void UART_puts_P(const char *s );

uint8_t CDC_usbFunctionDescriptor(usbRequest_t *rq);
uint8_t CDC_usbFunctionSetup(uint8_t data[8]);
uint8_t CDC_usbFunctionRead( uint8_t *data, uint8_t len );
uint8_t CDC_usbFunctionWrite( uint8_t *data, uint8_t len );
void CDC_usbFunctionWriteOut( uint8_t *data, uint8_t len );
void CDC_init(void);
void CDC_poll(void);

#endif
