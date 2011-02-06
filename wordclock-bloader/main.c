#ifdef sdfhsdhsgh
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/boot.h>
#include <util/delay.h>
#include "uart.h"

#define BOOT_UART_BAUD_RATE     9600     /* Baudrate */
#define XON                     17       /* XON Zeichen */
#define XOFF                    19       /* XOFF Zeichen */
#define START_SIGN              ':'      /* Hex-Datei Zeilenstartzeichen */

/* Zustände des Bootloader-Programms */
#define BOOT_STATE_EXIT         0
#define BOOT_STATE_PARSER       1

/* Zustände des Hex-File-Parsers */
#define PARSER_STATE_START      0
#define PARSER_STATE_SIZE       1
#define PARSER_STATE_ADDRESS    2
#define PARSER_STATE_TYPE       3
#define PARSER_STATE_DATA       4
#define PARSER_STATE_CHECKSUM   5
#define PARSER_STATE_ERROR      6

void program_page (uint32_t page, uint8_t *buf)
{
  uint16_t i;
  uint8_t sreg;

  /* Disable interrupts */
  sreg = SREG;
  cli();

  eeprom_busy_wait ();

  boot_page_erase (page);
  boot_spm_busy_wait (); /* Wait until the memory is erased. */

  for (i=0; i<SPM_PAGESIZE; i+=2)
  {
    /* Set up little-endian word. */
    uint16_t w = *buf++;
    w += (*buf++) << 8;

    boot_page_fill (page + i, w);
  }

  boot_page_write (page); /* Store buffer in flash page.    */
  boot_spm_busy_wait(); /* Wait until the memory is written.*/

  /* Reenable RWW-section again. We need this if we want to jump back */
  /* to the application after bootloading. */
  boot_rww_enable ();

  /* Re-enable interrupts (if they were ever enabled). */
  SREG = sreg;
}

static uint16_t hex2num (const uint8_t * ascii, uint8_t num)
{
  uint8_t i;
  uint16_t val = 0;

  for (i=0; i<num; i++)
  {
    uint8_t c = ascii[i];

    /* Hex-Ziffer auf ihren Wert abbilden */
    if (c >= '0' && c <= '9') c -= '0';
    else if (c >= 'A' && c <= 'F') c -= 'A' - 10;
    else if (c >= 'a' && c <= 'f') c -= 'a' - 10;

    val = 16 * val + c;
  }

  return val;
}

