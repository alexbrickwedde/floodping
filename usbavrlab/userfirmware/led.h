/************************************************************************************************
 * Project: generic
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2
 ***********************************************************************************************/

#ifndef __led_h_included__
#define __led_h_included__

#include <stdint.h>

#define LED_ON 			0xff
#define LED_OFF 		0x0
#define LED_FLASH 		0x1
#define LED_FLASH_NEG 	0x2

typedef struct led
  {
    const uint8_t pin;
	uint8_t frequency;
	uint8_t counter;
	uint8_t status;
  } led_t;

extern led_t leds[];
extern const uint8_t led_count;

void LED_init(void);
void LED_poll(void);

#endif
