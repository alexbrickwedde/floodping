/************************************************************************************************
 * Project: USB AVR-ISP
 * Author:  Jens Aehle
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-06....
 * Copyright: (c) 2007 
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 *
 * Achtung diese Version enthält noch keienrlei Sicherheitabfragen!!!
 *
 * Changes:
 *  2007-09-23								V1.1
 * 		fixed AVR910 protocol
 *
 ***********************************************************************************************/

#include "avr910protocol.h"
#include "usb_uart.h"
#include "isp.h"
#include "timer.h"
#include "led.h"
#include "main.h"

uint8_t    	AVR910_Status;

struct {
  uint8_t cmd;
  uint8_t addr[2];
  uint8_t data;
} AVR910_command;

uint8_t AVR910_commandindex;


uint8_t buffer[5];
uint8_t ptr=0;
uint8_t AVR910_device;
char c;

//---------------------------------------------------------------
//
// die DeviceLsite ist nur EINE Auswahl von mir
// die Anzahl abzugleichen ist abzugleichen
//
// Es wäre zu überlegen, ob man die paar Bytes nicht einfach in den 
// EEPROM legt. Die hätte zwei Vorteile:	- weniger PGM-Platz
//											- Anpassung an AVRDUDE wird einafcher
//								Nachteil:	- das Lesen dauert eine Ewigkeit
//
//---------------------------------------------------------------

const char PROGMEM devices[] =
{		    
		    0x51,		//tiny10
			0x50,		//tiny11
			0x55,		//tiny12
			0x56,		//tiny15
			0x58,		//tiny19
			0x5E,		//tiny26
			0x5C,		//tiny28
			0x13,		//S1200
			0x20,		//S2313
			0x48,		//S2323
			0x34,		//S2333
			0x4C,		//S2343
			0x28,		//S4414
			0x30,		//S4433
			0x6C,		//S4434
			0x3A,		//mega8515
			0x3A,		//mega8515B
			0x76,		//mega8
			0x77,		//mega8B
			0x74,		//mega16
			0x75,		//mega16B
			0x72,		//mega32
			0x73,		//mega32B
			0x43,		//mega128
			0x44,		//mega128B
			0x38, 		//S8515
			0x68,		//S8535 
			0x70,		//C8534
			0x71,		//C8544
			0x65,		//mega83
			0x67,		//mega83B
			0x60,		//mega161
			0x61,		//mega161B
			0x64,		//mega163
			0x66,		//mega163B
			0x41		//mega103
};

const char devicecount = sizeof(devices);

//---------------------------------------------------------------
//
// für mich gehören die nachfolgenden Routinen in die isp.c!
// geht aber wegen Platzmangel nicht
//
//---------------------------------------------------------------
void autoincrement(){
    uint16_t addr = (AVR910_command.addr[0]<<8) | AVR910_command.addr[1];
	addr++;
    AVR910_command.addr[1] = addr;
	AVR910_command.addr[0] = addr >> 8;
}

char DoISP(){
	ISP_transmit(AVR910_command.cmd);				// Befehl
	ISP_transmit(AVR910_command.addr[0]);			// Adresse
	ISP_transmit(AVR910_command.addr[1]);			// Adresse
    return ISP_transmit(AVR910_command.data);		// Data
}

//---------------------------------------------------------------
//
// Ende des Blocks
//
//---------------------------------------------------------------

void AVR910_init()
{
  AVR910_Status = PGM_STATUS_IDLE;
}

void AVR910_processmessage()
{
}

