//------------------------------------------------------------------------------
//                                  _            _     
//                                 | |          | |    
//      ___ _ __ ___  ___ _   _ ___| |_ ___  ___| |__  
//     / _ \ '_ ` _ \/ __| | | / __| __/ _ \/ __| '_ \. 
//    |  __/ | | | | \__ \ |_| \__ \ ||  __/ (__| | | |
//     \___|_| |_| |_|___/\__, |___/\__\___|\___|_| |_|
//                         __/ |                       
//                        |___/    Engineering
//
// Filename:    main.c
// Description: LED-Paint
//				
//
// Copyright (c) Martin Steppuhn (www.emsystech.de)
//
// Nur f�r den privaten Gebrauch / NON-COMMERCIAL USE ONLY
//
// Die Nutzung (auch auszugsweise) ist f�r den privaten und nichtkommerziellen 
// Gebrauch erlaubt. Eine Ver�ffentlichung und Weiterverwendung des Quellcodes 
// ist m�glich wenn diese Nutzungsbedingungen incl. Copyright beiliegen
// und die Quelle verlinkt ist. (www.emsystech.de)
//
// Bei kommerziellen Absichten nehmen Sie bitte Kontakt mit uns auf 
// (info@emsystech.de)
//
// Keine Gew�hr auf Fehlerfreiheit, Vollst�ndigkeit oder Funktion. Benutzung 
// auf eigene Gefahr. Es wird keinerlei Haftung f�r direkte oder indirekte 
// Personen- oder Sachsch�den �bernommen.
//              
// Author:      Martin Steppuhn
// History:     18.12.2009 Initial version
//------------------------------------------------------------------------------

/**** Includes ****************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "std_c.h"
#include "uart.h"

/**** Preprocessing directives (#define) **************************************/

//=== Portpins ===
#define		DATA_SET		PORTB |=  (1<<4)
#define		DATA_CLR		PORTB &= ~(1<<4)

#define		CLK_SET		PORTB |=  (1<<3)
#define		CLK_CLR		PORTB &= ~(1<<3)

#define		STROBE_SET	PORTB |=  (1<<2)
#define		STROBE_CLR	PORTB &= ~(1<<2)

#define		BUTTON			(!(PIND & (1<<2)))

//=== Pixels ===

#define ROW_0 0x01
#define ROW_1 0x02
#define ROW_2 0x04
#define ROW_3 0x08
#define ROW_4 0x10
#define ROW_5 0x20
#define ROW_6 0x40
#define ROW_7 0x80
#define ROW_8 0x100
#define ROW_9 0x200

#define		CLEAR_ALL	led[0]=0; led[1]=0; led[2]=0; led[3]=0;	led[4]=0; led[5]=0; led[6]=0; led[7]=0; led[8]=0;	led[9]=0; led[10]=0; led[11]=0

#define		WORD_ES_IST			led[0]|=ROW_0; led[1]|=ROW_0; led[4]|=ROW_0; led[5]|=ROW_0; led[6]|=ROW_0
#define		WORD_ZEHN			led[8]|=ROW_0; led[9]|=ROW_0; led[10]|=ROW_0; led[11]|=ROW_0

#define		WORD_FUENF			led[1]|=ROW_1; led[2]|=ROW_1; led[3]|=ROW_1; led[4]|=ROW_1
#define		WORD_VOR_1			led[6]|=ROW_1; led[7]|=ROW_1; led[8]|=ROW_1

#define		WORD_VIERTEL		led[5]|=ROW_2; led[6]|=ROW_2; led[7]|=ROW_2; led[8]|=ROW_2; led[9]|=ROW_2; led[10]|=ROW_2; led[11]|=ROW_2

#define		WORD_NACH			led[0]|=ROW_3; led[1]|=ROW_3; led[2]|=ROW_3; led[3]|=ROW_3
#define		WORD_VOR_2			led[4]|=ROW_3; led[5]|=ROW_3; led[6]|=ROW_3
#define		WORD_HALB			led[8]|=ROW_3; led[9]|=ROW_3; led[10]|=ROW_3; led[11]|=ROW_3

