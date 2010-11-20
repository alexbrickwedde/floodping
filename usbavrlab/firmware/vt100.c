/************************************************************************************************
 * Project: generic
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 * Based on code from Martin Thomas 
 * http://www.siwawi.arubi.uni-kl.de/avr_projects
 ***********************************************************************************************/



#include "vt100.h"
#include "usb_uart.h"

/*** Send escape sequence start ***/
static inline void send_esc(void)
{
    UART_putc( 27 );
    UART_putc( '[' );
}

//***************************
// Convert byte to 3 ASCII digits and send
//***************************
void Term_Send_Value_as_Digits( unsigned char value )
{
    unsigned char digit;
    
    digit = '0';
    while( value >= 100 )                // Still larger than 100 ?
    {
        digit++;                         // Increment first digit
        value -= 100;
    }
    
    UART_putc( digit );                  // Send first digit
    
    digit = '0';
    while( value >= 10 )                 // Still larger than 10 ?
    {
        digit++;                         // Increment second digit
        value -= 10;
    }
    
    UART_putc( digit );                  // Send second digit
    
    UART_putc( '0' + value );            // Send third digit
}

//***************************
// Send 'clear screen' sequence
//***************************
void Term_Erase_Screen()
{
    send_esc();                             // Send escape sequence start
    
    UART_putc( '2' );
    UART_putc( 'J' );
}


//***************************
// Set text mode
//***************************
void Term_Set_Display_Attribute_Mode( unsigned char mode )
{
    send_esc();                             // Send escape sequence start
    
    UART_putc( mode );
    UART_putc( 'm' );
}


//***************************
// Set text colour
//***************************
void Term_Set_Display_Colour( unsigned char fg_bg, unsigned char colour )
{
    send_esc();                             // Send escape sequence start
    
    UART_putc( fg_bg );                 // Select foreground/background
    UART_putc( colour );
    UART_putc( 'm' );
}


//***************************
// Set cursor position
//
// Top-left is (1,1)
//***************************
void Term_Set_Cursor_Position( unsigned char row, unsigned char column )
{
    send_esc();                                    // Send escape sequence start
    
    Term_Send_Value_as_Digits( row );              // Convert row byte
    UART_putc( ';' );
    Term_Send_Value_as_Digits( column );           // Convert column byte
    UART_putc( 'H' );
}


void Term_Draw_Window(const char *name,uint8_t x,uint8_t y,uint8_t width,uint8_t height)
{
  uint8_t ix,iy;
  Term_Set_Cursor_Position(y,x);
  UART_putc(218);
  for (ix=0;ix<width;ix++)
    UART_putc(196);
  UART_putc(191);
  for (iy=1;iy<=height;iy++) 
    {
      Term_Set_Cursor_Position(y+iy,x);
      UART_putc(179);
      for (ix=0;ix<width;ix++)
        UART_putc(0x20);
      UART_putc(179);
	}
  Term_Set_Cursor_Position(y+1,x+1);
  UART_puts_P(name);
  Term_Set_Cursor_Position(y+2,x);
  UART_putc(195);
  for (ix=0;ix<width;ix++)
    UART_putc(196);
  UART_putc(180);
  Term_Set_Cursor_Position(y+height+1,x);
  UART_putc(192);
  for (ix=0;ix<width;ix++)
    UART_putc(196);
  UART_putc(217);
}
