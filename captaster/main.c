#include <stdlib.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(a) (1 << a)

#ifndef cbi
#define cbi(sfr, bit)     (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit)     (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//
//enum { UP, DOWN };
//
//uint8_t x = 0x80;
//
//ISR (TIMER1_OVF_vect)           /* Note [2] */
//{
//    static uint16_t pwm;        /* Note [3] */
//    static uint8_t direction;
//
//    switch (direction)          /* Note [4] */
//    {
//        case UP:
//            if (++pwm == 0xff)
//                direction = DOWN;
//            break;
//
//        case DOWN:
//            if (--pwm == 0)
//                direction = UP;
//            break;
//    }
//
//    OCR1A = x;                  /* Note [5] */
//}
//
//void
//ioinit (void)                   /* Note [6] */
//{
//    /* Timer 1 is 10-bit PWM (8-bit PWM on some ATtinys). */
//    TCCR1 = _BV(PWM1A) | _BV(COM1A1) | _BV(CS12);
//
//    /* Set PWM value to 0. */
//    OCR1A = 0;
//
//    /* Enable OC1 as output. */
//    DDRB = _BV (PB1) | _BV (PB0);
//
//    /* Enable timer 1 overflow interrupt. */
//    TIMSK = _BV (TOIE1);
//    sei ();
//}
//
//int
//main (void)
//{
//    ioinit ();
//
//    for (;;)                    /* Note [7] */
//        sleep_mode();
//
//    return (0);
//}


//uint8_t getcap(uint8_t pin, uint8_t sampletime, uint8_t waittime) {
//	DDRB &= ~pin;
//	while (waittime--) {
//		__asm__ ("nop");
//	}
//	while (!(PINB & pin) && --sampletime)
//		;
//	DDRB |= pin;
//	return sampletime;
//}
//
//ISR(TIMER1_OVF_vect)
//{
//	OCR1A = 0x80;
//}
//
//int main() {
//
//	//	while (1) {
//	//		int i = 0;
//	//		int n = 11;
//	//		while (--n) {
//	//			i += getcap(1 << PB3, 50, 40);
//	//		}
//	//		i /= 10;
//	//		if (i < 42) {
//	//			PORTB |= (1 << PB0);
//	//		} else if (i > 45) {
//	//			PORTB &= ~(1 << PB0);
//	//		}
//	//		_delay_ms(100);
//	//	}
//
//	wdt_reset();
//	wdt_disable();
//
//	DDRB = _BV (PB1) | _BV (PB0);
//	TCCR1 = _BV(PWM1A) | _BV(COM1A1) | _BV(CS13);
//	OCR1A = 0;
//	TIMSK = (1<<TOIE1);
//	sei ();
//
//	OCR1A = 0x80;
//
//	while (1) {
//		wdt_reset();
//		PORTB |= (1 << PB0);
//		_delay_ms(1);
//		PORTB &= ~(1 << PB0);
//		_delay_ms(1);
//	}
//
//}





#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <string.h>
#include "diskio.h"
#include "pff.h"


#define FCC(c1,c2,c3,c4)	(((DWORD)c4<<24)+((DWORD)c3<<16)+((WORD)c2<<8)+(BYTE)c1)	/* FourCC */

void delay_ms (WORD);	/* Defined in asmfunc.S */
void delay_us (WORD);	/* Defined in asmfunc.S */

EMPTY_INTERRUPT(WDT_vect);


/*---------------------------------------------------------*/
/* Work Area                                               */
/*---------------------------------------------------------*/

volatile BYTE FifoRi, FifoWi, FifoCt;	/* FIFO controls */

BYTE Buff[256];		/* Wave output FIFO */

FATFS Fs;			/* File system object */
DIR Dir;			/* Directory object */
FILINFO Fno;		/* File information */

WORD rb;			/* Return value. Put this here to avoid bugs of avr-gcc */



/*---------------------------------------------------------*/

static
DWORD load_header (void)	/* 0:Invalid format, 1:I/O error, >1:Number of samples */
{
	DWORD sz, f;
	BYTE b, al = 0;


	if (pf_read(Buff, 12, &rb)) return 1;	/* Load file header (12 bytes) */

	if (rb != 12 || LD_DWORD(Buff+8) != FCC('W','A','V','E')) return 0;

	for (;;) {
		wdt_reset();
		pf_read(Buff, 8, &rb);			/* Get Chunk ID and size */
		if (rb != 8) return 0;
		sz = LD_DWORD(&Buff[4]);		/* Chunk size */

		switch (LD_DWORD(&Buff[0])) {	/* FCC */
		case FCC('f','m','t',' ') :					/* 'fmt ' chunk */
			if (sz & 1) sz++;
			if (sz > 100 || sz < 16) return 0;		/* Check chunk size */
			pf_read(Buff, sz, &rb);					/* Get content */
			if (rb != sz) return 0;
			if (Buff[0] != 1) return 0;				/* Check coding type (1) */
			b = Buff[2];
			if (b != 1 && b != 2) return 0;			/* Check channels (1/2) */
			GPIOR0 = al = b;						/* Save channel flag */
			b = Buff[14];
			if (b != 8 && b != 16) return 0;		/* Check resolution (8/16 bit) */
			GPIOR0 |= b;							/* Save resolution flag */
			if (b & 16) al <<= 1;
			f = LD_DWORD(&Buff[4]);					/* Check sampling freqency (8k-48k) */
			if (f < 8000 || f > 48000) return 4;
			OCR0A = (BYTE)(F_CPU / 8 / f) - 1;		/* Sampling freq */
			break;

		case FCC('d','a','t','a') :		/* 'data' chunk (start to play) */
			if (!al) return 0;							/* Check if format valid */
			if (sz < 1024 || (sz & (al - 1))) return 0;	/* Check size */
			if (Fs.fptr & (al - 1)) return 0;			/* Check offset */
			return sz;

		case FCC('D','I','S','P') :		/* 'DISP' chunk (skip) */
		case FCC('L','I','S','T') :		/* 'LIST' chunk (skip) */
		case FCC('f','a','c','t') :		/* 'fact' chunk (skip) */
			if (sz & 1) sz++;
			pf_lseek(Fs.fptr + sz);
			break;

		default :						/* Unknown chunk (error) */
			return 0;
		}
	}

	return 0;
}



