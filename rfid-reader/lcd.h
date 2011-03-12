// Ansteuerung eines HD44780 kompatiblen LCD im 4-Bit-Interfacemodus
// http://www.mikrocontroller.net/articles/AVR-GCC-Tutorial
//
void lcd_data(unsigned char temp1);
void lcd_command(unsigned char temp1);
void lcd_enable(void);
void lcd_init(void);
 
// LCD Befehle
 
#define CLEAR_DISPLAY 0x01
#define CURSOR_HOME   0x02
#define HOME   0x80
 
// Pinbelegung f�r das LCD, an verwendete Pins anpassen
 
#define LCD_PORT      PORTB
#define LCD_DDR       DDRB
#define LCD_RS        PB5
#define LCD_EN        PB4
// DB4 bis DB7 des LCD sind mit PB0 bis PB3 des AVR verbunden 
