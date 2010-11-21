#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "ldr.h"
#include "i2c-rtc.h"

# define cli()  __asm__ __volatile__ ("cli" ::)
# define sei()  __asm__ __volatile__ ("sei" ::)

#define BIT(a) (1 << a)

void InitPWM() {
	DDRD = 0xfc; //(1 << PD4) || (1 << PD5) || (1 << PD7);


	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
	TCCR1B = (1 << CS10);
	TCCR2 = (1 << CS20) | (1 << WGM20) | (1 << COM21);
	TCCR0 = (1 << WGM01) | (1 << WGM00) | (1 << COM01) | (01 << COM00) | (1
			<< CS00) | (1 << CS02);

	TIMSK &= ~0x3c;
}

void SetPWMOutput(uint8_t duty) {
	OCR1AL = duty;
	OCR1BL = 255 - duty;
	OCR0 = duty;
	OCR2 = duty;
}

//void sleep()
//{
//  wdt_reset();
//
//  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//  sleep_enable();
//
//  sleep_cpu ();
//  sleep_disable ();
//  wdt_reset();
//}


void SetColor(uint8_t bright, uint8_t uiR, uint8_t uiG, uint8_t uiB) {
	OCR1BL = (((bright) * uiR) >> 8);
	OCR1AL = (((bright) * uiG) >> 8);
	OCR2 = (((bright) * uiB) >> 8);
}

#ifndef cbi
#define cbi(sfr, bit)     (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit)     (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void uartPutc(char c) {
	while (!(UCSRA & (1 << UDRE)))
		;
	UDR = c;
}

void uartPuts(char *s) {
	int x = 0;
	while (s[x]) {
		uartPutc(s[x]);
		x++;
	}
}

#define SHIFT_SR_SPI_DDR  DDRB
#define SHIFT_SR_SPI_PORT PORTB
#define SHIFT_SR_SPI_MOSI PIN5
#define SHIFT_SR_SPI_MISO PIN6
#define SHIFT_SR_SPI_RCLK PIN4
#define SHIFT_SR_SPI_SCK  PIN7

void shift32_output(uint32_t value) {
	uint8_t u0 = (uint8_t) (value);
	uint8_t u1 = (uint8_t) (value >> 8);
	uint8_t u2 = (uint8_t) (value >> 16);
	uint8_t u3 = (uint8_t) (value >> 24);

	SPDR = u3;
	while (!(SPSR & (1 << SPIF)))
		;

	SPDR = u2;
	while (!(SPSR & (1 << SPIF)))
		;

	SPDR = u1;
	while (!(SPSR & (1 << SPIF)))
		;

	SPDR = u0;
	while (!(SPSR & (1 << SPIF)))
		;

	/* latch data */
	SHIFT_SR_SPI_PORT &= ~(1 << SHIFT_SR_SPI_RCLK);
	SHIFT_SR_SPI_PORT |= (1 << SHIFT_SR_SPI_RCLK);
}

void shift_init(void) {
	SHIFT_SR_SPI_DDR |= (1 << SHIFT_SR_SPI_MOSI) | (1 << SHIFT_SR_SPI_RCLK)
			| (1 << SHIFT_SR_SPI_SCK);
	SHIFT_SR_SPI_DDR &= ~(1 << SHIFT_SR_SPI_MISO); /* MISO muss eingang sein */
	SHIFT_SR_SPI_PORT |= (1 << SHIFT_SR_SPI_RCLK) | (1 << SHIFT_SR_SPI_MISO);

	SPCR = (1 << SPE) | (1 << MSTR) | (1 << CPOL) | (1 << SPR0) | (1 << SPR1);

	SPSR |= (1 << SPI2X);

	shift32_output(0); /* send dummybytes to intialize */
}