int main()
{
  /* Empfangenes Zeichen + Statuscode */
  uint16_t c = 0,
  /* Intel-HEX Zieladresse */
  hex_addr = 0,
  /* Zu schreibende Flash-Page */
  flash_page = 0,
  /* Intel-HEX Checksumme zum Überprüfen des Daten */
  hex_check = 0,
  /* Positions zum Schreiben in der Datenpuffer */
  flash_cnt = 0;
  /* temporäre Variable */
  uint8_t temp,
  /* Flag zum steuern des Programmiermodus */
  boot_state = BOOT_STATE_EXIT,
  /* Empfangszustandssteuerung */
  parser_state = PARSER_STATE_START,
  /* Flag zum ermitteln einer neuen Flash-Page */
  flash_page_flag = 1,
  /* Datenpuffer für die Hexdaten*/
  flash_data[SPM_PAGESIZE],
  /* Position zum Schreiben in den HEX-Puffer */
  hex_cnt = 0,
  /* Puffer für die Umwandlung der ASCII in Binärdaten */
  hex_buffer[5],
  /* Intel-HEX Datenlänge */
  hex_size = 0,
  /* Zähler für die empfangenen HEX-Daten einer Zeile */
  hex_data_cnt = 0,
  /* Intel-HEX Recordtype */
  hex_type = 0,
  /* empfangene HEX-Checksumme */
  hex_checksum=0;
  /* Funktionspointer auf 0x0000 */
  void (*start)( void ) = 0x0000;

  /* Füllen der Puffer mit definierten Werten */
  memset(hex_buffer, 0x00, sizeof(hex_buffer));
  memset(flash_data, 0xFF, sizeof(flash_data));

  /* Interrupt Vektoren verbiegen */
  temp = GICR;
  GICR = temp | (1<<IVCE);
  GICR = temp | (1<<IVSEL);

  uart_init( UART_BAUD_SELECT(115200,F_CPU) );

  uart_puts("at\r");
  _delay_ms(100);
  uart_puts("atl1\r");
  _delay_ms(100);

  uart_init( UART_BAUD_SELECT(BOOT_UART_BAUD_RATE,F_CPU) );
  sei();

  uart_puts("Hallo hier ist der echte Bootloader\n\r");
  _delay_ms(2000);

  do
  {
    c = uart_getc();
    if( !(c & UART_NO_DATA) )
    {
      /* Programmzustand: Parser */
      if(boot_state == BOOT_STATE_PARSER)
      {
        switch(parser_state)
        {
          /* Warte auf Zeilen-Startzeichen */
          case PARSER_STATE_START:
          if((uint8_t)c == START_SIGN)
          {
            uart_putc(XOFF);
            parser_state = PARSER_STATE_SIZE;
            hex_cnt = 0;
            hex_check = 0;
            uart_putc(XON);
          }
          break;
          /* Parse Datengröße */
          case PARSER_STATE_SIZE:
          hex_buffer[hex_cnt++] = (uint8_t)c;
          if(hex_cnt == 2)
          {
            uart_putc(XOFF);
            parser_state = PARSER_STATE_ADDRESS;
            hex_cnt = 0;
            hex_size = (uint8_t)hex2num(hex_buffer, 2);
            hex_check += hex_size;
            uart_putc(XON);
          }
          break;
          /* Parse Zieladresse */
          case PARSER_STATE_ADDRESS:
          hex_buffer[hex_cnt++] = (uint8_t)c;
          if(hex_cnt == 4)
          {
            uart_putc(XOFF);
            parser_state = PARSER_STATE_TYPE;
            hex_cnt = 0;
            hex_addr = hex2num(hex_buffer, 4);
            hex_check += (uint8_t) hex_addr;
            hex_check += (uint8_t) (hex_addr >> 8);
            if(flash_page_flag)
            {
              flash_page = hex_addr - hex_addr % SPM_PAGESIZE;
              flash_page_flag = 0;
            }
            uart_putc(XON);
          }
          break;
          /* Parse Zeilentyp */
          case PARSER_STATE_TYPE:
          hex_buffer[hex_cnt++] = (uint8_t)c;
          if(hex_cnt == 2)
          {
            uart_putc(XOFF);
            hex_cnt = 0;
            hex_data_cnt = 0;
            hex_type = (uint8_t)hex2num(hex_buffer, 2);
            hex_check += hex_type;
            switch(hex_type)
            {
              case 0: parser_state = PARSER_STATE_DATA; break;
              case 1: parser_state = PARSER_STATE_CHECKSUM; break;
              default: parser_state = PARSER_STATE_DATA; break;
            }
            uart_putc(XON);
          }
          break;
          /* Parse Flash-Daten */
          case PARSER_STATE_DATA:
          hex_buffer[hex_cnt++] = (uint8_t)c;
          if(hex_cnt == 2)
          {
            uart_putc(XOFF);
            uart_putc('.');
            hex_cnt = 0;
            flash_data[flash_cnt] = (uint8_t)hex2num(hex_buffer, 2);
            hex_check += flash_data[flash_cnt];
            flash_cnt++;
            hex_data_cnt++;
            if(hex_data_cnt == hex_size)
            {
              parser_state = PARSER_STATE_CHECKSUM;
              hex_data_cnt=0;
              hex_cnt = 0;
            }
            /* Puffer voll -> schreibe Page */
            if(flash_cnt == SPM_PAGESIZE)
            {
              uart_puts("P\n\r");
              _delay_ms(100);
              program_page((uint16_t)flash_page, flash_data);
              memset(flash_data, 0xFF, sizeof(flash_data));
              flash_cnt = 0;
              flash_page_flag = 1;
            }
            uart_putc(XON);
          }
          break;
          /* Parse Checksumme */
          case PARSER_STATE_CHECKSUM:
          hex_buffer[hex_cnt++] = (uint8_t)c;
          if(hex_cnt == 2)
          {
            uart_putc(XOFF);
            hex_checksum = (uint8_t)hex2num(hex_buffer, 2);
            hex_check += hex_checksum;
            hex_check &= 0x00FF;
            /* Dateiende -> schreibe Restdaten */
            if(hex_type == 1)
            {
              uart_puts("P\n\r");
              _delay_ms(100);
              program_page((uint16_t)flash_page, flash_data);
              boot_state = BOOT_STATE_EXIT;
            }
            /* Überprüfe Checksumme -> muss '0' sein */
            if(hex_check == 0) parser_state = PARSER_STATE_START;
            else parser_state = PARSER_STATE_ERROR;
            uart_putc(XON);
          }
          break;
          /* Parserfehler (falsche Checksumme) */
          case PARSER_STATE_ERROR:
          uart_putc('#');
          break;
          default:
          break;
        }
      }
      /* Programmzustand: UART Kommunikation */
      else if(boot_state != BOOT_STATE_PARSER)
      {
        switch((uint8_t)c)
        {
          case 'p':
          boot_state = BOOT_STATE_PARSER;
          uart_puts("Programmiere den Flash!\n\r");
          uart_puts("Kopiere die Hex-Datei und fusge sie"
              " hier ein (rechte Maustaste)\n\r");
          break;
          case 'q':
          boot_state = BOOT_STATE_EXIT;
          uart_puts("Verlasse den Bootloader!\n\r");
          break;
          default:
          uart_puts("Du hast folgendes Zeichen gesendet: ");
          uart_putc((unsigned char)c);
          uart_puts("\n\r");
          break;
        }
      }
    }
  }
  while(boot_state!=BOOT_STATE_EXIT);

  uart_puts("Reset AVR!\n\r");
  _delay_ms(1000);

  /* Interrupt Vektoren wieder gerade biegen */
  temp = MCUCR;
  GICR = temp | (1<<IVCE);
  GICR = temp & ~(1<<IVSEL);

  /* Reset */
  start();

  return 0;
}
#endif

