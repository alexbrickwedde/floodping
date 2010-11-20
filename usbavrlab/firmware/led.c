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
#include <avr/interrupt.h>
#include "led.h"
#include "main.h"

uint8_t LED_counter;

void LED_init(void)
{
  uint8_t i;
  for (i=0;i<led_count;i++)
    LED_DDR |= (1<<leds[i].pin);

  LED_counter = (F_CPU/100000);
  LED_poll();
}

void LED_poll(void)
{
  if (LED_counter < (F_CPU/100000))
    {
	  LED_counter++;
	  return;
	}
  LED_counter = 0;
  uint8_t i;
  for (i=0;i<led_count;i++)
    {
	  if (leds[i].frequency != LED_OFF)
	    {
		  if (leds[i].frequency == LED_ON) 
		    LED_PORT &= ~(1<<leds[i].pin);
		  else if (leds[i].frequency == LED_FLASH_NEG)
		    {
   		      LED_PORT |= (1<<leds[i].pin);
			  if (leds[i].counter == 0)
			    {
     		      LED_PORT &= ~(1<<leds[i].pin);
				  leds[i].frequency = LED_ON;
				}
              else leds[i].counter--;
			} 
		  else if (leds[i].frequency == LED_FLASH)
		    {
   		      LED_PORT &= ~(1<<leds[i].pin);
			  if (leds[i].counter == 0)
			    {
     		      LED_PORT |= (1<<leds[i].pin);
				  leds[i].frequency = LED_OFF;
				}
              else leds[i].counter--;
			} 
          else
		    {
			  if (leds[i].counter == 0)
			    {
				  leds[i].counter = leds[i].frequency;
				  if (leds[i].status == LED_OFF)
				    {
					  leds[i].status = LED_ON;
            	      LED_PORT &= ~(1<<leds[i].pin);
					}
                  else
				    {
					  leds[i].status = LED_OFF;
            	      LED_PORT |= (1<<leds[i].pin);
					}
				}
			  else leds[i].counter--;
			} 
		}
      else
 	    LED_PORT |= (1<<leds[i].pin);
	}
}

