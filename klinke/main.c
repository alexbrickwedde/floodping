#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdlib.h>

volatile unsigned char uiCount = 0;

#define ServoRiegelZu       42
#define ServoRiegelOffen    165

#define FreigabeDauer       40 /* x 100ms */

void PulseOn()
{
  PORTD |= (1 << PD4);
}

void PulseOff()
{
  PORTD &= ~(1 << PD4);
}

ISR(TIMER0_COMPA_vect)
{
  unsigned char ucTemp = uiCount;
  cli();
  if(ucTemp == 0)
  {
    PulseOn();
  }
  else if (ucTemp == 2)
  {
    PulseOff();
  }
  else if (ucTemp >= 10)
  {
    uiCount = 0;
    sei();
    return;
  }
  ucTemp++;
  uiCount = ucTemp;
  sei();
}


int
main(void)
{
  cli();
  wdt_reset();
  wdt_disable();

  DDRD = (1 << PD4) | (1 << PD5);
  PORTD &= ~(1 << PD5);

  OCR0A = ServoRiegelZu;
  TIMSK |= (1 << OCIE0A);
  TCCR0A = (1 << WGM01);
  TCCR0B |= (1 << CS01) | (1 << CS00);

  sei();

  unsigned int uiDelay = 0;
  unsigned char uiServoSoll = ServoRiegelZu;

  for (;;)
  {
    _delay_ms(100);
    int bTuerKontakt = PINB & (1 << PB5);
    int bRFIDFreigabe = PINB & (1 << PB6);
//    int bRFIDFehler = PINB & (1 << PB3);

    if(1 || bTuerKontakt)
    {
      if ( ( uiServoSoll == ServoRiegelOffen ) && ( uiDelay == 0) )
      {
        uiServoSoll = ServoRiegelZu;
        OCR0A = uiServoSoll;
        PORTD |= (1 << PD5);
        _delay_ms(1000);
        PORTD &= ~(1 << PD5);
      }
      else if (bRFIDFreigabe && ( uiServoSoll == ServoRiegelZu ) )
      {
        uiServoSoll = ServoRiegelOffen;
        OCR0A = uiServoSoll;
        uiDelay = FreigabeDauer;
        PORTD |= (1 << PD5);
        _delay_ms(1000);
        PORTD &= ~(1 << PD5);
      }
    }

    if(uiDelay > 0)
    {
      uiDelay--;
    }
  }
}