/*****************************************************************************
 Title:     STK500v2 compatible bootloader
 Author:    Peter Fleury <pfleury@gmx.ch>   http://jump.to/fleury
 File:      $Id: stk500boot.c,v 1.6 2006/03/04 19:23:26 peter Exp $
 Compiler:  avr-gcc 3.4.5 or 4.0.2 / avr-libc 1.4.3
 Hardware:  All AVRs with bootloader support, tested with ATmega8
 License:   GNU General Public License

 DESCRIPTION:
 This program allows an AVR with bootloader capabilities to
 read/write its own Flash/EEprom. To enter Programming mode
 an input pin is checked. If this pin is pulled low, programming mode
 is entered. If not, normal execution is done from $0000
 "reset" vector in Application area.
 Size < 500 words, fits into a 512 word bootloader section
 when compiled with avr-gcc 4.0.2

 USAGE:
 - Set AVR MCU type and clock-frequency (F_CPU) in the Makefile.
 - Set baud rate below (AVRISP only works with 115200 bps)
 - compile/link the bootloader with the supplied Makefile
 - program the "Boot Flash section size" (BOOTSZ fuses),
 for boot-size 512 words:  program BOOTSZ1
 - enable the BOOT Reset Vector (program BOOTRST)
 - Upload the hex file to the AVR using any ISP programmer
 - Program Boot Lock Mode 3 (program BootLock 11 and BootLock 12 lock bits)
 - Reset your AVR while keeping PROG_PIN pulled low
 - Start AVRISP Programmer (AVRStudio/Tools/Program AVR)
 - AVRISP will detect the bootloader
 - Program your application FLASH file and optional EEPROM file using AVRISP

 AVRdude:
 Please uncomment #define REMOVE_CMD_SPI_MULTI when using AVRdude.
 Comment #define REMOVE_PROGRAM_LOCK_BIT_SUPPORT to reduce code size
 Read Fuse Bits and Read/Write Lock Bits is not supported

 NOTES:
 Based on Atmel Application Note AVR109 - Self-programming
 Based on Atmel Application Note AVR068 - STK500v2 Protocol

 LICENSE:
 Copyright (C) 2006 Peter Fleury

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 *****************************************************************************/
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/boot.h>
#include <avr/pgmspace.h>
#include "command.h"
#include <util/delay.h>