void AVR910_byterecived(uint8_t data)
{										// avrdude-Reihenfolge S, V, v, p, a, t, T, P
  buffer[ptr] = data;
  UART_putc(data);
  MAIN_critical_tasks();
  return;

  switch (buffer[0]) {
	    case 'P': 	ISP_connect();			// Umschalten in den Programmiermodus
					if (ISP_enterprogrammingmode()==0) UART_putc('\r');
					else UART_putc('E');
					ptr=0;
		          	break;
					
        case 'S':   UART_puts("AVR Lab"); 	// Name des Dongels in genau 7 Zeichen 
					ptr=0;
		          	break;

	    case 'V':   UART_putc('1');			// Abfrage der SoftWare-Version
                  	UART_putc('1');			// 2Char
					ptr=0;
				  	break;

		case 'v': 	UART_putc('1');			// Abfrage der HardWare-Vversion
                  	UART_putc('0');			// 2Char
					ptr=0;	
			  		break;

		case 'p': 	UART_putc('S');			// Ist der Prommer seriell oder parallel?
                  	ptr=0;					// S = seriel         P = parallel
			  		break;
		
		case 'a': 	UART_putc('Y');			// Kann der . Prommer die Adressen automatisch hochzählen?
					ptr = 0;				// N = nein    Y = ja
				  	break;

        case 't':  	for (ptr=0; ptr<devicecount; ptr++)	// eine Liste der unterstützten Atmels DEVCODE-AVRDUDE.CONF
					       UART_putc(pgm_read_byte(&devices[ptr]));	
					UART_putc(0);			// Liste abschließen						   		
					ptr = 0;
			  		break;

        case 'T':   if (ptr == 0) ptr++;	// AVRDUDE gibt das DEVICE an den Proggie
		            else {
					       AVR910_device = data;
					       ptr = 0;
						   UART_putc('\r');
						 }	
			  		break;

        case 'x':   if (ptr == 0) ptr++;	// Set LEDs - wer es brauch
		            else {
  			               leds[LED_RED].frequency = LED_ON;
					       ptr = 0;
						   UART_putc('\r');
						 }	
			  		break;

        case 'y':   if (ptr == 0) ptr++;	// Clear LEDs - wer es brauch
		            else {
  			               leds[LED_RED].frequency = LED_OFF;
					       ptr = 0;
						   UART_putc('\r');
						 }	
			  		break;

        case 's':   UART_putc(ISP_readsignaturebyte(2));	// Einlesen der Signatur des Atmel-Devices
		            UART_putc(ISP_readsignaturebyte(1));	// 3 Bytes zurückschicken
					UART_putc(ISP_readsignaturebyte(0));
					ptr = 0;
			  		break;

        case 'e':   ISP_erase();			// Chip löschen
 				   	UART_putc('\r');
					ptr = 0;
					break;

        case 'A':   if (ptr < 2) ptr++;		// Set Adress
		            else {
						   AVR910_command.addr[0] = buffer[1];
						   AVR910_command.addr[1] = buffer[2];
						   UART_putc('\r');
					       ptr = 0;
						 }	
			  		break;

        case 'C':   if (ptr == 0) ptr++;				// FLASHschreiben - HiByte
		            else {
						   AVR910_command.cmd = 0x48;
						   //  AVR910_command.addr[0]; 	brauchen wir nicht
						   //  AVR910_command.addr[1];
						   AVR910_command.data = data;
						   DoISP();
						   TIMER_delay(4);				// Warteschleife
						   autoincrement();				// nicht vergessen!!!!
						   UART_putc('\r');
					       ptr = 0;
						 }	
			  		break;

        case 'c':   if (ptr == 0) ptr++;				// FLASHschreiben - LoByte
		            else {
						   AVR910_command.cmd = 0x40;
						   //  AVR910_command.addr[0]; 	brauchen wir nicht
						   //  AVR910_command.addr[1];
						   AVR910_command.data = data;
						   DoISP();
						   TIMER_delay(4);				// Warteschleife
						   UART_putc('\r');
					       ptr = 0;
						 }	
			  		break;

        case 'D':   if (ptr == 0) ptr++;				// Schreiben eines Bytes in den EEPROM
		            else {
						   AVR910_command.cmd = 0xC0;	// Befehl laut tabelle
 					       //  AVR910_command.addr[0]; 		brauchen wir nicht
						   //  AVR910_command.addr[1];
						   AVR910_command.data = data;	
						   DoISP();
						   TIMER_delay(4);				// Warteschleife
						   autoincrement();	
					       ptr = 0;
						   UART_putc('\r');
						}	
			  		break;

        case 'd':   									// Lesen eines Bytes aus dem EEPROM
					AVR910_command.cmd = 0xA0;			// Befehl laut tabelle
 					//  AVR910_command.addr[0]; 			brauchen wir nicht
					//  AVR910_command.addr[1];
					AVR910_command.data = data;			
					c = DoISP();
					UART_putc(c);
					ptr = 0;
			  		break;



        case 'R':   AVR910_command.cmd = 0x28;			// FLASH lesen Hi
 				    //  AVR910_command.addr[0]; 		brauchen wir nicht
					//  AVR910_command.addr[1];
					AVR910_command.data = 0x00;			// egal
					c = DoISP();
					UART_putc(c);
					AVR910_command.cmd = 0x20;			// FLASH lesen Lo
 				    //  AVR910_command.addr[0]; 		brauchen wir nicht
					//  AVR910_command.addr[1];
					AVR910_command.data = 0x00;			// egal
					c = DoISP();
					autoincrement();					// ganz wichtig
					UART_putc(c);
					ptr = 0;
			  		break;

        case 'L':   ISP_disconnect(); 					// Programmiermodus verlassen
					UART_putc('\r');					// event. Hardwarenahe umsetzen
					ptr = 0;
			  		break;
       
	    case 'l':	// Hier ist Vorsicht geboten         // Write LOCK-Bits BRUZEL-BRUZEL- ... nix geht mehr
					if (ptr == 0) ptr++;	
		            else {                               // einfach mal nicht die DoISP Struktur nutzen
//							ISP_transmit(0xAC);			 // Befehl
// 					        ISP_transmit(0xE0); 		     // laut Tabelle: B 111x xxxx
//						    ISP_transmit(0x00);			 // egal
//							ISP_transmit(0xC0 | data);   // hier passiert es
 //						    TIMER_delay(4);				 // Warteschleife

					       	ptr = 0;
						   	UART_putc('\r');
						 }	
			  		break;					

	    case 'm':								        // einfach mal nicht die DoISP Struktur nutzen
					AVR910_command.cmd = 0x4c;			// Befehle
 				    //  AVR910_command.addr[0]; 		brauchen wir nicht
					//  AVR910_command.addr[1];
					AVR910_command.data = 0x00;			// egal
					c = DoISP();					       	
					ptr = 0;
				   	UART_putc('\r');
			  		break;					


        case ':':   if (ptr < 3) ptr++;					// Universal Kommando
		            else {
						   ISP_transmit(buffer[1]);
						   ISP_transmit(buffer[2]);
						   ISP_transmit(buffer[3]);
   						   c = ISP_transmit(0);			// laut Protokoll
						   TIMER_delay(4);				// Warteschleife
						   UART_putc(c);
						   UART_putc('\r');
					       ptr = 0;
						 }	
			  		break;

        case '.':   if (ptr < 4) ptr++;					// New Universal Kommando
		            else {
						   ISP_transmit(buffer[1]);
						   ISP_transmit(buffer[2]);
						   ISP_transmit(buffer[3]);
   						   c = ISP_transmit(buffer[4]); // laut Protokoll
						   TIMER_delay(4);				// Warteschleife
						   UART_putc(c);
						   UART_putc('\r');
					       ptr = 0;
						 }	
			  		break;

		default: if (ptr<5) ptr++;
		         else  {
				    UART_putc('?');
					ptr = 0;
                 }   
  }


}

