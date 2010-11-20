/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2
 ***********************************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include "stk500protocol.h"
#include "usb_uart.h"
#include "isp.h"
#include "timer.h"
#include "led.h"
#include "main.h"

#include <util/delay.h>

#define BUFFER_SIZE     281 // results in 275 bytes max body size
#define RX_TIMEOUT      200 // timeout in milliseconds

#ifndef ISAVRISPMKII
 #define STK_TXMSG_START 5
#else
 #define STK_TXMSG_START 0
#endif

uint8_t       	STK500_Buffer[BUFFER_SIZE];
uint16_t       	STK500_rxPos = 0;
uint16_t  	   	STK500_rxLen = 0;
uint16_t  	  	STK500_txLen;

uint8_t    		STK500_Status;
stkParam_t 		STK500_Param;
uint32_t   		STK500_Address;

extern uint8_t 	ee_mem[];

void STK500_init()
{
  STK500_Status = PGM_STATUS_IDLE;
  STK500_Param.s.softwareVersionMajor = eeprom_read_byte(&ee_mem[eeSoftwareMajor]);
  STK500_Param.s.softwareVersionMinor = eeprom_read_byte(&ee_mem[eeSoftwareMinor]);
  if (STK500_Param.s.softwareVersionMajor > 0xa)
    {
      STK500_Param.s.softwareVersionMajor = 2;
      STK500_Param.s.softwareVersionMinor = 0xa;
	}
  STK500_Param.s.hardwareVersion = 1;
}

void STK500_save()
{
  eeprom_write_byte(&ee_mem[eeSoftwareMajor],STK500_Param.s.softwareVersionMajor);
  eeprom_write_byte(&ee_mem[eeSoftwareMinor],STK500_Param.s.softwareVersionMinor);
}
  

void STK500_sendmessage()
{
#ifndef ISAVRISPMKII
  uint8_t *p = STK500_Buffer, sum = 0;
  uint16_t len;
  *p++ = STK_STX;
  *p++ = STK500_Buffer[1];  /* sequence number */
  *p++ = STK500_txLen >> 8;
  *p++ = STK500_txLen;
  *p++ = STK_TOKEN;

  len = STK500_txLen+6;
  STK500_txLen = len--;
  p = STK500_Buffer;
  while(len--)
    sum ^= *p++;
  *p = sum;
  p = STK500_Buffer;
  while (STK500_txLen--)
    UART_putc(*p++);
#endif
}

