#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdlib.h>

//signed int volatile WDTcounter = 0;
//ISR(WDT_vect)
//{
//  cli();
//  WDTCR |= _BV(WDIE) | _BV(WDP2) | _BV(WDP1);
//  WDTcounter--;
//  sei();
//}

volatile unsigned int uiCount = 0;

#define ServoRiegelZu       45
#define ServoRiegelOffen    165

#define FreigabeDauer       200

void PulseOn()
{
  PORTB |= (1 << PB4);
}

void PulseOff()
{
  PORTB &= ~(1 << PB4);
}

ISR(TIMER0_COMPA_vect)
{
  cli();
  if(uiCount == 0)
  {
    PulseOn();
  }
  else if (uiCount == 2)
  {
    PulseOff();
  }
  else if (uiCount >= 10)
  {
    uiCount = 0;
    sei();
    return;
  }
  uiCount++;
  sei();
}


int
main(void)
{
  cli();
  wdt_reset();
  //  wdt_enable (WDTO_1S);
  //  WDTCR |= _BV(WDIE) | _BV(WDP2) | _BV(WDP1);

  DDRB = (1 << PB4);

  OCR0A = ServoRiegelZu;
  TIMSK |= (1 << OCIE0A);
  TCCR0A = (1 << WGM01);
  TCCR0B |= (1 << CS01) | (1 << CS00);

  sei();

  unsigned int uiDelay = 0;
  unsigned char uiServoSoll = ServoRiegelZu;

  for (;;)
  {
    _delay_ms(20);
    int bTuerKontakt = PINB & (1 << PB1);
    int bRFIDFreigabe = PINB & (1 << PB2);
//    int bRFIDFehler = PINB & (1 << PB3);

    if(1 || bTuerKontakt)
    {
      if ( ( uiServoSoll == ServoRiegelOffen ) && ( uiDelay == 0) )
      {
        uiServoSoll = ServoRiegelZu;
        OCR0A = uiServoSoll;
      }
      else if (bRFIDFreigabe && ( uiServoSoll == ServoRiegelZu ) )
      {
        uiServoSoll = ServoRiegelOffen;
        OCR0A = uiServoSoll;
        uiDelay = FreigabeDauer;
      }
    }

    if(uiDelay > 0)
    {
      uiDelay--;
    }
  }
}

//
//int
//main(void)
//{
//  cli();
//  wdt_reset();
//  //  wdt_enable (WDTO_1S);
//  //  WDTCR |= _BV(WDIE) | _BV(WDP2) | _BV(WDP1);
//  sei();
//
//  DDRB = (1 << PB4);
//
//  unsigned int uiServoSoll = ServoRiegelZu;
//  unsigned int uiDelay = 0;
//  for (;;)
//  {
//    PORTB |= (1 << PB4);
//    _delay_us(uiServoSoll);
//    PORTB &= ~(1 << PB4);
//    _delay_ms(18);
//
//    int bTuerKontakt = PINB & (1 << PB1);
//    int bRFIDFreigabe = PINB & (1 << PB2);
////    int bRFIDFehler = PINB & (1 << PB3);
//
//    uiServoSoll = bRFIDFreigabe ? ServoRiegelZu : ServoRiegelOffen;
//    continue;
//    if(1 || bTuerKontakt)
//    {
//      if ( ( uiServoSoll == ServoRiegelOffen ) && ( uiDelay == 0) )
//      {
//        uiServoSoll = ServoRiegelZu;
//      }
//      else if (bRFIDFreigabe && ( uiServoSoll == ServoRiegelZu ) )
//      {
//        uiServoSoll = ServoRiegelOffen;
//        uiDelay = FreigabeDauer;
//      }
//    }
//
//    if(uiDelay > 0)
//    {
//      uiDelay--;
//    }
//
//  }
//}
