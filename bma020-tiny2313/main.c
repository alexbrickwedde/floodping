#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "rf12.h"
#include "bma.h"
#include "main.h"

#include <util/delay.h>

#define AIRID "0101"

unsigned int volatile WDTcounter = 0;

ISR(WDT_OVERFLOW_vect)
{
  cli();
  WDTCSR |= _BV(WDIE) | _BV(WDP2) | _BV(WDP1) | _BV(WDP0);
  WDTcounter++;
  sei();
}

void
send()
{
  unsigned char results[6];

  long x = 0;
  long y = 0;
  long z = 0;
  BMA_init();
  for (int c = 0; c < 32; c++)
  {
    results[0] = BMA_trans(0x8200);
    results[1] = BMA_trans(0x8300);
    results[2] = BMA_trans(0x8400);
    results[3] = BMA_trans(0x8500);
    results[4] = BMA_trans(0x8600);
    results[5] = BMA_trans(0x8700);
    x += ((results[0]) | ((results[1]) << 8)) >> 6;
    y += ((results[2]) | ((results[3]) << 8)) >> 6;
    z += ((results[4]) | ((results[5]) << 8)) >> 6;
    _delay_ms(1);
  }
  BMA_uninit();

  if(x==0 && y==0 && z==0)
    return;

  x >>= 5;
  y >>= 5;
  z >>= 5;

  if (x & 0x0200)
  {
    x |= 0xfe00;
  }
  if (y & 0x0200)
  {
    y |= 0xfe00;
  }
  if (z & 0x0200)
  {
    z |= 0xfe00;
  }

  x -= 36;
  y += 32;
  z -= 8;

  char buf[32];// = "g123456789012345678901234567890\0\0\0";
  buf[0] = 'g';
  memcpy(buf + 1, &x, 2);
  memcpy(buf + 3, &y, 2);
  memcpy(buf + 5, &z, 2);
  buf[7] = 0;
  memcpy(buf + 8, &x, 2);
  memcpy(buf + 10, &y, 2);
  memcpy(buf + 12, &z, 2);
  buf[14] = 0;

  rf12_init();
  rf12_setfreq(RF12FREQ868(868.3));
  rf12_setbandwidth(4, 1, 4);
  rf12_setbaud(666);
  rf12_setpower(0, 6);

  rf12_txdata(buf, 15);

  rf12_trans(0x8201);
  rf12_trans(0x0);
}

#define MAXCOUNT 30

int
main(void)
{

  rf12_preinit(AIRID);

  send();

  cli();
  wdt_reset();
  wdt_enable (WDTO_1S);
  WDTCSR |= _BV(WDIE) | _BV(WDP2) | _BV(WDP1) | _BV(WDP0);
  sei();

  for (;;)
  {
    if (WDTcounter >= MAXCOUNT)
    {

      send();
      WDTcounter = 0;
    }

    wdt_reset();

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();

    sleep_cpu ();
    sleep_disable ();
    wdt_reset();
  }
}
