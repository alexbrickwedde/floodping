/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2008-12-10
 * Copyright: (c) 2008 by Christian Ulrich
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 *
 * Changes:
 ***********************************************************************************************/

#include <avr/io.h>
#include "jtag.h"

void JTAG_attatch()
{
  JTAG_PORT |= ((1<<JTAG_TDO)|(1<<JTAG_TMS));
  JTAG_PORT &= ~((1<<JTAG_TCK));
  JTAG_DDR |= (1<<JTAG_TMS)|(1<<JTAG_TCK)|(1<<JTAG_TDO);
  JTAG_DDR &= ~(1<<JTAG_TDI);
}

void JTAG_detatch()
{
  JTAG_TAP_STATE = TAP_STATE_UNKNOWN;
  JTAG_DDR &= ~(1<<JTAG_TMS)|(1<<JTAG_TCK)|(1<<JTAG_TDO)|(1<<JTAG_TDI);
  JTAG_PORT &= ~(1<<JTAG_TMS)|(1<<JTAG_TCK)|(1<<JTAG_TDO)|(1<<JTAG_TDI);
}

//Clocks the statemashine one time
void JTAG_tap_state(unsigned char TMS_on)
{
  if (TMS_on)
    JTAG_PORT |= (1<<JTAG_TMS);
  else
    JTAG_PORT &= ~(1<<JTAG_TMS);
  JTAG_PORT |= (1<<JTAG_TCK);
  asm volatile ("NOP");
  JTAG_PORT &= ~(1<<JTAG_TCK);
  asm volatile ("NOP");
}

unsigned char JTAG_TAP_STATE = TAP_STATE_UNKNOWN;