/*
 * Uncomment the following lines to save code space
 */
#define REMOVE_PROGRAM_LOCK_BIT_SUPPORT  // disable program lock bits
#define REMOVE_BOOTLOADER_LED            // no LED to show active bootloader
#define REMOVE_PROG_PIN_PULLUP           // disable internal pullup, use external
#define REMOVE_CMD_SPI_MULTI             // disable processing of SPI_MULTI commands
/*
 * UART Baudrate, AVRStudio AVRISP only accepts 115200 bps
 */
#define BAUDRATE 115200

/*
 * HW and SW version, reported to AVRISP, must match version of AVRStudio
 */
#define CONFIG_PARAM_BUILD_NUMBER_LOW 0
#define CONFIG_PARAM_BUILD_NUMBER_HIGH  0
#define CONFIG_PARAM_HW_VER       0x0F
#define CONFIG_PARAM_SW_MAJOR     2
#define CONFIG_PARAM_SW_MINOR     7

/*
 * use 16bit address variable for ATmegas with <= 64K flash
 */
typedef uint16_t address_t;

/*
 * Calculate the address where the bootloader starts
 * from FLASHEND and BOOTSIZE
 */
#define BOOTSIZE 2048
#define APP_END  (0x8000 -(2*BOOTSIZE))

/*
 * Signature bytes are not available in avr-gcc io_xxx.h
 */
//elif defined (__AVR_ATmega32__)
#define SIGNATURE_BYTES 0x1E9502

#define UART_BAUD_RATE_LOW       UBRRL
#define UART_CONTROL_REG       UCSRB
#define UART_ENABLE_TRANSMITTER  TXEN
#define UART_ENABLE_RECEIVER   RXEN
#define UART_STATUS_REG          UCSRA
#define UART_TRANSMIT_COMPLETE   TXC
#define UART_RECEIVE_COMPLETE  RXC
#define UART_DATA_REG          UDR

#define UART_BAUD_SELECT(baudRate,xtalCpu) ((xtalCpu)/((baudRate)*16L)-1)

/*
 * States used in the receive state machine
 */
#define ST_START    0
#define ST_GET_SEQ_NUM  1
#define ST_MSG_SIZE_1 2
#define ST_MSG_SIZE_2 3
#define ST_GET_TOKEN  4
#define ST_GET_DATA   5
#define ST_GET_CHECK  6
#define ST_PROCESS    7

/*
 * function prototypes
 */
static void
sendchar(char c);
static unsigned char
recchar(void);

/*
 * since this bootloader is not linked against the avr-gcc crt1 functions,
 * to reduce the code size, we need to provide our own initialization
 */
void
__jumpMain(void) __attribute__ ((naked)) __attribute__ ((section (".init9")));

void
__jumpMain(void)
{
  asm volatile ( ".set __stack, %0" :: "i" (RAMEND) );
  asm volatile ( "clr __zero_reg__" );
  // GCC depends on register r1 set to 0
  asm volatile ( "out %0, __zero_reg__" :: "I" (_SFR_IO_ADDR(SREG)) );
  // set SREG to 0
  asm volatile ( "rjmp main");
  // jump to main()
}

/*
 * send single byte to USART, wait until transmission is completed
 */
static void
sendchar(char c)
{
  UART_DATA_REG = c; // prepare transmission
  while (!(UART_STATUS_REG & (1 << UART_TRANSMIT_COMPLETE)))
    ;// wait until byte sent
  UART_STATUS_REG |= (1 << UART_TRANSMIT_COMPLETE); // delete TXCflag
}

/*
 * send single byte to USART, wait until transmission is completed
 */
static void
sendstr(char *c)
{
  while (*c)
  {
    sendchar(*c);
    c++;
  }
}

