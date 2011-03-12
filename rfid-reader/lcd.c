#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
 
void lcd_data(unsigned char temp1)
{
   unsigned char temp2 = temp1;
 
   LCD_PORT |= (1<<LCD_RS);        // RS auf 1 setzen
 
   temp1 = temp1 >> 4;
   temp1 = temp1 & 0x0F;
   LCD_PORT &= 0xF0;
   LCD_PORT |= temp1;               // setzen
   lcd_enable();
 
   temp2 = temp2 & 0x0F;
   LCD_PORT &= 0xF0;
   LCD_PORT |= temp2;               // setzen
   lcd_enable();
   
   _delay_us(242);
}
 
void lcd_command(unsigned char temp1)
{
   unsigned char temp2 = temp1;
 
   LCD_PORT &= ~(1<<LCD_RS);        // RS auf 0 setzen
 
   temp1 = temp1 >> 4;              // oberes Nibble holen
   temp1 = temp1 & 0x0F;            // maskieren
   LCD_PORT &= 0xF0;
   LCD_PORT |= temp1;               // setzen
   lcd_enable();
 
   temp2 = temp2 & 0x0F;            // unteres Nibble holen und maskieren
   LCD_PORT &= 0xF0;
   LCD_PORT |= temp2;               // setzen
   lcd_enable();
   
   _delay_us(42);
}
 
void lcd_enable(void)
{
   // Bei Problemen ggf. Pause gemäß Datenblatt des LCD Controllers einfügen
   // http://www.mikrocontroller.net/topic/81974#685882
   LCD_PORT |= (1<<LCD_EN);
    _delay_us(1);                   // kurze Pause
   // Bei Problemen ggf. Pause gemäß Datenblatt des LCD Controllers verlängern
   // http://www.mikrocontroller.net/topic/80900
   LCD_PORT &= ~(1<<LCD_EN);
}
 
void lcd_init(void)
{
   LCD_DDR = LCD_DDR | 0x0F | (1<<LCD_RS) | (1<<LCD_EN);   // Port auf Ausgang schalten
 
   // muss 3mal hintereinander gesendet werden zur Initialisierung
 
   _delay_ms(15);
   LCD_PORT &= 0xF0;
   LCD_PORT |= 0x03;            
   LCD_PORT &= ~(1<<LCD_RS);      // RS auf 0
   lcd_enable();
 
   _delay_ms(5);
   lcd_enable();
 
   _delay_ms(1);
   lcd_enable();
   _delay_ms(1);
 
   // 4 Bit Modus aktivieren 
   LCD_PORT &= 0xF0;
   LCD_PORT |= 0x02;
   lcd_enable();
   _delay_ms(1);
 
   // 4Bit / 2 Zeilen / 5x7
   lcd_command(0x28);
    
   // Display ein / Cursor aus / kein Blinken
   lcd_command(0x0C); 
 
   // inkrement / kein Scrollen
   lcd_command(0x06);
 
//   lcd_command(CLEAR_DISPLAY);
//   _delay_ms(5);
}
