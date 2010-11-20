/************************************************************************************************
 * Project: generic
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2
 ***********************************************************************************************/

#ifndef __vt100_h_included__
#define __vt100_h_included__

#include <avr/io.h>

#define MODE_NONE         '0'
#define MODE_BOLD         '1'
#define MODE_DIM          '2'
#define MODE_UNDERLINE    '4'
#define MODE_BLINK        '5'
#define MODE_REVERSED     '7'
#define MODE_CONCEALED    '8'

#define COL_FOREGROUND    '3'
#define COL_BACKGROUND    '4'

#define COL_BLACK         '0'
#define COL_RED           '1'
#define COL_GREEN         '2'
#define COL_YELLOW        '3'
#define COL_BLUE          '4'
#define COL_MAGENTA       '5'
#define COL_CYAN          '6'
#define COL_WHITE         '7'

void Term_Erase_Screen(void);
void Term_Send_Value_as_Digits( unsigned char value );
void Term_Set_Cursor_Position( unsigned char row, unsigned char column );
void Term_Set_Display_Attribute_Mode( unsigned char mode );
void Term_Set_Display_Colour( unsigned char fg_bg, unsigned char colour );
void Term_Draw_Window(const char *name,uint8_t x,uint8_t y,uint8_t width,uint8_t height);


#endif