void STK500_processmessage()
{
  uint16_t i;
  uint8_t res = 0;
  uint8_t Address_as_byte = 0;
  uint16_t len;
  uint8_t tmp;
  STK500_txLen = 2;
  switch (STK500_Buffer[STK_TXMSG_START])
    {
	  case STK_CMD_SIGN_ON:
	    {
#ifndef ISAVRISPMKII
          static PROGMEM uint8_t STK500_initstring[] = {8, 'S', 'T', 'K', '5', '0', '0', '_', '2', 0};
#else
          static PROGMEM uint8_t STK500_initstring[] = {10, 'A', 'V', 'R', 'I', 'S', 'P', '_', 'M','K','2', 0};
#endif
          uint8_t *p = &STK500_Buffer[STK_TXMSG_START + 2];
          strcpy_P(p, STK500_initstring);
          STK500_Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
#ifndef ISAVRISPMKII
          STK500_txLen = 11;
#else
          STK500_txLen = 13;
#endif
		  break; 
        }
      case STK_CMD_SET_PARAMETER:
	    {
          STK500_Param.bytes[STK500_Buffer[STK_TXMSG_START + 1] & 0x1f] = STK500_Buffer[STK_TXMSG_START + 2];
		  if (STK500_Buffer[STK_TXMSG_START + 1] == STK_PARAM_SCK_DURATION)
		    {
              switch (STK500_Buffer[STK_TXMSG_START + 2])
                {
#ifndef ISAVRISPMKII //STK500v2
                case 0xfe:
				case 0x4c:
				case 0x3:ISP_Speed = 1;break;
                case 0x2:ISP_Speed = 2;break;
                case 0x1:ISP_Speed = 4;break;
                case 0x0:ISP_Speed = 6;
#else				 //AVRISPmkII
		        case 0xa3:
				case 0x95:
				case 0x3e:ISP_Speed = 1;break;
				case 0x06:ISP_Speed = 2;break;
				case 0x05:ISP_Speed = 3;break;
				case 0x04:ISP_Speed = 4;break;
				case 0x03:ISP_Speed = 5;break;
				case 0x02:ISP_Speed = 6;break;
				case 0x01:
				case 0x00:ISP_Speed = 7;break;
#endif
                }
            } 
          STK500_Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
		  break;
        }
      case STK_CMD_GET_PARAMETER:
	    {
		  if (STK500_Buffer[STK_TXMSG_START + 1] == STK_PARAM_SCK_DURATION)
		    {
              switch (ISP_Speed)
                {
#ifndef ISAVRISPMKII
                case 1:STK500_Param.s.sckDuration = 0x3e;break;
                case 2:
				case 3:STK500_Param.s.sckDuration = 0x2;break;
                case 4:
				case 5:STK500_Param.s.sckDuration = 0x1;break;
                case 6:
				case 7:STK500_Param.s.sckDuration = 0x0;
#else
                case 1:STK500_Param.s.sckDuration = 0xfe;break;
                case 2:STK500_Param.s.sckDuration = 0x06;break;
				case 3:STK500_Param.s.sckDuration = 0x05;break;
                case 4:STK500_Param.s.sckDuration = 0x04;break;
				case 5:STK500_Param.s.sckDuration = 0x03;break;
                case 6:STK500_Param.s.sckDuration = 0x02;break;
				case 7:STK500_Param.s.sckDuration = 0x01;break;
#endif
                }
            } 
          else if (STK500_Buffer[STK_TXMSG_START + 1] == STK_PARAM_VTARGET)
		    {
#if defined(USBASP_COMPATIBLE)||defined(CCCB_COMPATIBLE)
  		  	  STK500_Param.s.vTarget = 50;
#else
			  STK500_Param.s.vTarget = ISP_getsupplyvoltage();
#endif
			}  
          STK500_Buffer[STK_TXMSG_START + 2] = STK500_Param.bytes[STK500_Buffer[STK_TXMSG_START + 1] & 0x1f];
          STK500_Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
          STK500_txLen = 3;
		  break;
        } 
      case STK_CMD_ENTER_PROGMODE_ISP:
	    {
          if (PGM_statuschanged != NULL)
		    PGM_statuschanged(PGM_STATUS_PROGRAMMING);   
          STK500_Status = PGM_STATUS_PROGRAMMING;
		  ISP_connect();
		  if (ISP_enterprogrammingmode() == 0)
            STK500_Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
          else
            STK500_Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_FAILED;
		  break;
		} 
      case STK_CMD_LEAVE_PROGMODE_ISP:
	    {
		  ISP_disconnect();
          STK500_Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
          if (PGM_statuschanged != NULL)
		    PGM_statuschanged(PGM_STATUS_IDLE);   
          STK500_Status = PGM_STATUS_IDLE;
		  break;
		}
      case STK_CMD_RESET_PROTECTION:
	    {
          STK500_Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
		  break;
		}
      case STK_CMD_CHIP_ERASE_ISP:
	    {
		  ISP_erase();
     	  TIMER_delay(((stkChipEraseIsp_t*) &STK500_Buffer[STK_TXMSG_START + 1])->eraseDelay);
          STK500_Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
		  break;
		}
      case STK_CMD_READ_FUSE_ISP:
	  case STK_CMD_READ_LOCK_ISP:
	  case STK_CMD_READ_SIGNATURE_ISP:
	  case STK_CMD_READ_OSCCAL_ISP:
	    {
		  for (i=0;i<4;i++)
            if (i == ((stkReadFuseIsp_t*) &STK500_Buffer[STK_TXMSG_START + 1])->retAddr-1)
		      res = ISP_transmit(((stkReadFuseIsp_t*) &STK500_Buffer[STK_TXMSG_START + 1])->cmd[i]);
		    else
		      ISP_transmit(((stkReadFuseIsp_t*) &STK500_Buffer[STK_TXMSG_START + 1])->cmd[i]);
          STK500_Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
		  STK500_Buffer[STK_TXMSG_START + 2] = res;	 
          STK500_Buffer[STK_TXMSG_START + 3] = STK_STATUS_CMD_OK;
		  STK500_txLen = 4;
		  break;
		}
      case STK_CMD_PROGRAM_LOCK_ISP:
      case STK_CMD_PROGRAM_FUSE_ISP:
	    {
		  for (i=0;i<4;i++)
     		ISP_transmit(((stkProgramFuseIsp_t*) &STK500_Buffer[STK_TXMSG_START + 1])->cmd[i]);
          STK500_Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
          STK500_Buffer[STK_TXMSG_START + 2] = STK_STATUS_CMD_OK;
		  STK500_txLen = 3;
		  break;
		}
	  case STK_CMD_LOAD_ADDRESS:
	    {
          STK500_Address  = STK500_Buffer[STK_TXMSG_START + 1];
          STK500_Address  = (STK500_Address << 8)|STK500_Buffer[STK_TXMSG_START + 2];
          STK500_Address  = (STK500_Address << 8)|STK500_Buffer[STK_TXMSG_START + 3];
          STK500_Address  = (STK500_Address << 8)|STK500_Buffer[STK_TXMSG_START + 4]; 		  
          STK500_Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
          break;
        }
      case STK_CMD_PROGRAM_EEPROM_ISP:
	    Address_as_byte = 1;
      case STK_CMD_PROGRAM_FLASH_ISP:
	    {
          #define progFlashParam ((stkProgramFlashIsp_t*) &STK500_Buffer[STK_TXMSG_START + 1])  
          
		  uint8_t valuePollingMask, rdyPollingMask; 
          uint8_t pollmode;
		  uint16_t startaddress = STK500_Address;
		  res = STK_STATUS_CMD_OK;
          len=  ((int)progFlashParam->numBytes[0])<<8;
          len|= progFlashParam->numBytes[1]; 

          for (i=0;i<len;i++)
		    {
			  if ((i&8)==8)
			    usbPoll();
			  if (!Address_as_byte)
                ISP_transmit(progFlashParam->cmd[0] | ((i & 1) << 3));
              else 
                ISP_transmit(progFlashParam->cmd[0]);
              ISP_transmit(STK500_Address>>8);
              ISP_transmit(STK500_Address);
			  ISP_transmit(progFlashParam->data[i]);
			  if (!Address_as_byte)
      		    {
				  if (i&1)
				    STK500_Address++;
				}
              else  
			    STK500_Address++;
        	  if (progFlashParam->mode & 1) //page mode
			    {
				  if ((i < len-1) || !(progFlashParam->mode & 0x80)) continue;
				  //write page
                  ISP_transmit(progFlashParam->cmd[1]);
                  ISP_transmit(startaddress >> 8);
                  ISP_transmit(startaddress);
                  ISP_transmit(0);
                  valuePollingMask = 0x20;
                  rdyPollingMask = 0x40;
				}
			  else //word mode
			    {
                  valuePollingMask = 4;
                  rdyPollingMask = 8; 
				}
              pollmode = progFlashParam->mode; 
              if (progFlashParam->poll[0] == progFlashParam->data[i])
			    pollmode = 0;
              //poll
#ifdef HASVALUEPOLLING
              if (pollmode & valuePollingMask)
			    { //value polling
				  
//                  TIMER_start(progFlashParam->delay);
         		  tmp = progFlashParam->poll[0];
				  while (tmp == progFlashParam->poll[0])
				    {
                      if (!Address_as_byte)
                        ISP_transmit(progFlashParam->cmd[2] | ((i & 1) << 3));
                      else 
                        ISP_transmit(progFlashParam->cmd[2]);
                      ISP_transmit(STK500_Address >> 8);
                      ISP_transmit(STK500_Address);
                      tmp = ISP_transmit(0);
					  tmp = 0;
                      if(TIMER_overflowed())
					    {
                          res = STK_STATUS_CMD_TOUT;
						  break;
						}
                    }
				}
              else 
#endif
			  if (pollmode & rdyPollingMask)
                { //ready polling
                  TIMER_start((progFlashParam->delay));
                  while(ISP_deviceisbusy())
				    {
#ifndef ISAVRISPMKII //STK500v2
					  usbPoll();
#endif
                      if(TIMER_overflowed())
                        res = STK_STATUS_RDY_BSY_TOUT;
                    }
                  res = STK_STATUS_CMD_OK;
				}
              else
			    { //timed polling
   			      TIMER_start(progFlashParam->delay);
                  while (TIMER_timeout)
				    usbPoll();
				  res = STK_STATUS_CMD_OK;
				}
            }
          STK500_Buffer[STK_TXMSG_START + 1] = res;
		  break;
		} 
      case STK_CMD_READ_EEPROM_ISP: 
	    Address_as_byte = 1;
      case STK_CMD_READ_FLASH_ISP:
	    {
		  len = (((stkReadFlashIsp_t*) &STK500_Buffer[STK_TXMSG_START + 1])->numBytes[0]<<8)+((stkReadFlashIsp_t*) &STK500_Buffer[STK_TXMSG_START + 1])->numBytes[1];
		  tmp = ((stkReadFlashIsp_t*) &STK500_Buffer[STK_TXMSG_START + 1])->cmd;
          for (i=0;i<len;i++)
		    {
#ifndef ISAVRISPMKII //STK500v2
     		  MAIN_critical_tasks(); //keep main tasks alive (wdt,usb)
#endif
              if (!Address_as_byte)
                ISP_transmit(tmp | ((i & 1) << 3));
              else 
                ISP_transmit(tmp);
              ISP_transmit(STK500_Address >> 8);
              ISP_transmit(STK500_Address);
              STK500_Buffer[STK_TXMSG_START + 2 + i] = ISP_transmit(0);
			  if (!Address_as_byte)
      		    {
				  if (i&1)
				    STK500_Address++;
				}
              else  
			    STK500_Address++;
     		  usbPoll(); //keep main tasks alive (wdt,usb)
		    }
          STK500_Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
		  STK500_Buffer[STK_TXMSG_START + 1 + len + 1] = STK_STATUS_CMD_OK;
		  STK500_txLen = len+3;
		  break;
		}
      case STK_CMD_SPI_MULTI:
	    {
          #define progMultiParam ((stkMultiIsp_t*) &STK500_Buffer[STK_TXMSG_START + 1])  
		  uint8_t lentx = progMultiParam->numTx;
		  uint8_t lenrx = progMultiParam->numRx;
		  uint8_t rxstart = progMultiParam->rxStartAddr;
		  uint8_t STK500_rxPos = 1;
		  for (i = 0;i<lentx;i++)
		    {
			  if (i >= rxstart)
			    {
				  STK500_Buffer[STK_TXMSG_START + 1 + STK500_rxPos] = ISP_transmit(progMultiParam->txData[i]);
				  STK500_rxPos++;
				}
              else
			    ISP_transmit(progMultiParam->txData[i]);
			}
		  while (STK500_rxPos < lenrx)
		    {
			  STK500_Buffer[STK_TXMSG_START + 1 + STK500_rxPos] = ISP_transmit(progMultiParam->txData[i]);
			  STK500_rxPos++;
			}
          STK500_Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_OK;
		  STK500_Buffer[STK_TXMSG_START + 1 + lenrx + 1] = STK_STATUS_CMD_OK;
		  STK500_txLen = lenrx+3;
		  break;
		}
      default:
	    {
          STK500_Buffer[STK_TXMSG_START + 1] = STK_STATUS_CMD_FAILED;
		}
	   
	}
  STK500_sendmessage();
}