int main() {

	cli();

	UBRRH = 0x00;
	UBRRL = 0x08;

	UCSRB |= (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);

	uartPuts("WordClock V0.1 initializing...\r\n");

	//	PORTA |= (1 << PA7) | (1 << PA6);
	//	DDRA = 0;

	uartPuts("\r\n... PWM");
	InitPWM();
	SetColor(0xFF, 0xFF, 0x01, 0x01);

	uartPuts("\r\n... Shifter");
	shift_init();
	SetColor(0xFF, 0xFF, 0xFF, 0x01);

	uartPuts("\r\n... LDR ADC");
	ldr_init();
	SetColor(0xFF, 0x01, 0xFF, 0xFF);

//	uartPuts("\r\n... DCF77");
//	uartPuts("...PON-Hi");
//	DDRD |= ( 1 << PD3);
//	PORTD |= ( 1 << PD3);
//	_delay_ms(1000);
//	uartPuts("...PON-Lo");
//	PORTD &= 0xff ^ ( 1 << PD3 );
//
//	while(1){}

	SetColor(0xFF, 0x01, 0xFF, 0xFF);
	uartPuts("\r\n... RTC");
	DATETIME time;
	uint8_t i2c_errorcode;
	uint8_t i2c_status;
	if (!i2c_rtc_init(&i2c_errorcode, &i2c_status)) // initialize rtc
	{
		uartPuts(" FAILED !!!\r\n");
		for (int uiCount = 0; uiCount < 10; uiCount++) {
			SetColor(0xFF, 0x01, 0x01, 0x01);
			_delay_ms(20);
			SetColor(0xFF, 0xff, 0xff, 0xff);
			_delay_ms(20);
		}
	}

	SetColor(0xFF, 0xFF, 0xFF, 0xFF);
	sei();

	uartPuts("\r\nReady...\r\n");

	//	uint32_t x = 1;
	//	while(1)
	//	{
	//		  shift32_output(x);
	//		  _delay_ms(100);
	//		  x = x << 1;
	//		  if(x==0) x = 1;
	//	}


	//	time.hh = 19;
	//	time.mm = 24;
	//	time.ss = 2;
	//	time.DD = 18;
	//	time.MM = 11;
	//	time.YY = 10;
	//	time.wd = 3;
	//	if(!i2c_rtc_write(&time))
	//	{
	//		for (uiCount = 0; uiCount < 10; uiCount++) {
	//			SetColor(0x01, 0x01, 0x01);
	//			_delay_ms(20);
	//			SetColor(0xff, 0xff, 0xff);
	//			_delay_ms(20);
	//		}
	//	}

	int uiR = 0x01;
	int uiG = 0x01;
	int uiB = 0x01;
	int uiCount = 0;

	uint16_t Button1 = 0;
	uint16_t Button2 = 0;

	while (1) {

		_delay_ms(10);
		uiCount++;

		ldr_read();
		uint8_t bright = ldr_get_brightness();
		if (bright < 64) {
			bright = (bright >> 1) + 32;
		}
		SetColor(bright, uiR, uiG, uiB);

		if (uiCount % 10) {
			continue;
		}

		if (!(PINA & (1 << PA7))) {
			Button1++;
		} else {
			Button1 = 0;
		}

		if (!(PINA & (1 << PA6))) {
			Button2++;
		} else {
			Button2 = 0;
		}

		if (Button1 > 1) {
			if (((Button1 + 10) % 12) == 0 || Button1 > 36) {
				uartPuts("Hour++\r\n");
				int res = i2c_rtc_read(&time, 0);
				SetColor(bright, uiR, uiG, uiB);
				add_hour(time);
				if (time.hh > 23)
					time.hh = 0;
				res = i2c_rtc_write(&time);
				char s[100];
				sprintf(s, "time : %02d:%02d:%02d\r\n", time.hh, time.mm,
						time.ss);
				uartPuts(s);
			}
		}

		if(Button2 == 2) {
			uartPuts("toggle DST\r\n");
			set_dst((rtc_dstactive == 0) ? 1 : 0);
		}

//		if (Button2 > 1) {
//			if (((Button2 + 10) % 12) == 0 || Button2 > 36) {
//				uartPuts("Min++\r\n");
//				res = i2c_rtc_read(&time, 1);
//				SetColor(bright, uiR, uiG, uiB);
//				add_minute(time);
//				time.ss = 0;
//				if (time.mm > 59)
//					time.mm = 0;
//				i2c_rtc_write(&time);
//				char s[100];
//				sprintf(s, "time : %02d:%02d:%02d\r\n", time.hh, time.mm,
//						time.ss);
//				uartPuts(s);
//			}
//		}

//		if(PIND & (1<< PD2))
//		{
//			uartPuts("1\r\n");
//		}
//		else
//		{
//			uartPuts("0\r\n");
//		}

		if (uiCount % 100) {
			continue;
		}

		int res = i2c_rtc_read(&time, 1);
		SetColor(bright, uiR, uiG, uiB);
		if (!res) {
			uartPuts("RTC error\r\n");
			for (uiCount = 0; uiCount < 40; uiCount++) {
				SetColor(0x01, 0x01, 0x01, 0x01);
				_delay_ms(50);
				SetColor(0xff, 0xff, 0xff, 0xff);
				_delay_ms(50);
			}
		}

		if (time.ss != 0) {
			char s[100];
			sprintf(s, "time : %02d:%02d:%02d %02d.%02d.%4d\r\n", time.hh, time.mm, time.ss, time.DD, time.MM, time.YY+2000);
			uartPuts(s);
		}

		shift32_output((((uint32_t) 1) << (time.ss % 5)) ^ 0xffffffff);

		if (time.ss < 16) {
			uiR = 0xff;
			uiG = time.ss << 4;
			uiB = 0x01;
		} else if (time.ss < 32) {
			uiR = 0xff - (time.ss << 4);
			uiG = 0xff;
			uiB = 0x01;
		} else if (time.ss < 48) {
			uiR = 0x01;
			uiG = 0xff;
			uiB = time.ss << 4;
		} else if (time.ss < 64) {
			uiR = 0x01;
			uiG = 0xff - (time.ss << 4);
			uiB = 0xff;
		} else if (time.ss < 80) {
			uiR = time.ss << 4;
			uiG = 0x01;
			uiB = 0xff;
		} else if (time.ss < 96) {
			uiR = 0xff;
			uiG = 0x01;
			uiB = 0xff - (time.ss << 4);
		} else {
		}

		if (uiCount % 1000) {
			uiCount = 0;
		}
	}
	return 0;
}
