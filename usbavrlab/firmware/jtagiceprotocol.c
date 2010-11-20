/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 ***********************************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include "jtagiceprotocol.h"
#include "usb_uart.h"
#include "isp.h"
#include "timer.h"
#include "led.h"
#include "main.h"

#include <util/delay.h>

#define BUFFER_SIZE     281 /* results in 275 bytes max body size */
#define RX_TIMEOUT      200 /* timeout in milliseconds */

#define STK_TXMSG_START 5

static uint8_t        Buffer[BUFFER_SIZE];
static uint16_t       rxPos;
static uint16_t  	  rxLen;
static uint16_t  	  txLen;

uint8_t    JTAGICE_Status;
stkParam_t JTAGICE_Param;
uint32_t   JTAGICE_Address;

void JTAGICE_init()
{
  JTAGICE_Status = PGM_STATUS_IDLE;
  JTAGICE_Param.s.softwareVersionMajor = eeprom_read_byte(&ee_mem[eeSoftwareMajor]);
  JTAGICE_Param.s.softwareVersionMinor = eeprom_read_byte(&ee_mem[eeSoftwareMinor]);
  if (JTAGICE_Param.s.softwareVersionMajor > 0xa)
    {
      JTAGICE_Param.s.softwareVersionMajor = 2;
      JTAGICE_Param.s.softwareVersionMinor = 0xa;
	}
  JTAGICE_Param.s.hardwareVersion = 1;
}

void JTAGICE_save()
{
  eeprom_write_byte(&ee_mem[eeSoftwareMajor],JTAGICE_Param.s.softwareVersionMajor);
  eeprom_write_byte(&ee_mem[eeSoftwareMinor],JTAGICE_Param.s.softwareVersionMinor);
}
  

void JTAGICE_sendmessage()
{
  uint8_t *p = Buffer, sum = 0;
  uint16_t len;
  *p++ = STK_STX;
  *p++ = Buffer[1];  /* sequence number */
  *p++ = txLen >> 8;
  *p++ = txLen;
  *p++ = STK_TOKEN;

  len = txLen+6;
  txLen = len--;
  p = Buffer;
  while(len--)
    sum ^= *p++;
  *p = sum;
  p = Buffer;
  while (txLen--)
    UART_putc(*p++);
}

void JTAGICE_processmessage()
{
  txLen = 2;
  uint16_t i;
  uint8_t res = 0;
  uint8_t Address_as_byte = 0;
  uint16_t len;
  uint8_t tmp;

  switch (Buffer[STK_TXMSG_START])
    {
	  case STK_CMD_SIGN_ON:
	    {
          static PROGMEM uint8_t JTAGICE_initstring[] = {8, 'S', 'T', 'K', '5', '0', '0', '_', '2', 0};
          uint8_t *p = &Buffer[STK_TXMSG_START + 2];
          strcpy_P(p, JTAGICE_initstring);
          Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
          txLen = 11;
		  break; 
        }
      case STK_CMD_SET_PARAMETER:
	    {
          JTAGICE_Param.bytes[Buffer[STK_TXMSG_START + 1] & 0x1f] = Buffer[STK_TXMSG_START + 2];
		  if (Buffer[STK_TXMSG_START + 1] == STK_PARAM_SCK_DURATION)
		    {
              switch (Buffer[STK_TXMSG_START + 2])
                {
                case 0xfe:
				case 0x4c:
				case 0x3:ISP_Speed = 1;break;
                case 0x2:ISP_Speed = 2;break;
                case 0x1:ISP_Speed = 4;break;
                case 0x0:ISP_Speed = 6;
                }
            } 
          Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
		  break;
        }
      case STK_CMD_GET_PARAMETER:
	    {
		  if (Buffer[STK_TXMSG_START + 1] == STK_PARAM_SCK_DURATION)
		    {
              switch (ISP_Speed)
                {
                case 1:JTAGICE_Param.s.sckDuration = 0xfe;break;
                case 2:
				case 3:JTAGICE_Param.s.sckDuration = 0x2;break;
                case 4:
				case 5:JTAGICE_Param.s.sckDuration = 0x1;break;
                case 6:
				case 7:JTAGICE_Param.s.sckDuration = 0x0;
                }
            } 
          else if (Buffer[STK_TXMSG_START + 1] == STK_PARAM_VTARGET)
		    {
#if defined(USBASP_COMPATIBLE)||defined(CCCB_COMPATIBLE)
  		  	  JTAGICE_Param.s.vTarget = 50;
#else
			  JTAGICE_Param.s.vTarget = ISP_getsupplyvoltage();
#endif
			}  
          Buffer[STK_TXMSG_START + 2] = JTAGICE_Param.bytes[Buffer[STK_TXMSG_START + 1] & 0x1f];
          Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
          txLen = 3;
		  break;
        } 
      default:
	    {
          Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_FAILED;
		}
	   
	}
  JTAGICE_sendmessage();
}

void JTAGICE_byterecived(uint8_t data)
{
  if(rxPos == 0)
    { 
      if (data == STK_STX)
        Buffer[rxPos++] = data;
    }
  else
    {
      if(rxPos < BUFFER_SIZE)
	    {
          Buffer[rxPos++] = data;
          if (rxPos == 4)
		    {
              rxLen = (Buffer[2] << 8)+Buffer[3];
              rxLen += 6;
              if(rxLen > BUFFER_SIZE) //wrong length
			    {
                rxPos = 0;
				}
            }
		  else if (rxPos == 5)
		    {
              if(data != STK_TOKEN)
			    {
                rxPos = 0;
				}
            }
		  else if (rxPos > 4 && rxPos == rxLen)
		    { 
                uint8_t sum = 0;//calculate chksum
                uint8_t *p = Buffer;
                while(rxPos)
				  { 
                    sum ^= *p++;
                    rxPos--;
                  }
                if(sum == 0) //chksum ok
				  { 
                    JTAGICE_processmessage();
                  }
				else //chksum error
 				  {
                    Buffer[STK_TXMSG_START] = STK_ANSWER_CKSUM_ERROR;
                    Buffer[STK_TXMSG_START + 1] = STK_ANSWER_CKSUM_ERROR;
					txLen = 3;
                    JTAGICE_sendmessage();
                  }
            }
        }
	  else
	    { 
          rxPos = 0;
        }
    }
}