#ifndef AVRISPMKII
void STK500_byterecived(uint8_t data)
{
  if(STK500_rxPos == 0)
    { 
      if (data == STK_STX)
        STK500_Buffer[STK500_rxPos++] = data;
    }
  else
    {
      if(STK500_rxPos < BUFFER_SIZE)
	    {
          STK500_Buffer[STK500_rxPos++] = data;
          if (STK500_rxPos == 4)
		    {
              STK500_rxLen = (STK500_Buffer[2] << 8)+STK500_Buffer[3];
              STK500_rxLen += 6;
              if(STK500_rxLen > BUFFER_SIZE) //wrong length
			    {
                STK500_rxPos = 0;
				}
            }
		  else if (STK500_rxPos == 5)
		    {
              if(data != STK_TOKEN)
			    {
                STK500_rxPos = 0;
				}
            }
		  else if (STK500_rxPos > 4 && STK500_rxPos == STK500_rxLen)
		    { 
                uint8_t sum = 0;//calculate chksum
                uint8_t *p = STK500_Buffer;
                while(STK500_rxPos)
				  { 
                    sum ^= *p++;
                    STK500_rxPos--;
                  }
                if(sum == 0) //chksum ok
				  { 
                    STK500_processmessage();
                  }
				else //chksum error
 				  {
                    STK500_Buffer[STK_TXMSG_START] = STK_ANSWER_CKSUM_ERROR;
                    STK500_Buffer[STK_TXMSG_START + 1] = STK_ANSWER_CKSUM_ERROR;
					STK500_txLen = 3;
                    STK500_sendmessage();
                  }
            }
        }
	  else
	    { 
          STK500_rxPos = 0;
        }
    }
}

#endif
