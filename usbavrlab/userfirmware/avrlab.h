/************************************************************************************************
 * Project: USB AVR-Lab
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-09-24
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2
 *
 * Changes:
 ***********************************************************************************************/

//must be called to init AVR-USB Lab
//muss aufgerufen werden um das AVR-USB Lab zu initialisieren
void avrlab_init(void);
//must be called at least every 40 ms
//muss mindestens alle 40 ms aufgerufen werden
void avrlab_poll(void);

//To use the LED´s on the avr-usb lab
//Um die LED´s auf dem AVR-USB Lab anzusteuern

//mode:
//LED_ON		led is on
//LED_OFF   	led is off
//LED_FLASH 	led flashes in frequency
//LED_FLASH_NEG led flashes inverted

//frequency: frequency for led flashing

void SetLed(unsigned char led,unsigned char mode,unsigned char frequency);