#define		WORD_PLUS1			led[0]|=ROW_9; led[1]|=ROW_9
#define		WORD_PLUS2			led[3]|=ROW_9; led[4]|=ROW_9
#define		WORD_PLUS3			led[6]|=ROW_9; led[7]|=ROW_9
#define		WORD_PLUS4			led[9]|=ROW_9; led[10]|=ROW_9

#define		WORD_5				led[0]|=ROW_4; led[1]|=ROW_4; led[2]|=ROW_4; led[3]|=ROW_4
#define		WORD_2				led[6]|=ROW_4; led[7]|=ROW_4; led[8]|=ROW_4; led[9]|=ROW_4
#define		WORD_1				led[8]|=ROW_4; led[9]|=ROW_4; led[10]|=ROW_4

#define		WORD_7				led[0]|=ROW_5; led[1]|=ROW_5; led[2]|=ROW_5; led[3]|=ROW_5; led[4]|=ROW_5; led[5]|=ROW_5
#define		WORD_6				led[7]|=ROW_5; led[8]|=ROW_5; led[9]|=ROW_5; led[10]|=ROW_5; led[11]|=ROW_5

#define		WORD_10				led[0]|=ROW_6; led[1]|=ROW_6; led[2]|=ROW_6; led[3]|=ROW_6
#define		WORD_9 				led[3]|=ROW_6; led[4]|=ROW_6; led[5]|=ROW_6; led[6]|=ROW_6
#define		WORD_4				led[8]|=ROW_6; led[9]|=ROW_6; led[10]|=ROW_6; led[11]|=ROW_6

#define		WORD_3				led[0]|=ROW_7; led[1]|=ROW_7; led[2]|=ROW_7; led[3]|=ROW_7
#define		WORD_11				led[4]|=ROW_7; led[5]|=ROW_7; led[6]|=ROW_7
#define		WORD_8				led[8]|=ROW_7; led[9]|=ROW_7; led[10]|=ROW_7; led[11]|=ROW_7

#define		WORD_12				led[1]|=ROW_8; led[2]|=ROW_8; led[3]|=ROW_8; led[4]|=ROW_8; led[5]|=ROW_8
#define		WORD_UHR			led[9]|=ROW_8; led[10]|=ROW_8; led[11]|=ROW_8

#define		PIC_FRAME			led[0] = 0x3FF; led[1] = 0x201;	led[2]=0x201; led[3]=0x201; led[4]=0x201;	led[5]=0x201; led[6]=0x201; led[7]=0x201; led[8]=0x201; led[9]=0x201; led[10]=0x201; led[11]=0x3FF

/**** Type definitions (typedef) **********************************************/

/**** Global constants ********************************************************/

/**** Global variables ********************************************************/

/**** Local constants  ********************************************************/

const uint8 font[40] = // Digits
		{ 0xFE, 0x82, 0x82, 0xFE, // 0
				0x08, 0x04, 0xFE, 0x00, // 1
				0xC4, 0xA2, 0x92, 0x8C, // 2
				0x82, 0x92, 0x92, 0x7C, // 3
				0x1E, 0x10, 0xF8, 0x10, // 4
				0x9E, 0x92, 0x92, 0x62, // 5
				0x78, 0x94, 0x92, 0x60, // 6
				0x02, 0xF2, 0x0A, 0x06, // 7
				0xFE, 0x92, 0x92, 0xFE, // 8
				0x9E, 0x92, 0x92, 0xFE // 9
		};

/**** Local variables *********************************************************/

uint8 c;
uint16 led[12];
uint8 col_cnt;
uint16 col;
uint8 button_mem;
uint8 hour, minute, second;
uint8 time_setup_cnt0;
uint8 time_setup_cnt1;
uint16 loop_cnt;
uint8 sec_flag, key_flag;

enum {
	Idle, StartHour, InputHour, StartMinute, InputMinute
} e_SetupState;

/**** Local function prototypes ***********************************************/

