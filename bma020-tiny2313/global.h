
#ifndef cbi
#define cbi(sfr, bit)     (_SFR_BYTE(sfr) &= ~_BV(bit)) 
#endif
#ifndef sbi
#define sbi(sfr, bit)     (_SFR_BYTE(sfr) |= _BV(bit))  
#endif

#define LED_AN(LED)     (PORTD |=  (1<<(LED)))
#define LED_AUS(LED)    (PORTD &= ~(1<<(LED)))
#define LED_TOGGLE(LED) (PORTD ^=  (1<<(LED)))
//#define LED1            PD6
//#define LED2            PD5


