#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdio.h>
#include "usbdrv.h"
#include "isp.h"
#include "led.h"
#include "main.h"
#include "timer.h"
#include "buffer.h"

#define USBASP_FUNC_CONNECT     	1
#define USBASP_FUNC_DISCONNECT  	2
#define USBASP_FUNC_TRANSMIT    	3
#define USBASP_FUNC_READFLASH   	4
#define USBASP_FUNC_ENABLEPROG  	5
#define USBASP_FUNC_WRITEFLASH  	6
#define USBASP_FUNC_READEEPROM  	7
#define USBASP_FUNC_WRITEEEPROM 	8
#define USBASP_FUNC_SETLONGADDRESS 	9
#define FUNC_START_BOOTLOADER		30
#define FUNC_SET_CDC_MODE			31
#define FUNC_CDC_READ				32
#define FUNC_CDC_WRITE				33
#define FUNC_GET_TYPE				0xFE

#define PROG_STATE_IDLE         	0
#define PROG_STATE_WRITEFLASH   	1
#define PROG_STATE_READFLASH    	2
#define PROG_STATE_READEEPROM   	3
#define PROG_STATE_WRITEEEPROM  	4
#define STATE_WRITE_CDC				5
#define STATE_READ_CDC				6
#define STATE_SET_CDC_MODE			7

#define PROG_BLOCKFLAG_FIRST    	1
#define PROG_BLOCKFLAG_LAST     	2


uint8_t CDC_mode[7] = {0x80, 0x25, 0, 0, 0, 0, 8};  // default: 9600 bps, 8n1
static uchar replyBuffer[8];
static uchar prog_state = PROG_STATE_IDLE;

static uchar prog_address_newmode = 0;
static unsigned long prog_address;
static unsigned int prog_nbytes = 0;
static unsigned int prog_pagesize;
static uchar prog_blockflags;
static uchar prog_pagecounter;
unsigned char debug_buffer_data[100];
BUF_t debug_buffer;

void USBASP_init(void)
{
  uchar    i;
//Reconnect USB
  usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
  i = 0;
  while(--i)
     _delay_ms(2);
  usbDeviceConnect();
  usbInit();
  sei();
  BUF_init(&debug_buffer,debug_buffer_data,sizeof(debug_buffer_data));
}

void UART_putc(uchar data)
{
  BUF_put(data,&debug_buffer);
}

uchar usbFunctionSetup(uchar data[8])
{
  uchar len = 0;

  if(data[1] == FUNC_GET_TYPE)
    {
	  replyBuffer[0] = 2;
	  len = 1;
	}
  else if(data[1] == FUNC_START_BOOTLOADER)
    {
      cli();
	  wdt_enable(WDTO_15MS);
      while(1);
	  len = 0;
	}
  else if(data[1] == USBASP_FUNC_CONNECT)
    {
      prog_address_newmode = 0;
      ISP_connect();
      leds[LED_RED].frequency = LED_ON;
    } 
  else if (data[1] == USBASP_FUNC_DISCONNECT) 
    {
      ISP_disconnect();
      leds[LED_RED].frequency = LED_OFF;
    } 
  else if (data[1] == USBASP_FUNC_TRANSMIT) 
    {
      replyBuffer[0] = ISP_transmit(data[2]);
      replyBuffer[1] = ISP_transmit(data[3]);
      replyBuffer[2] = ISP_transmit(data[4]);
      replyBuffer[3] = ISP_transmit(data[5]);
      len = 4;
    } 
  else if (data[1] == USBASP_FUNC_READFLASH) 
    {
      if (!prog_address_newmode)
        prog_address = (data[3] << 8) | data[2];
      prog_nbytes = (data[7] << 8) | data[6];
      prog_state = PROG_STATE_READFLASH;
      len = 0xff; // multiple in
    } 
  else if (data[1] == USBASP_FUNC_READEEPROM) 
    {
      if (!prog_address_newmode)
        prog_address = (data[3] << 8) | data[2];
      prog_nbytes = (data[7] << 8) | data[6];
      prog_state = PROG_STATE_READEEPROM;
      len = 0xff; // multiple in
    } 
  else if (data[1] == USBASP_FUNC_ENABLEPROG) 
    {
      replyBuffer[0] = ISP_enterprogrammingmode();
      len = 1;
    } 
  else if (data[1] == USBASP_FUNC_WRITEFLASH) 
    {
      if (!prog_address_newmode)
        prog_address = (data[3] << 8) | data[2];
      prog_pagesize = data[4];
      prog_blockflags = data[5] & 0x0F;
      prog_pagesize += (((unsigned int)data[5] & 0xF0)<<4);
      if (prog_blockflags & PROG_BLOCKFLAG_FIRST) 
	    {
          prog_pagecounter = prog_pagesize;
        }
      prog_nbytes = (data[7] << 8) | data[6];
      prog_state = PROG_STATE_WRITEFLASH;
      len = 0xff; // multiple out 
    } 
  else if (data[1] == USBASP_FUNC_WRITEEEPROM) 
    {
      if (!prog_address_newmode)
        prog_address = (data[3] << 8) | data[2];
      prog_pagesize = 0;
      prog_blockflags = 0;
      prog_nbytes = (data[7] << 8) | data[6];
      prog_state = PROG_STATE_WRITEEEPROM;
      len = 0xff; // multiple out
    } 
  else if(data[1] == USBASP_FUNC_SETLONGADDRESS) 
    {
      // set new mode of address delivering (ignore address delivered in commands) 
      prog_address_newmode = 1;
      // set new address 
      prog_address = *((unsigned long*)&data[2]);
    }
  else if (data[0] == FUNC_CDC_WRITE)
    {
      prog_state = STATE_WRITE_CDC;
      len = 0xff; // multiple out
	}
  else if (data[0] == FUNC_CDC_READ)
    {
      prog_state = STATE_READ_CDC;
      len = 0xff; // multiple out
	}
  else if (data[0] == FUNC_SET_CDC_MODE)
    {
      prog_state = STATE_SET_CDC_MODE;
	  len = 0xFF;
	}
  usbMsgPtr = replyBuffer;
  return len;
}