//------------------------------------------------------------------------------
// Name:      dram_time
// Function:  Zeit entsprechend darstellen
//            
// Parameter: 
// Return:    
//------------------------------------------------------------------------------
void draw_time(void) {
	uint8 i, h;

	if (e_SetupState == InputHour || e_SetupState == StartHour) {
		i = (hour / 10) * 4;
		led[0] = font[i];
		led[1] = font[i + 1];
		led[2] = font[i + 2];
		led[3] = font[i + 3];
		led[4] = 0;
		i = (hour % 10) * 4;
		led[5] = font[i];
		led[6] = font[i + 1];
		led[7] = font[i + 2];
		led[8] = font[i + 3];
		led[9] = 0;

		if (second & 1) {
			led[10] = 0x44;
			led[11] = 0;
		} else {
			led[10] = 0;
			led[11] = 0x44;
		}
	} else if (e_SetupState == InputMinute || e_SetupState == StartMinute) {
		if (second & 1) {
			led[0] = 0x44;
			led[1] = 0;
		} else {
			led[0] = 0;
			led[1] = 0x44;
		}
		led[2] = 0;
		i = (minute / 10) * 4;
		led[3] = font[i];
		led[4] = font[i + 1];
		led[5] = font[i + 2];
		led[6] = font[i + 3];
		led[7] = 0;
		i = (minute % 10) * 4;
		led[8] = font[i];
		led[9] = font[i + 1];
		led[10] = font[i + 2];
		led[11] = font[i + 3];
	} else {
		CLEAR_ALL;
		WORD_ES_IST;
		WORD_UHR;

		h = 0;
		if (minute < 5) {
			h = hour;
		} else if (minute < 10) {
			WORD_FUENF;
			WORD_NACH;
			h = hour;
		} else if (minute < 15) {
			WORD_ZEHN;
			WORD_NACH;
			h = hour;
		} else if (minute < 20) {
			WORD_VIERTEL;
			WORD_NACH;
			h = hour;
		} else if (minute < 25) {
			WORD_ZEHN;
			WORD_VOR_1;
			WORD_HALB;
			h = hour + 1;
		} else if (minute < 30) {
			WORD_FUENF;
			WORD_VOR_1;
			WORD_HALB;
			h = hour + 1;
		} else if (minute < 35) {
			WORD_HALB;
			h = hour + 1;
		} else if (minute < 40) {
			WORD_FUENF;
			WORD_NACH;
			WORD_HALB;
			h = hour + 1;
		} else if (minute < 45) {
			WORD_ZEHN;
			WORD_NACH;
			WORD_HALB;
			h = hour + 1;
		} else if (minute < 50) {
			WORD_VIERTEL;
			WORD_VOR_2;
			h = hour + 1;
		} else if (minute < 55) {
			WORD_ZEHN;
			WORD_VOR_1;
			h = hour + 1;
		} else if (minute < 60) {
			WORD_FUENF;
			WORD_VOR_1;
			h = hour + 1;
		}

		switch (minute % 5) {
		case 1:
			WORD_PLUS1
			;
			break;
		case 2:
			WORD_PLUS2
			;
			break;
		case 3:
			WORD_PLUS3
			;
			break;
		case 4:
			WORD_PLUS4
			;
			break;
		}

		if (h == 0) {
			WORD_12
			;
		} else if (h == 1) {
			WORD_1
			;
		} else if (h == 2) {
			WORD_2
			;
		} else if (h == 3) {
			WORD_3
			;
		} else if (h == 4) {
			WORD_4
			;
		} else if (h == 5) {
			WORD_5
			;
		} else if (h == 6) {
			WORD_6
			;
		} else if (h == 7) {
			WORD_7
			;
		} else if (h == 8) {
			WORD_8
			;
		} else if (h == 9) {
			WORD_9
			;
		} else if (h == 10) {
			WORD_10
			;
		} else if (h == 11) {
			WORD_11
			;
		} else if (h == 12) {
			WORD_12
			;
		}
	}
}