void JTAG_goto_tap_state(unsigned char targetstate)
{
  unsigned char i;
  while (JTAG_TAP_STATE != targetstate)
    {
	  switch (JTAG_TAP_STATE)
	  {
      case TAP_STATE_UNKNOWN:
        {
	      for (i=0;i<5;i++)		//Tab to Test Logic reset
            JTAG_tap_state(1);
          JTAG_TAP_STATE = TAP_STATE_RESET;
	      break;
        }
      case TAP_STATE_RESET:
        {
	      if (targetstate == TAP_STATE_RESET)
            JTAG_tap_state(1);
	      else
		    {
              JTAG_tap_state(0);
              JTAG_TAP_STATE = TAP_STATE_IDLE;
		    }     
   		  break;
	    } 
      case TAP_STATE_IDLE:
	    {
	      if (targetstate == TAP_STATE_IDLE)
            JTAG_tap_state(0);
	      else
		   {
             JTAG_tap_state(1);
             JTAG_TAP_STATE = TAP_STATE_SELECT_DR_SCAN;
		   }     
     	  break;
		} 
//Data Register Scan Chain
      case TAP_STATE_SELECT_DR_SCAN:
  	    {
		  if (targetstate >= TAP_STATE_SELECT_IR_SCAN)
		    {
              JTAG_tap_state(1);
              JTAG_TAP_STATE = TAP_STATE_SELECT_IR_SCAN;
		    }
		  else
		    {
              JTAG_tap_state(0);
              JTAG_TAP_STATE = TAP_STATE_CAPTURE_DR;
		    }     
     	  break;
		} 
      case TAP_STATE_CAPTURE_DR:
	    {
	      if (targetstate >= TAP_STATE_EXIT1_DR)
	   	    {
              JTAG_tap_state(1);
              JTAG_TAP_STATE = TAP_STATE_EXIT1_DR;
			}
		  else
		    {
              JTAG_tap_state(0);
              JTAG_TAP_STATE = TAP_STATE_SHIFT_DR;
		    }     
       	  break;
		} 
      case TAP_STATE_SHIFT_DR:
	    {
	      if (targetstate == TAP_STATE_SHIFT_DR)
            JTAG_tap_state(0);
	      else
	        {
              JTAG_tap_state(1);
              JTAG_TAP_STATE = TAP_STATE_EXIT1_DR;
		    }     
     	  break;
	    } 
      case TAP_STATE_EXIT1_DR:
	    {
	      if (targetstate == TAP_STATE_PAUSE_DR)
	   	    {
              JTAG_tap_state(0);
              JTAG_TAP_STATE = TAP_STATE_PAUSE_DR;
			}
		  else
		    {
              JTAG_tap_state(1);
              JTAG_TAP_STATE = TAP_STATE_UPDATE_DR;
		    }     
     	  break;
		} 
      case TAP_STATE_PAUSE_DR:
	    {
	      if (targetstate == TAP_STATE_PAUSE_DR)
            JTAG_tap_state(0);
	      else
		    {
              JTAG_tap_state(1);
              JTAG_TAP_STATE = TAP_STATE_EXIT2_DR;
		    }     
     	  break;
	    } 
      case TAP_STATE_EXIT2_DR:
	    {
  	      if (targetstate == TAP_STATE_SHIFT_DR)
		    {
              JTAG_tap_state(0);
              JTAG_TAP_STATE = TAP_STATE_SHIFT_DR;
		    }
		  else
		    {
              JTAG_tap_state(1);
              JTAG_TAP_STATE = TAP_STATE_UPDATE_DR;
		    }     
     	  break;
	    } 
      case TAP_STATE_UPDATE_DR:
	    {
	      if (targetstate == TAP_STATE_SELECT_DR_SCAN)
	   	    {
              JTAG_tap_state(1);
              JTAG_TAP_STATE = TAP_STATE_SELECT_DR_SCAN;
		    }
		  else
		    {
              JTAG_tap_state(0);
              JTAG_TAP_STATE = TAP_STATE_IDLE;
		    }     
     	  break;
	    } 
//Instruction Register Scan Chain
      case TAP_STATE_SELECT_IR_SCAN:
  	    {
		  if (targetstate < TAP_STATE_SELECT_IR_SCAN)
		    {
              JTAG_tap_state(1);
              JTAG_TAP_STATE = TAP_STATE_RESET;
		    }
		  else
		    {
              JTAG_tap_state(0);
              JTAG_TAP_STATE = TAP_STATE_CAPTURE_IR;
		    }     
     	  break;
		} 
      case TAP_STATE_CAPTURE_IR:
	    {
	      if (targetstate >= TAP_STATE_EXIT1_IR)
	   	    {
              JTAG_tap_state(1);
              JTAG_TAP_STATE = TAP_STATE_EXIT1_IR;
			}
		  else
		    {
              JTAG_tap_state(0);
              JTAG_TAP_STATE = TAP_STATE_SHIFT_IR;
		    }     
       	  break;
		} 
      case TAP_STATE_SHIFT_IR:
	    {
	      if (targetstate == TAP_STATE_SHIFT_IR)
            JTAG_tap_state(0);
	      else
	        {
              JTAG_tap_state(1);
              JTAG_TAP_STATE = TAP_STATE_EXIT1_IR;
		    }     
     	  break;
	    } 
      case TAP_STATE_EXIT1_IR:
	    {
	      if (targetstate == TAP_STATE_PAUSE_IR)
	   	    {
              JTAG_tap_state(0);
              JTAG_TAP_STATE = TAP_STATE_PAUSE_IR;
			}
		  else
		    {
              JTAG_tap_state(1);
              JTAG_TAP_STATE = TAP_STATE_UPDATE_IR;
		    }     
     	  break;
		} 
      case TAP_STATE_PAUSE_IR:
	    {
	      if (targetstate == TAP_STATE_PAUSE_IR)
            JTAG_tap_state(0);
	      else
		    {
              JTAG_tap_state(1);
              JTAG_TAP_STATE = TAP_STATE_EXIT2_IR;
		    }     
     	  break;
	    } 
      case TAP_STATE_EXIT2_IR:
	    {
  	      if (targetstate == TAP_STATE_SHIFT_IR)
		    {
              JTAG_tap_state(0);
              JTAG_TAP_STATE = TAP_STATE_SHIFT_IR;
		    }
		  else
		    {
              JTAG_tap_state(1);
              JTAG_TAP_STATE = TAP_STATE_UPDATE_IR;
		    }     
     	  break;
	    } 
      case TAP_STATE_UPDATE_IR:
	    {
	      if (targetstate == TAP_STATE_SELECT_IR_SCAN)
	   	    {
              JTAG_tap_state(1);
              JTAG_TAP_STATE = TAP_STATE_SELECT_DR_SCAN;
		    }
		  else
		    {
              JTAG_tap_state(0);
              JTAG_TAP_STATE = TAP_STATE_IDLE;
		    }     
     	  break;
	    } 
      }
    }
}

unsigned char JTAG_shift_bit(unsigned char TDI_on)
{
  JTAG_PORT &= ~(1<<JTAG_TMS);
  if (TDI_on)
    JTAG_PORT |= (1<<JTAG_TDO);
  else
    JTAG_PORT &= ~(1<<JTAG_TDO);
  JTAG_PORT |= (1<<JTAG_TCK);
  asm volatile("NOP");
  JTAG_PORT &= ~(1<<JTAG_TCK);

  if (JTAG_PIN & JTAG_TDI) return 1;
  else return 0;
}

void JTAG_shift_bytes(unsigned char *chain,unsigned int len)
{
  unsigned char i = 0;
  unsigned int bytes_remain = len;

  JTAG_PORT &= ~(1<<JTAG_TMS);

  SPCR = (1 << SPE) | (1 << MSTR) | (1 << DORD);
  SPSR = (1 << SPI2X);
  while(bytes_remain)
	{
      SPDR = chain[i];
      while (!(SPSR & (1 << SPIF)));
      chain[i] = SPDR; 
      i++;
 	  bytes_remain--;
	}
  SPCR &= ~(1 << SPE);
}
