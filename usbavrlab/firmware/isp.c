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

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "isp.h"

uint8_t ISP_Speed = 1;
uint8_t ISP_Status = 0;

#define ISP_DIVIDER (uint8_t)(17 * 1024 / ((33 + 22) * 25.6)) 

uint8_t ISP_getsupplyvoltage(void)
{
  uint16_t supply;
  ISP_SUPPLY_PORT &= ~(1<<ISP_SUPPLY);

  ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);    // Frequenzvorteiler 
                               // setzen auf 8 (1) und ADC aktivieren (1)
  ADMUX = 1;                      // Kanal waehlen
  ADMUX |= (1<<REFS1) | (1<<REFS0); // interne Referenzspannung nutzen 
  ADCSRA |= (1<<ADSC);              // eine ADC-Wandlung 
  while ( ADCSRA & (1<<ADSC));
  supply = ADCW;
  ADCSRA |= (1<<ADSC);            // eine Wandlung "single conversion"
  while ( ADCSRA & (1<<ADSC) );
  supply = ADCW;
  return (supply + ISP_DIVIDER/2) / ISP_DIVIDER;
}

void ISP_checkstatus(void)
{
  uint8_t newstatus;

  if (  (ISP_getsupplyvoltage() > 27) )
    newstatus = ISP_STATUS_CONNECTED_OK;
  else if (  (ISP_getsupplyvoltage() > 20) && (ISP_getsupplyvoltage() < 27) )
    newstatus = ISP_STATUS_CONNECTED_NOT_OK;
  else
    newstatus = ISP_STATUS_DISCONNECTED;
  if (newstatus != ISP_Status)	  
    {
	  if (ISP_statuschanged != NULL) ISP_statuschanged(newstatus);
      ISP_Status = newstatus;
	}
}

void ISP_pulsesck(void)
{
  ISP_OUT |= (1 << ISP_SCK);     /* SCK high */
  _delay_ms(0.07);
  ISP_OUT &= ~(1 << ISP_SCK);    /* SCK low */
  _delay_ms(0.07); 
}

void ISP_spienable(uint8_t speed) 
{
  switch (speed)
    {
	  case 2:/* enable SPI, master, 93,75 kHz SCK */
	    {
          SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1)| (1 << SPR0);
          SPSR = 0;
	      break;
        }  
      case 3:
	    {
          /* enable SPI, master, 187,5Hz SCK */
          SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1);
          SPSR = 0;
		  break;
		}
      case 4:
	    {
          /* enable SPI, master, 375kHz SCK */
          SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1);
          SPSR = (1 << SPI2X);
		  break;
		}		 
      case 5:
	    {
          /* enable SPI, master, 750kHz SCK */
          SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
          SPSR = 0;
		  break;
		}
	  case 6:
	    {
          /* enable SPI, master, 1,5 MHz SCK */
          SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
          SPSR = (1 << SPI2X);
		  break;
		}			 
	  case 7:
	    {
          /* enable SPI, master, 3 MHz SCK */
          SPCR = (1 << SPE) | (1 << MSTR);
          SPSR = 0;
		  break;
		}			 
    }
}

#define ISP_spidisable() SPCR = 0

void ISP_connect() 
{
  /* all ISP pins are inputs before */
  /* now set output pins */
  ISP_DDR |= (1 << ISP_RST) | (1 << ISP_SCK) | (1 << ISP_MOSI);
  ISP_OUT |= (1 << ISP_SCK);   /* SCK high */
  TIMER_delay(5); //5ms wait
  /* reset device */
  ISP_OUT &= ~(1 << ISP_RST);   /* RST low */
  ISP_OUT &= ~(1 << ISP_SCK);   /* SCK low */
  /* positive reset pulse > 2 SCK (target) */
  _delay_ms(0.17); 
  ISP_OUT |= (1 << ISP_RST);    /* RST high */
  _delay_ms(0.17);                 
  ISP_OUT &= ~(1 << ISP_RST);   /* RST low */
  ISP_spienable(ISP_Speed);
}

void ISP_disconnect() 
{
  ISP_DDR &= ~((1 << ISP_RST) | (1 << ISP_SCK) | (1 << ISP_MOSI));
  ISP_OUT &= ~((1 << ISP_RST) | (1 << ISP_SCK) | (1 << ISP_MOSI));
  ISP_spidisable();
}

uint8_t ISP_transmit(uint8_t send_byte) 
{
  uint8_t rec_byte = 0;
  uint8_t i;
  
  if (ISP_Speed == 1)
    {
      for (i = 0; i < 8; i++) 
        {
          /* set MSB to MOSI-pin */
          if ((send_byte & 0x80) != 0) 
            ISP_OUT |= (1 << ISP_MOSI);  /* MOSI high */
          else
            ISP_OUT &= ~(1 << ISP_MOSI); /* MOSI low */
          /* shift to next bit */
          send_byte  = send_byte << 1;
          /* receive data */
          rec_byte = rec_byte << 1;
          if ((ISP_IN & (1 << ISP_MISO)) != 0) 
            rec_byte++;
          /* pulse SCK */
		  ISP_pulsesck();
        }
      return rec_byte;
    }
  else if (ISP_Speed == 0) return 1;
  else
    {
      SPDR = send_byte;
      while (!(SPSR & (1 << SPIF)));
      return SPDR;
	}
}

uint8_t ISP_enterprogrammingmode() 
{
  uint8_t check;
  uint8_t count = 128;

  while (count--) 
    {
      ISP_transmit(0xAC);
      ISP_transmit(0x53);
      check = ISP_transmit(0);
      ISP_transmit(0);
      if (check == 0x53)
        return 0;
      ISP_spidisable();
      ISP_pulsesck();
      ISP_spienable(ISP_Speed);
    }
  return 1;  /* error: device dosn't answer */ 
}

void ISP_erase()
{
  ISP_transmit(0xAC);
  ISP_transmit(0x80);
  ISP_transmit(0x00);
  ISP_transmit(0x00);
}

uint8_t ISP_deviceisbusy()
{
  ISP_transmit(0xf0);
  ISP_transmit(0x0);
  ISP_transmit(0x0);
  return ISP_transmit(0x0) & 1;
}