static
void ramp (
	int dir		/* 0:Ramp-down, 1:Ramp-up */
)
{
	BYTE v, d, n;


	if (dir) {
		v = 0; d = 1;
	} else {
		v = 128; d = (BYTE)-1;
	}

	n = 128;
	do {
		v += d;
		OCR1A = v; OCR1B = v;
		delay_us(100);
	} while (--n);
}



static
FRESULT play (
	const char *dir,	/* Directory */
	const char *fn		/* File */
)
{
	DWORD sz;
	FRESULT res;
	BYTE sw;
	WORD btr;


	strcpy((char*)Buff, dir);	/* sprintf(Buff, "%s/%s", dir, fn); */
	strcat((char*)Buff, "/");
	strcat((char*)Buff, fn);

	wdt_reset();
	res = pf_open((char*)Buff);		/* Open sound file */
	if (res == FR_OK) {
		sz = load_header();			/* Load file header */
		if (sz < 256) return 255;

		if (!TCCR1) {				/* Enable audio out if not enabled */
			PLLCSR = 0b00000110;	/* Select PLL clock for TC1.ck */
			GTCCR =  0b01100000;	/* Enable TC1.OCB as PWM out (L-ch) */
			TCCR1 = 0b00000001;	/* Start TC1 with TC1.OCA is enabled as PWM out (R-ch) */
			TCCR0A = 0b00000010;	/* Enable TC0.ck = 2MHz as interval timer */
			TCCR0B = 0b00000010;
			TIMSK = _BV(OCIE0A);
			ramp(1);
		}

		FifoCt = 0; FifoRi = 0; FifoWi = 0;		/* Reset FIFO */
		pf_read(0, 512 - (Fs.fptr % 512), &rb);	/* Snip sector unaligned part */
		sz -= rb;

		sw = 1;		/* Button status flag */
		do {
			wdt_reset();
			/* Forward audio data */
			btr = (sz > 1024) ? 1024 : (WORD)sz;
			res = pf_read(0, btr, &rb);
			if (res != FR_OK || btr != rb) break;
			sz -= rb;
			/* Check button down and break on button down */
			sw <<= 1;
			if (bit_is_clear(PINB, 0) && ++sw == 1) break;
		} while (rb == 1024);	/* Repeat until all data read */
	}

	while (FifoCt) ;			/* Wait for FIFO empty */
	OCR1A = 128; OCR1B = 128;

	return res;
}



static
void delay500 (void)
{
	wdt_reset();
	TCCR0B = 0; TCCR0A = 0;	/* Stop TC0 */

	if (TCCR1) {
		ramp(0);
		TCCR1 = 0; GTCCR = 0;	/* Stop TC1 */
	}

	WDTCR = _BV(WDE) | _BV(WDIE) | 0b101;	/* Enable WDT interrupt in timeout of 0.5s */
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);	/* Enter power down mode */
	sleep_mode();

	wdt_reset();
	WDTCR = _BV(WDE) | 0b110;				/* Enable WDT reset in timeout of 1s */
}



/*-----------------------------------------------------------------------*/
/* Main                                                                  */


int main (void)
{
	FRESULT res;
	char *dir;


	MCUSR = 0;
	WDTCR = _BV(WDE) | 0b110;	/* Enable WDT reset in timeout of 1s */

	PORTB = 0b101001;		/* Initialize port: - - H L H L L P */
	DDRB  = 0b111110;

	sei();

	for (;;) {
		if (pf_mount(&Fs) == FR_OK) {	/* Initialize FS */
			wdt_reset();
			res = pf_opendir(&Dir, dir = "wav");	/* Open sound file directory */
			if (res == FR_NO_PATH) {
				res = pf_opendir(&Dir, dir = "");	/* Open root directory if no sound dir */
			}
			while (res == FR_OK) {
				res = pf_readdir(&Dir, 0);			/* Rewind dir */
				while (res == FR_OK) {				/* Play all wav files in the dir */
					wdt_reset();
					res = pf_readdir(&Dir, &Fno);		/* Get a dir entry */
					if (res || !Fno.fname[0]) break;	/* Break on error or end of dir */
					if (!(Fno.fattrib & (AM_DIR|AM_HID)) && strstr(Fno.fname, ".WAV"))
						res = play(dir, Fno.fname);		/* Play file */
				}
			}
		}
		delay500();			/* Delay 500ms in low power sleep mode */
	}
}