//------------------------------------------------------------------------------
//		MAIN
//------------------------------------------------------------------------------
int main(void) {
	DDRC = 0x0F;
	DDRD = 0xF0;
	DDRB = 0x03 + (1 << 2) + (1 << 3) + (1 << 4);
	PORTD |= (1 << 2); // f�r Pullup
	SFIOR &= (1 << PUD);

	// Timer 2 mit externem 32kHz Quarz betreiben
	ASSR |= (1 << AS2);
	TCCR2 = (1 << CS22) + (1 << CS20); // /128 f�r 1Hz Int

	// Timer 1 f�r LED INT mit ca. 1,2kHz 		
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) + (1 << CS10);
	OCR1A = 6667;

	// Timer Interrupts

	TIMSK = (1 << OCIE1A) + (1 << TOIE2); // set interrupt mask

	uart_init();
	uart_puts_p(
			"\r\nWordClock V1.0.0, Dez.2009 Martin Steppuhn (www.emsystech.de)\r\n");

	hour = 0;
	minute = 0;
	second = 0;

	sei();
	// Interrupt ein

	while (1) {
		if (sec_flag) //=== 1 Sekunde ===
		{
			sec_flag = false;
			if (BUTTON) {
				time_setup_cnt1++;
				if (time_setup_cnt1 > 3) {
					switch (e_SetupState) {
					case Idle:
						e_SetupState = StartHour;
						break;
					case InputHour:
						e_SetupState = StartMinute;
						break;
					case InputMinute:
						e_SetupState = Idle;
						break;
					case StartHour:
					case StartMinute:
						break;
					}
				}
			} else {
				time_setup_cnt0++;
				if (time_setup_cnt0 > 5) {
					e_SetupState = Idle;
				}
			}
			draw_time();
		}

		if (key_flag) //=== 10ms ===
		{
			key_flag = false;
			if (!BUTTON && button_mem) // falling Edge
					{
				button_mem = false;

				switch (e_SetupState) {
				case Idle:
					break;
				case StartHour:
					e_SetupState = InputHour;
					break;
				case StartMinute:
					e_SetupState = InputMinute;
					break;
				case InputHour:
					hour = (hour < 11) ? hour + 1 : 0;
					break;
				case InputMinute:
					minute = (minute < 59) ? minute + 1 : 0;
					break;
				}

			}
			if (BUTTON) {
				button_mem = true;
				time_setup_cnt0 = 0;
			} else {
				time_setup_cnt1 = 0;
			}
			draw_time();
		}

		// if(uart_kbhit())	{	c = uart_getc();	uart_putc(c);	}
	}
}

int volatile correction = 0;

//------------------------------------------------------------------------------
// Name:      TIMER2_OVF_vect
// Function:  TIMER2 Overflow mit 1Hz (32kHz Uhrenquarz /128 /256
//            
// Parameter: 
// Return:    
//------------------------------------------------------------------------------
ISR(TIMER2_OVF_vect) {
	correction++;
	if(correction > 10000)
	{
		correction = 0;
		second++;
	}
	second++;
	if (second > 59) {
		second = 0;
		minute++;
		if (minute > 59) {
			minute = 0;
			hour++;
			if (hour > 11)
				hour = 0;
		}
	}
	sec_flag = true;
}

//------------------------------------------------------------------------------
// Name:      TIMER1_COMPA_vect
// Function:  LED-Matrix Refresh mit 1,2kHz -> 100Hz Bildwiderholrate
//            
// Parameter: 
// Return:    
//------------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect) {
	col_cnt++;
	if (col_cnt > 11) {
		key_flag = true; // zum sampeln/entprellen der Taste
		col_cnt = 0;
		DATA_CLR;
	} else {
		DATA_SET;
	}
	CLK_SET;
	CLK_CLR;

	PORTC &= ~0x0F;
	PORTD &= ~0xF0;
	PORTB &= ~0x03;

	STROBE_SET;
	STROBE_CLR;

	col = led[col_cnt];

	PORTC |= col & 0x0F;
	PORTD |= col & 0xF0;
	PORTB |= (col >> 8) & 0x03;
}