uchar ispReadFlash(unsigned long address) 
{
  ISP_transmit(0x20 | ((address & 1) << 3));
  ISP_transmit(address >> 9);
  ISP_transmit(address >> 1);
  return ISP_transmit(0);
}


uchar ispWriteFlash(unsigned long address, uchar data, uchar pollmode) 
{
  ISP_transmit(0x40 | ((address & 1) << 3));
  ISP_transmit(address >> 9);
  ISP_transmit(address >> 1);
  ISP_transmit(data);

  if (pollmode == 0)
    return 0;

  if (data == 0x7F) {
    TIMER_delay(5); // wait 4,8 ms 
    return 0;
  } else {

    // polling flash 
    uchar retries = 30;
	TIMER_start(1);
    while (retries != 0) {
      if (ispReadFlash(address) != 0x7F) {
	return 0;
      };
      
      if (TIMER_timeout == 0) 
	    {
   	      TIMER_start(1);
	      retries --;
        }

    }
    return 1; // error 
  }
}

uchar ispFlushPage(unsigned long address, uchar pollvalue) 
{
  ISP_transmit(0x4C);
  ISP_transmit(address >> 9);
  ISP_transmit(address >> 1);
  ISP_transmit(0);


  if (pollvalue == 0xFF) {
    TIMER_delay(5);
    return 0;
  } else {

    // polling flash 
    uchar retries = 30;
	TIMER_start(1);


    while (retries != 0) {
      if (ispReadFlash(address) != 0xFF) {
	return 0;
      };

      if (TIMER_timeout == 0) 
	    {
   	      TIMER_start(1);
	      retries --;
        }
    }

    return 1; // error 
  }
}


uchar ispReadEEPROM(unsigned int address) 
{
  ISP_transmit(0xA0);
  ISP_transmit(address >> 8);
  ISP_transmit(address);
  return ISP_transmit(0);
}


uchar ispWriteEEPROM(unsigned int address, uchar data) 
{
  ISP_transmit(0xC0);
  ISP_transmit(address >> 8);
  ISP_transmit(address);
  ISP_transmit(data);

  TIMER_delay(10); // wait 9,6 ms 

  return 0;
} 
 
uchar usbFunctionRead(uchar *data, uchar len)
{
 uchar i;
 int c;

  // check if programmer is in correct read state 
  if (
      (prog_state != PROG_STATE_READFLASH) 
   && (prog_state != PROG_STATE_READEEPROM)
   && (prog_state != STATE_READ_CDC)
     ) 
    return 0xff;

  // fill packet 
  for (i = 0; i < len; i++) 
    {
      if (prog_state == PROG_STATE_READFLASH) 
        data[i] = ispReadFlash(prog_address);
      else if (prog_state == PROG_STATE_READEEPROM) 
        data[i] = ispReadEEPROM(prog_address);
      else if (prog_state == STATE_READ_CDC) 
	    {
		  c = BUF_get(&debug_buffer);
		  if (c == -1) break;
		  data[i] = c;
		}
      prog_address++;
    }
  // last packet? 
  if (len < 8) 
    prog_state = PROG_STATE_IDLE;
  return i;
}

uchar usbFunctionWrite(uchar *data, uchar len)
{
  uchar retVal = 0;
  uchar i;

  // check if programmer is in correct write state 
  if (
      (prog_state != PROG_STATE_WRITEFLASH) 
	&&(prog_state != PROG_STATE_WRITEEEPROM)
	&&(prog_state != STATE_WRITE_CDC)
	&&(prog_state != STATE_SET_CDC_MODE)
	 ) 
    return 0xff;

  for (i = 0; i < len; i++) 
    {
      if (prog_state == PROG_STATE_WRITEFLASH) 
	    {
          if (prog_pagesize == 0)
    	    ispWriteFlash(prog_address, data[i], 1);
          else
        	ispWriteFlash(prog_address, data[i], 0);
	      prog_pagecounter --;
	      if (prog_pagecounter == 0) 
		    {
	          ispFlushPage(prog_address, data[i]);
	          prog_pagecounter = prog_pagesize;
	        }
          prog_nbytes --;
        }
	  else if (prog_state == PROG_STATE_WRITEEEPROM) 
	    {
          ispWriteEEPROM(prog_address, data[i]);
          prog_nbytes --;
        }
      else if (prog_state == STATE_WRITE_CDC)
	    Oncharrecived(data[i]);
      else if (prog_state == STATE_SET_CDC_MODE)
	    CDC_mode[i] = data[i];
      if (prog_nbytes == 0) 
	    {
          prog_state = PROG_STATE_IDLE;
          if ((prog_blockflags & PROG_BLOCKFLAG_LAST) && (prog_pagecounter != prog_pagesize)) 
        	ispFlushPage(prog_address, data[i]);
          retVal = 1; // Need to return 1 when no more data is to be received
        }
      prog_address ++;
    }
  if (prog_state == STATE_SET_CDC_MODE)
    prog_state = PROG_STATE_IDLE;
  return retVal;
}

