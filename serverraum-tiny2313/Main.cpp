/*
 * Main.cpp
 *
 *  Created on: 25.09.2010
 *      Author: root
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#ifndef cbi
#define cbi(sfr, bit)     (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit)     (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define LED_AN(LED)     (PORTD |=  (1<<(LED)))
#define LED_AUS(LED)    (PORTD &= ~(1<<(LED)))
#define LED_TOGGLE(LED) (PORTD ^=  (1<<(LED)))
#define LED1            PD5
#define LED2            PD3


#include "Main.h"

Main::Main() {
}

Main::~Main() {
}

void Main::run() {
    DDRD |= (1 << LED1) | (1 << LED2);

    while(1)
    {
        LED_TOGGLE(LED2);
        LED_AN(LED1);



        LED_AUS(LED1);
    }
}


int main()
{
	Main x;
	x.run();
}