/*
 * Read single byte from USART, block if no data available
 */
static unsigned char
recchar(void)
{
  while (!(UART_STATUS_REG & (1 << UART_RECEIVE_COMPLETE)))
    ; // wait for data
  return UART_DATA_REG;
}

void
USART_Flush(void)
{
  unsigned char dummy;
  while (UCSRA & (1 << RXC))
    dummy = UDR;
}

int
main(void)
{
  address_t address = 0;
  unsigned char msgParseState;
  unsigned int i = 0;
  unsigned char checksum = 0;
  unsigned char seqNum = 0;
  unsigned int msgLength = 0;
  unsigned char msgBuffer[285];
  unsigned char c, *p;

  UART_BAUD_RATE_LOW = UART_BAUD_SELECT(BAUDRATE,F_CPU);
  UART_CONTROL_REG = (1 << UART_ENABLE_RECEIVER) | (1 << UART_ENABLE_TRANSMITTER);

  sendstr("Bootloader...(press 'p', 2 sec.)\r\n");
  _delay_ms(20);
  USART_Flush();
  _delay_ms(2000);
  if (UART_STATUS_REG & (1 << UART_RECEIVE_COMPLETE) && UDR == 'p')
  {
    sendstr("programming-mode enabled:\r\navrdude -pm32 -cstk500 -PCOM27 -b115200 -v\r\npress 'rrr' after avrdude");
    _delay_ms(100);
    USART_Flush();
    for (;;)
    {
      /*
       * Collect received bytes to a complete message
       */
      msgParseState = ST_START;
      while (msgParseState != ST_PROCESS)
      {
        c = recchar();
        switch (msgParseState)
        {
        case ST_START:
          if (c == MESSAGE_START)
          {
            msgParseState = ST_GET_SEQ_NUM;
            checksum = MESSAGE_START ^ 0;
          }
          else if (c == 'r')
          {
            if( ( recchar() == 'r' ) && ( recchar() == 'r' ))
            {
              boot_rww_enable();
              asm volatile ( "push r1" "\n\t"
                  "push r1" "\n\t"
                  "ret" "\n\t"
                  ::);
            }
          }
          break;

        case ST_GET_SEQ_NUM:
          if ((c == 1) || (c == seqNum))
          {
            seqNum = c;
            msgParseState = ST_MSG_SIZE_1;
            checksum ^= c;
          }
          else
          {
            msgParseState = ST_START;
          }
          break;

        case ST_MSG_SIZE_1:
          msgLength = c << 8;
          msgParseState = ST_MSG_SIZE_2;
          checksum ^= c;
          break;

        case ST_MSG_SIZE_2:
          msgLength |= c;
          msgParseState = ST_GET_TOKEN;
          checksum ^= c;
          break;

        case ST_GET_TOKEN:
          if (c == TOKEN)
          {
            msgParseState = ST_GET_DATA;
            checksum ^= c;
            i = 0;
          }
          else
          {
            msgParseState = ST_START;
          }
          break;

        case ST_GET_DATA:
          msgBuffer[i++] = c;
          checksum ^= c;
          if (i == msgLength)
          {
            msgParseState = ST_GET_CHECK;
          }
          break;

        case ST_GET_CHECK:
          if (c == checksum)
          {
            msgParseState = ST_PROCESS;
          }
          else
          {
            msgParseState = ST_START;
          }
          break;
        }//switch
      }//while(msgParseState)

      /*
       * Now process the STK500 commands, see Atmel Appnote AVR068
       */

      switch (msgBuffer[0])
      {
      case CMD_SPI_MULTI:
        {
          unsigned char answerByte = 0;

          if (msgBuffer[4] == 0x30)
          {
            unsigned char signatureIndex = msgBuffer[6];

            if (signatureIndex == 0)
              answerByte = (SIGNATURE_BYTES >> 16) & 0x000000FF;
            else if (signatureIndex == 1)
              answerByte = (SIGNATURE_BYTES >> 8) & 0x000000FF;
            else
              answerByte = SIGNATURE_BYTES & 0x000000FF;
          }
          msgLength = 7;
          msgBuffer[1] = STATUS_CMD_OK;
          msgBuffer[2] = 0;
          msgBuffer[3] = msgBuffer[4]; // Instruction Byte 1
          msgBuffer[4] = msgBuffer[5]; // Instruction Byte 2
          msgBuffer[5] = answerByte;
          msgBuffer[6] = STATUS_CMD_OK;
        }
        break;
      case CMD_SIGN_ON:
        msgLength = 11;
        msgBuffer[1] = STATUS_CMD_OK;
        msgBuffer[2] = 8;
        msgBuffer[3] = 'A';
        msgBuffer[4] = 'V';
        msgBuffer[5] = 'R';
        msgBuffer[6] = 'I';
        msgBuffer[7] = 'S';
        msgBuffer[8] = 'P';
        msgBuffer[9] = '_';
        msgBuffer[10] = '2';
        break;

      case CMD_GET_PARAMETER:
        {
          unsigned char value;

          switch (msgBuffer[1])
          {
          case PARAM_BUILD_NUMBER_LOW:
            value = CONFIG_PARAM_BUILD_NUMBER_LOW;
            break;
          case PARAM_BUILD_NUMBER_HIGH:
            value = CONFIG_PARAM_BUILD_NUMBER_HIGH;
            break;
          case PARAM_HW_VER:
            value = CONFIG_PARAM_HW_VER;
            break;
          case PARAM_SW_MAJOR:
            value = CONFIG_PARAM_SW_MAJOR;
            break;
          case PARAM_SW_MINOR:
            value = CONFIG_PARAM_SW_MINOR;
            break;
          default:
            value = 0;
            break;
          }
          msgLength = 3;
          msgBuffer[1] = STATUS_CMD_OK;
          msgBuffer[2] = value;
        }
        break;

      case CMD_SET_PARAMETER:
      case CMD_ENTER_PROGMODE_ISP:
      case CMD_LEAVE_PROGMODE_ISP:
        msgLength = 2;
        msgBuffer[1] = STATUS_CMD_OK;
        break;

      case CMD_READ_SIGNATURE_ISP:
        {
          unsigned char signatureIndex = msgBuffer[4];
          unsigned char signature;

          if (signatureIndex == 0)
            signature = (SIGNATURE_BYTES >> 16) & 0x000000FF;
          else if (signatureIndex == 1)
            signature = (SIGNATURE_BYTES >> 8) & 0x000000FF;
          else
            signature = SIGNATURE_BYTES & 0x000000FF;

          msgLength = 4;
          msgBuffer[1] = STATUS_CMD_OK;
          msgBuffer[2] = signature;
          msgBuffer[3] = STATUS_CMD_OK;
        }
        break;

      case CMD_READ_LOCK_ISP:
        msgLength = 4;
        msgBuffer[1] = STATUS_CMD_OK;
        msgBuffer[2] = boot_lock_fuse_bits_get(GET_LOCK_BITS);
        msgBuffer[3] = STATUS_CMD_OK;
        break;

      case CMD_READ_FUSE_ISP:
        {
          unsigned char fuseBits;

          if (msgBuffer[2] == 0x50)
          {
            if (msgBuffer[3] == 0x08)
              fuseBits = boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS);
            else
              fuseBits = boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
          }
          else
          {
            fuseBits = boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);
          }
          msgLength = 4;
          msgBuffer[1] = STATUS_CMD_OK;
          msgBuffer[2] = fuseBits;
          msgBuffer[3] = STATUS_CMD_OK;
        }
        break;

      case CMD_CHIP_ERASE_ISP:
        // erase only main section (bootloader protection)
        address = 0;
        while (address < APP_END)
        {
          boot_page_erase(address); // Perform page erase
          boot_spm_busy_wait(); // Wait until the memory is erased.
          address += SPM_PAGESIZE; // point to next page
        }
        msgLength = 2;
        msgBuffer[1] = STATUS_CMD_OK;
        break;

      case CMD_LOAD_ADDRESS:
        address = (((msgBuffer[3]) << 8) | (msgBuffer[4])) << 1; //convert word to byte address
        msgLength = 2;
        msgBuffer[1] = STATUS_CMD_OK;
        break;

      case CMD_PROGRAM_FLASH_ISP:
      case CMD_PROGRAM_EEPROM_ISP:
        {
          unsigned int size = ((msgBuffer[1]) << 8) | msgBuffer[2];
          unsigned char *p = msgBuffer + 10;
          unsigned int data;
          unsigned char highByte, lowByte;
          address_t tempaddress = address;

          if (msgBuffer[0] == CMD_PROGRAM_FLASH_ISP)
          {
            /* Write FLASH */
            do
            {
              lowByte = *p++;
              highByte = *p++;

              data = (highByte << 8) | lowByte;
              boot_page_fill(address, data);

              address = address + 2; // Select next word in memory
              size -= 2; // Reduce number of bytes to write by two
            }
            while (size); // Loop until all bytes written

            boot_page_write(tempaddress);
            boot_spm_busy_wait();
            boot_rww_enable(); // Re-enable the RWW section
          }
          else
          {
            /* write EEPROM */
            do
            {
              EEARL = address; // Setup EEPROM address
              EEARH = (address >> 8);
              address++; // Select next EEPROM byte

              EEDR = *p++; // get byte from buffer
              EECR |= (1 << EEMWE); // Write data into EEPROM
              EECR |= (1 << EEWE);

              while (EECR & (1 << EEWE))
                ; // Wait for write operation to finish
              size--; // Decrease number of bytes to write
            }
            while (size); // Loop until all bytes written
          }
          msgLength = 2;
          msgBuffer[1] = STATUS_CMD_OK;
        }
        break;

      case CMD_READ_FLASH_ISP:
      case CMD_READ_EEPROM_ISP:
        {
          unsigned int size = ((msgBuffer[1]) << 8) | msgBuffer[2];
          unsigned char *p = msgBuffer + 1;
          msgLength = size + 3;

          *p++ = STATUS_CMD_OK;
          if (msgBuffer[0] == CMD_READ_FLASH_ISP)
          {
            unsigned int data;

            // Read FLASH
            do
            {
              data = pgm_read_word_near(address);
              *p++ = (unsigned char) data; //LSB
              *p++ = (unsigned char) (data >> 8); //MSB
              address += 2; // Select next word in memory
              size -= 2;
            }
            while (size);
          }
          else
          {
            /* Read EEPROM */
            do
            {
              EEARL = address; // Setup EEPROM address
              EEARH = ((address >> 8));
              address++; // Select next EEPROM byte
              EECR |= (1 << EERE); // Read EEPROM
              *p++ = EEDR; // Send EEPROM data
              size--;
            }
            while (size);
          }
          *p++ = STATUS_CMD_OK;
        }
        break;

      default:
        msgLength = 2;
        msgBuffer[1] = STATUS_CMD_FAILED;
        break;
      }

      /*
       * Now send answer message back
       */
      sendchar(MESSAGE_START);
      checksum = MESSAGE_START ^ 0;

      sendchar(seqNum);
      checksum ^= seqNum;

      c = ((msgLength >> 8) & 0xFF);
      sendchar(c);
      checksum ^= c;

      c = msgLength & 0x00FF;
      sendchar(c);
      checksum ^= c;

      sendchar(TOKEN);
      checksum ^= TOKEN;

      p = msgBuffer;
      while (msgLength)
      {
        c = *p++;
        sendchar(c);
        checksum ^= c;
        msgLength--;
      }
      sendchar(checksum);
      seqNum++;

    }//for

  }
  sendstr("running App\r\n");

  /*
   * Now leave bootloader
   */
  boot_rww_enable(); // enable application section

  asm volatile ( "push r1" "\n\t" // Jump to Reset vector in Application Section
      "push r1" "\n\t"
      "ret" "\n\t"
      ::);

  /*
   * Never return to stop GCC to generate exit return code
   * Actually we will never reach this point, but the compiler doesn't
   * understand this
   */
  for (;;)
    ;
}
