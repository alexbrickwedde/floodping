#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdlib.h>

signed int volatile WDTcounter = 0;

ISR(WDT_vect)
{
  cli();
  WDTCR |= _BV(WDIE) | _BV(WDP2) | _BV(WDP1);
  WDTcounter--;
  sei();
}

unsigned char crand()
{
  int x = rand();
  x >>= 7;
  return x;
}

int
main(void)
{
  cli();
  wdt_reset();
  wdt_enable (WDTO_1S);
  WDTCR |= _BV(WDIE) | _BV(WDP2) | _BV(WDP1);
  sei();

  DDRB |=  (1<<PB0);

  for (;;)
  {
    if (WDTcounter < 0)
    {
      PORTB |= 1;
      int delay = (crand() << 2) + 500;
      _delay_ms(delay);
      PORTB &= 0xfe;
      WDTcounter = crand() & 0x0f;
    }

    wdt_reset();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();

    sleep_cpu ();
    sleep_disable ();
    wdt_reset();
  }
}
