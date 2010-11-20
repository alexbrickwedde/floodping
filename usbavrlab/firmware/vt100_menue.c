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

#include "config.h"

#ifdef HASMENUE  //if not included menue.h dont compile this

#include <stdio.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "menue.h"
#include "vt100.h"
#include "usb_uart.h"

uint8_t MENUE_entry,MENUE_back;
const char return_str[] PROGMEM = "return";

unsigned int strlen_P (const prog_char *str)
 {
    unsigned int len = 0;
 
    while (1)
    {
       char c = (char) pgm_read_byte (str);
       if ('\0' == c)
          return len;
       len++;
       str++; 
    }
 }

int MENUE_next_entry(int entry)
{
  int n_entry;
  n_entry = entry+1;
  while ((n_entry < MENUE_size) && (pgm_read_byte(&menue[n_entry].level) > pgm_read_byte(&menue[entry].level)))
    n_entry++;
  if ((n_entry < MENUE_size)  && (pgm_read_byte(&menue[n_entry].level) == pgm_read_byte(&menue[entry].level)))
    return n_entry;
  else
    return -1;
}
int MENUE_prev_entry(int entry)
{
  int p_entry;
  p_entry = entry-1;
  while ((p_entry > 0) && (pgm_read_byte(&menue[p_entry].level) > pgm_read_byte(&menue[entry].level)))
    p_entry--;
  if ((p_entry > 0) && (pgm_read_byte(&menue[p_entry].level) == pgm_read_byte(&menue[entry].level)))
    return p_entry;
  else
    return -1;
}

void MENUE_update(void)
{
  unsigned char i,a;
  unsigned char arow;
  unsigned char level_width = 0;
  
  arow = 13;
  i = MENUE_entry;
  while (pgm_read_byte(&menue[i].level) >= pgm_read_byte(&menue[MENUE_entry].level)) i--;
  if (strlen_P(menue[i].name) > level_width)
    level_width = strlen_P(menue[i].name);
  a = i;
  i++;
  while ((i <= MENUE_size) && (pgm_read_byte(&menue[i].level) >= pgm_read_byte(&menue[MENUE_entry].level)))
    {
      if (pgm_read_byte(&menue[i].level) == pgm_read_byte(&menue[MENUE_entry].level))
        {
          arow--;
          if (strlen_P(menue[i].name) > level_width)
		    level_width = strlen_P(menue[i].name);
        }
	  i++; 
    }
  Term_Set_Display_Attribute_Mode(MODE_NONE);
  Term_Erase_Screen();
  Term_Set_Display_Colour(COL_BACKGROUND,COL_BLUE);
  if (pgm_read_byte(&menue[a+1].level) > 1)
    arow--;
  Term_Draw_Window(menue[a].name,39-(level_width/2),arow,(level_width)+2,(13-arow)+2);
  i=a+1;
  arow += 3;
  if (pgm_read_byte(&menue[i].level) > 1)
    {
      Term_Set_Cursor_Position(arow,40-(level_width/2));
	  if (MENUE_back)
        Term_Set_Display_Attribute_Mode(MODE_REVERSED);
	  UART_puts_P(return_str);
	  if (MENUE_back)
	    {
          Term_Set_Display_Attribute_Mode(MODE_NONE);
          Term_Set_Display_Colour(COL_BACKGROUND,COL_BLUE);
		}
      arow++; 
	}
  while ((i <= MENUE_size) && (pgm_read_byte(&menue[i].level) >= pgm_read_byte(&menue[MENUE_entry].level)))
    {
	  if(pgm_read_byte(&menue[i].level) == pgm_read_byte(&menue[MENUE_entry].level)) 
	    {
          Term_Set_Cursor_Position(arow,40-(level_width/2));
     	  if ((i==MENUE_entry) && (MENUE_back==0))
            Term_Set_Display_Attribute_Mode(MODE_REVERSED);
		  UART_puts_P(menue[i].name);
     	  if ((i==MENUE_entry) && (MENUE_back==0))
		    {
              Term_Set_Display_Attribute_Mode(MODE_NONE);
              Term_Set_Display_Colour(COL_BACKGROUND,COL_BLUE);
			}
	      arow++;
	    }
      i++;
    }
}

void MENUE_nofunction(void)
{
  Term_Set_Display_Attribute_Mode(MODE_NONE);
  Term_Erase_Screen();
  Term_Set_Cursor_Position(14,35);
  UART_puts("no function !");
}

void MENUE_clrscr(void)
{
  Term_Set_Display_Attribute_Mode(MODE_NONE);
  Term_Erase_Screen();
}

void MENUE_prevlevel(void)
{
  int tmp_entry;
  MENUE_back = 0;
  tmp_entry = MENUE_entry;
  while ((tmp_entry > 1) && (pgm_read_byte(&menue[MENUE_entry].level)-1 != pgm_read_byte(&menue[tmp_entry].level)))
    tmp_entry--;
  MENUE_entry = tmp_entry;
  MENUE_update();
}

void MENUE_show(int can_exit)
{
  MENUE_update(); 
}

void MENUE_task(unsigned char key)
{
  int tmp_entry;
  switch (MENUE_is_key(key))
    {
      case KEY_back:
	    {
	      if (MENUE_prev_entry(MENUE_entry) != -1)
	  	    {
			  MENUE_entry = MENUE_prev_entry(MENUE_entry);
			  MENUE_update();
			}
		  else if (pgm_read_byte(&menue[MENUE_entry].level) > 1)
		    {
		      MENUE_back = 1;
		      MENUE_update();
		    }   
 	      break;
	    }
      case KEY_next:
	    {
	      if (MENUE_back == 1)
	  	    {
		      MENUE_back = 0;
              MENUE_update();
		    }
          else
  		    if (MENUE_next_entry(MENUE_entry) != -1)
		      {
		        MENUE_entry = MENUE_next_entry(MENUE_entry);
			    MENUE_update();
			  } 
 			break;
		}
      case KEY_ok:
	    {
	      if (MENUE_back == 1)
	        {
              MENUE_prevlevel();
			}
          else 
		    {
   		      if (pgm_read_byte(&menue[MENUE_entry+1].level) == pgm_read_byte(&menue[MENUE_entry].level)+1)
			    {
	   		      MENUE_entry++;
			      MENUE_update();
                }
              else
			    {
                  void (*func)(void);
				  func = (void(*)(void)) pgm_read_word (&menue[MENUE_entry].func);
			      if ((*func) == NULL)
			        {
					  MENUE_nofunction();
					  for (tmp_entry=0;tmp_entry<30;tmp_entry++)
					    {
				          _delay_ms(100);
						}
                      MENUE_update();
   				    }
                  else
				    {
					  MENUE_clrscr();
        		      (*func)();
				      MENUE_update();
					}
			    }
            }
          break;
        }   
	}
}

void MENUE_init(void)
{
  MENUE_entry = 1;
  MENUE_back = 0;
}

unsigned char keyindex = 0;

int MENUE_is_key(unsigned char key)
{
  if (key == 0xD)
    {
	  keyindex = 0;
      return KEY_ok;
	}
  else if ((keyindex == 0) && (key == 27)) keyindex++;
  else if ((keyindex == 1) && (key == '[')) keyindex++;
  else if ((keyindex == 2) && (key == 'A'))
    {
	  keyindex = 0;
      return KEY_back;
	}
  else if ((keyindex == 2) && (key == 'B'))
    {
	  keyindex = 0;
      return KEY_next;
    }
  else keyindex = 0;
  return 0;
}

#endif
