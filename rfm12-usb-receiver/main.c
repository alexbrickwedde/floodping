//#include <avr/io.h>
//#include <util/delay.h>
//#include <stdlib.h>
//
//#define RF12FREQ868(freq)       ((unsigned short)((freq-860.0)/0.005))
//#define RF_PORT   PORTC
//#define RF_DDR    DDRC
//#define RF_PIN    PINC
//
//#define SDI   5
//#define SCK	  4
//#define CS    3
//#define SDO   2
//#define FSK   1
//
//#ifndef cbi
//#define cbi(sfr, bit)     (_SFR_BYTE(sfr) &= ~_BV(bit))
//#endif
//#ifndef sbi
//#define sbi(sfr, bit)     (_SFR_BYTE(sfr) |= _BV(bit))
//#endif
//
//#define LED_AN(LED)     (PORTD |=  (1<<(LED)))
//#define LED_AUS(LED)    (PORTD &= ~(1<<(LED)))
//#define LED_TOGGLE(LED) (PORTD ^=  (1<<(LED)))
//#define LED1            PD2
//#define LED2            PD3
//
//int uuart_putc(unsigned char c) {
//	while (!(UCSRA & (1 << UDRE))) {
//	}
//
//	UDR = c;
//	return 0;
//}
//
//void uuart_puts(char *s) {
//	while (*s) {
//		uuart_putc(*s);
//		s++;
//	}
//}
//
////uint8_t rfm12_bandwidth = RxBW134;
////uint8_t rfm12_gain = LNA_6;
////uint8_t rfm12_drssi = RSSI_79;
//
//unsigned short rf12_trans(unsigned short wert) {
//	unsigned short werti = 0;
//	unsigned char i;
//
//	cbi(RF_PORT, CS);
//	for (i = 0; i < 16; i++) {
//		if (wert & 32768)
//			sbi(RF_PORT, SDI);
//		else
//			cbi(RF_PORT, SDI);
//		werti <<= 1;
//		if (RF_PIN & (1 << SDO))
//			werti |= 1;
//		sbi(RF_PORT, SCK);
//		wert <<= 1;
//		_delay_us(0.3);
//		cbi(RF_PORT, SCK);
//	}sbi(RF_PORT, CS);
//	return werti;
//}
//
//void rfm12_setbandwidth(unsigned char bandwidth, unsigned char gain,
//		unsigned char drssi) {
//	rf12_trans(
//			0x9400 | ((bandwidth & 7) << 5) | ((gain & 3) << 3) | (drssi & 7));
//}
//
//void rfm12_setfreq(unsigned short freq) {
//	if (freq < 96) // 430,2400MHz
//		freq = 96;
//	else if (freq > 3903) // 439,7575MHz
//		freq = 3903;
//	rf12_trans(0xA000 | freq);
//}
//
//void rfm12_setbaud(unsigned short baud) {
//	if (baud < 663)
//		return;
//	if (baud < 5400) // Baudrate= 344827,58621/(R+1)/(1+CS*7)
//		rf12_trans(0xC680 | ((43104 / baud) - 1));
//	else
//		rf12_trans(0xC600 | ((344828UL / baud) - 1));
//}
//
//void rfm12_setpower(unsigned char power, unsigned char mod) {
//	rf12_trans(0x9800 | (power & 7) | ((mod & 15) << 4));
//}
//
//void rf12_init(void) {
//	RF_DDR = (1 << SDI) | (1 << SCK) | (1 << CS) | (1 << FSK);
//
//	sbi(RF_PORT, CS);
//	sbi(RF_PORT, FSK);
//
//	for (unsigned char i = 0; i < 10; i++)
//		_delay_ms(10); // wait until POR done
//
//	rf12_trans(0xC0E0); // AVR CLK: 10MHz
//	rf12_trans(0x80E7); // Enable FIFO and 868
//	rf12_trans(0xC2AB); // Data Filter: internal
//	rf12_trans(0xCA81); // Set FIFO mode
//	rf12_trans(0xE000); // disable wakeuptimer
//	rf12_trans(0xC800); // disable low duty cycle
//	rf12_trans(0xC4F7); // AFC settings: autotuning: -10kHz...+7,5kHz
//
//	rfm12_setfreq(RF12FREQ868(868.3));
//	rfm12_setbandwidth(4, 1, 4);
//	rfm12_setbaud(666);
//	rfm12_setpower(0, 6);
//
//}
//
//void rfm12_init(void) {
//	rf12_init();
//}
//
//unsigned char rf12_ready(unsigned char bTimeout) {
//	int timeout = 10000;
//
//	cbi(RF_PORT, SDI);
//	cbi(RF_PORT, CS);
//	asm( "nop" );
//	while (!(RF_PIN & (1 << SDO)) && timeout) {
//		if (bTimeout) {
//			timeout--;
//			_delay_us(1); // wait until FIFO ready
//		}
//	}sbi(PORTB, CS);
//	if (timeout == 0)
//		return 0;
//	else
//		return 1;
//}
//
//unsigned rf12_data(void) {
//	//	int res = rf12_trans(0x0000);
//	//	char bOk = ((res) & 0x0200) == 0;
//	//	//	printstatus(res);
//	//	return bOk;
//	cbi(RF_PORT, CS);
//	cbi(RF_PORT, SDI);
//	asm("nop");
//	if (RF_PIN & (1 << SDO))
//		return 1;
//	else
//		return 0;
//}
//
////void rf12_txdata(char *data, unsigned char number) {
////  unsigned char i;
////
////  sbi(RF_PORT, FSK);
////
////  rf12_trans(0x8238); // TX on
////  rf12_ready(0);
////  rf12_trans(0xB8AA);
////  rf12_ready(0);
////  rf12_trans(0xB8AA);
////  rf12_ready(0);
////  rf12_trans(0xB8AA);
////  rf12_ready(0);
////  rf12_trans(0xB82D);
////  rf12_ready(0);
////  rf12_trans(0xB8D4);
////  rf12_ready(0);
////  rf12_trans(0x0000);
////  for (i = 0; i < number; i++) {
////    rf12_ready(0);
////    rf12_trans(0xB800 | (*data++));
////  }
////  rf12_ready(0);
////  rf12_trans(0x8208); // TX off
////}
//
//void rf12_rxdata(char *data, unsigned char number) {
//	unsigned char i;
//	rf12_trans(0x82C8); // RX on
//	rf12_trans(0xCA81); // set FIFO mode
//	rf12_trans(0xCA83); // enable FIFO
//	for (i = 0; i < number; i++) {
//		rf12_ready(0);
//		*data++ = rf12_trans(0xB000);
//	}
//	rf12_trans(0x8208); // RX off
//}
//
//unsigned char rf12_rxbyte(char *data) {
//	int t = rf12_ready(1);
//	if (!t) {
//		return 0;
//	}
//	*data = rf12_trans(0xB000);
//	return 1;
//}
//
//void enable_rx() {
//	rf12_trans(0x82C8); // RX on
//	_delay_ms(10);
//	rf12_trans(0xCA81); // set FIFO mode
//	_delay_ms(10);
//	rf12_trans(0xCA83); // enable FIFO
//	_delay_ms(10);
//}
//
//void disable_rx() {
//	rf12_trans(0x8208); // RX off
//}
//
//unsigned int rf12_rxdata_if_available(char *data, int *res) {
//	*res = rf12_trans(0x0000);
//	char bOk = ((*res) & 0x0200) == 0;
//	if (bOk) {
//		*data = rf12_trans(0xB000);
//	}
//	return (bOk);
//}
//
////volatile char *g_buf;
////volatile int g_len;
////volatile uip_udp_conn_t *g_conn;
//
//void rfm12_int_process(void) {
//	uint16_t status = rf12_trans(0x0000);
//
//	if (status & 0x4000) {
//		uuart_puts("rfm12/por - init");
//		rfm12_init();
//		return;
//	}
//
//	if (status & 0x2000) {
//		uuart_puts("rfm12/overflow - init");
//		rfm12_init();
//		return;
//	}
//
//	if ((status & 0x8000) == 0) {
//		//    return;
//	}
//
////  if (0) {
////    int st2 = status;
////    char bits[16];
////    for (int xc = 0; xc < 16; xc++) {
////      bits[xc] = st2 & 1;
////      st2 >>= 1;
////    }
////    RFM12_DEBUG ("status 0b%d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d\n",bits[15],bits[14],bits[13],bits[12],bits[11],bits[10],bits[9],bits[8],bits[7],bits[6],bits[5],bits[4],bits[3],bits[2],bits[1],bits[0]);
////  }
//
//	char bOk = (status & 0x0200) == 0;
//	//  bOk = rf12_ready(1);
//	if (bOk) {
//		char buf[64];
//		unsigned int x = 0;
//		unsigned int size = 5;
//		while (1) {
//			buf[x] = 0;
//			int res = rf12_rxbyte(buf + x);
//			if (!res) {
//			}
//			switch (buf[4]) {
//			case 'e':
//				size = 9;
//				break;
//			case 'f':
//				size = 19;
//				break;
//			case 'T':
//				size = 25;
//				break;
//			case 'g':
//				size = 19;
//				break;
//			default:
//				size = 6;
//				break;
//			}
//			x++;
//			if (x >= size)
//				break;
//		}
//
//		disable_rx();
//		_delay_us(10);
//		enable_rx();
//
//		if (size > 6) {
//			uuart_puts("\r\n>");
//			char s[20];
//			for (int c = 0; c < size; c++) {
//				itoa(buf[c], s, 16);
//				if (buf[c] < 16) {
//					uuart_putc('0');
//				}
//				uuart_puts(s);
//			}
//			uuart_puts("\r\n#");
//		}
//
////    udpsend(buf, size);
////    switch (buf[4]) {
////    case 'T': {
////      unsigned int temp;
////      memcpy(&temp, buf + 5, 2);
////      char *id = buf + 7;
////      RFM12_DEBUG ("%c%c%c%c %2x:%2x:%2x:%2x:%2x:%2x:%2x:%2x  %4d.%01d C\n", buf[0], buf[1], buf[2], buf[3], id[0], id[1], id[2], id[3], id[4], id[5], id[6], id[7], temp >> 4, (temp << 12) / 6553 );
////    }
////      break;
////    case 'g': {
////      signed int x, y, z;
////      memcpy(&x, buf + 5, 2);
////      memcpy(&y, buf + 7, 2);
////      memcpy(&z, buf + 9, 2);
////
////      int x1 = ((x / 2.3));
////      int y1 = ((y / 2.3));
////      int z1 = ((z / 2.3));
////
////      RFM12_DEBUG ("g %4d %4d %4d\n", x1, y1, z1 );
////    }
////      break;
////    default:
////      RFM12_DEBUG ("unknown symbol %c %2x\n", buf[4], buf[4]);
////      RFM12_DEBUG ("content %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x \n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], buf[8], buf[9], buf[10], buf[11]);
////    }
//	}
//	return;
//
//}
//
//uint16_t rfm12_get_status(void) {
//	uint16_t r;
//	r = rf12_trans(0x0000); /* read status word */
//	return r;
//}
//
//#define BAUD 9600
//#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)
//
///* Name: main.c
// * Project: AVR USB driver for CDC interface on Low-Speed USB
// * Author: Osamu Tamura
// * Creation Date: 2006-05-12
// * Tabsize: 4
// * Copyright: (c) 2006 by Recursion Co., Ltd.
// * License: Proprietary, free under certain conditions. See Documentation.
// *
// * 2006-07-08   removed zero-sized receive block
// * 2006-07-08   adapted to higher baud rate by T.Kitazawa
// *
// */
//
//#include <string.h>
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <avr/pgmspace.h>
//#include <avr/wdt.h>
//#include <util/delay.h>
//
//#include "oddebug.h"
//#include "usbdrv.h"
//#include "usbconfig.h"
//
//enum {
//	SEND_ENCAPSULATED_COMMAND = 0,
//	GET_ENCAPSULATED_RESPONSE,
//	SET_COMM_FEATURE,
//	GET_COMM_FEATURE,
//	CLEAR_COMM_FEATURE,
//	SET_LINE_CODING = 0x20,
//	GET_LINE_CODING,
//	SET_CONTROL_LINE_STATE,
//	SEND_BREAK
//};
//
//static PROGMEM char configDescrCDC[] = { /* USB configuration descriptor */
//9, /* sizeof(usbDescrConfig): length of descriptor in bytes */
//USBDESCR_CONFIG, /* descriptor type */
//67, 0, /* total length of data returned (including inlined descriptors) */
//2, /* number of interfaces in this configuration */
//1, /* index of this configuration */
//0, /* configuration name string index */
//#if USB_CFG_IS_SELF_POWERED
//		(1 << 7) | USBATTR_SELFPOWER, /* attributes */
//#else
//		(1 << 7), /* attributes */
//#endif
//				USB_CFG_MAX_BUS_POWER / 2, /* max USB current in 2mA units */
//
//		/* interface descriptor follows inline: */
//		9, /* sizeof(usbDescrInterface): length of descriptor in bytes */
//		USBDESCR_INTERFACE, /* descriptor type */
//		0, /* index of this interface */
//		0, /* alternate setting for this interface */
//		USB_CFG_HAVE_INTRIN_ENDPOINT, /* endpoints excl 0: number of endpoint descriptors to follow */
//		USB_CFG_INTERFACE_CLASS,
//		USB_CFG_INTERFACE_SUBCLASS,
//		USB_CFG_INTERFACE_PROTOCOL,
//		0, /* string index for interface */
//
//		/* CDC Class-Specific descriptor */
//		5, /* sizeof(usbDescrCDC_HeaderFn): length of descriptor in bytes */
//		0x24, /* descriptor type */
//		0, /* header functional descriptor */
//		0x10, 0x01,
//
//		4, /* sizeof(usbDescrCDC_AcmFn): length of descriptor in bytes */
//		0x24, /* descriptor type */
//		2, /* abstract control management functional descriptor */
//		0x02, /* SET_LINE_CODING,    GET_LINE_CODING, SET_CONTROL_LINE_STATE    */
//
//		5, /* sizeof(usbDescrCDC_UnionFn): length of descriptor in bytes */
//		0x24, /* descriptor type */
//		6, /* union functional descriptor */
//		0, /* CDC_COMM_INTF_ID */
//		1, /* CDC_DATA_INTF_ID */
//
//		5, /* sizeof(usbDescrCDC_CallMgtFn): length of descriptor in bytes */
//		0x24, /* descriptor type */
//		1, /* call management functional descriptor */
//		3, /* allow management on data interface, handles call management by itself */
//		1, /* CDC_DATA_INTF_ID */
//
//		/* Endpoint Descriptor */
//		7, /* sizeof(usbDescrEndpoint) */
//		USBDESCR_ENDPOINT, /* descriptor type = endpoint */
//		0x80 | USB_CFG_EP3_NUMBER, /* IN endpoint number */
//		0x03, /* attrib: Interrupt endpoint */
//		8, 0, /* maximum packet size */
//		USB_CFG_INTR_POLL_INTERVAL, /* in ms */
//
//		/* Interface Descriptor  */
//		9, /* sizeof(usbDescrInterface): length of descriptor in bytes */
//		USBDESCR_INTERFACE, /* descriptor type */
//		1, /* index of this interface */
//		0, /* alternate setting for this interface */
//		2, /* endpoints excl 0: number of endpoint descriptors to follow */
//		0x0A, /* Data Interface Class Codes */
//		0,
//		0, /* Data Interface Class Protocol Codes */
//		0, /* string index for interface */
//
//		/* Endpoint Descriptor */
//		7, /* sizeof(usbDescrEndpoint) */
//		USBDESCR_ENDPOINT, /* descriptor type = endpoint */
//		0x01, /* OUT endpoint number 1 */
//		0x02, /* attrib: Bulk endpoint */
//		8, 0, /* maximum packet size */
//		0, /* in ms */
//
//		/* Endpoint Descriptor */
//		7, /* sizeof(usbDescrEndpoint) */
//		USBDESCR_ENDPOINT, /* descriptor type = endpoint */
//		0x81, /* IN endpoint number 1 */
//		0x02, /* attrib: Bulk endpoint */
//		8, 0, /* maximum packet size */
//		0, /* in ms */
//};
//
//uchar usbFunctionDescriptor(usbRequest_t *rq) {
//
//	if (rq->wValue.bytes[1] == USBDESCR_DEVICE) {
//		usbMsgPtr = (uchar *) usbDescriptorDevice;
//		return usbDescriptorDevice[0];
//	} else { /* must be config descriptor */
//		usbMsgPtr = (uchar *) configDescrCDC;
//		return sizeof(configDescrCDC);
//	}
//}
//
//#define ulong unsigned long
//#define uchar unsigned char
//
//typedef union usbDWord {
//	ulong dword;
//	uchar bytes[4];
//} usbDWord_t;
//
//uchar sendEmptyFrame;
//static uchar intr3Status; /* used to control interrupt endpoint transmissions */
//
//static uchar stopbit, parity, databit;
//static usbDWord_t baud;
//
////static void resetUart(void)
////{
//////    uartInit(baud.dword, parity, stopbit, databit);
//////    irptr    = 0;
//////    iwptr    = 0;
//////    urptr    = 0;
//////    uwptr    = 0;
////}
//
///* ------------------------------------------------------------------------- */
///* ----------------------------- USB interface ----------------------------- */
///* ------------------------------------------------------------------------- */
//
//uchar usbFunctionSetup(uchar data[8]) {
//	usbRequest_t *rq = (void *) data;
//
//	if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) { /* class request type */
//
//		if (rq->bRequest == GET_LINE_CODING
//				|| rq->bRequest == SET_LINE_CODING) {
//			return 0xff;
//			/*    GET_LINE_CODING -> usbFunctionRead()    */
//			/*    SET_LINE_CODING -> usbFunctionWrite()    */
//		}
//		if (rq->bRequest == SET_CONTROL_LINE_STATE) {
////            UART_CTRL_PORT      = (UART_CTRL_PORT&~(1<<UART_CTRL_DTR))|((rq->wValue.word&1)<<UART_CTRL_DTR);
//
//#if USB_CFG_HAVE_INTRIN_ENDPOINT3
//			/* Report serial state (carrier detect). On several Unix platforms,
//			 * tty devices can only be opened when carrier detect is set.
//			 */
//			if (intr3Status == 0)
//				intr3Status = 2;
//#endif
//		}
//#if 1
//		/*  Prepare bulk-in endpoint to respond to early termination   */
//		if ((rq->bmRequestType & USBRQ_DIR_MASK) == USBRQ_DIR_HOST_TO_DEVICE)
//			sendEmptyFrame = 1;
//#endif
//	}
//
//	return 0;
//}
//
///*---------------------------------------------------------------------------*/
///* usbFunctionRead                                                          */
///*---------------------------------------------------------------------------*/
//
//uchar usbFunctionRead(uchar *data, uchar len) {
//
//	data[0] = baud.bytes[0];
//	data[1] = baud.bytes[1];
//	data[2] = baud.bytes[2];
//	data[3] = baud.bytes[3];
//	data[4] = stopbit;
//	data[5] = parity;
//	data[6] = databit;
//
//	return 7;
//}
//
///*---------------------------------------------------------------------------*/
///* usbFunctionWrite                                                          */
///*---------------------------------------------------------------------------*/
//
//uchar usbFunctionWrite(uchar *data, uchar len) {
//
//	/*    SET_LINE_CODING    */
//	baud.bytes[0] = data[0];
//	baud.bytes[1] = data[1];
//	baud.bytes[2] = data[2];
//	baud.bytes[3] = data[3];
//
//	stopbit = data[4];
//	parity = data[5];
//	databit = data[6];
//
//	if (parity > 2)
//		parity = 0;
//	if (stopbit == 1)
//		stopbit = 0;
//
////    resetUart();
//
//	return 1;
//}
//
//static void report_interrupt(void);
//
//void usbFunctionWriteOut(uchar *data, uchar len) {
//
//	if (len > 0)
//	{
//      report_interrupt ();
//	}
//
////    /*  usb -> rs232c:  transmit char    */
////    for( ; len; len-- ) {
////        uchar   uwnxt;
////
////        uwnxt = (uwptr+1) & TX_MASK;
////        if( uwnxt!=irptr ) {
////            tx_buf[uwptr] = *data++;
////            uwptr = uwnxt;
////        }
////    }
////
////    /*  postpone receiving next data    */
////    if( uartTxBytesFree()<=8 )
////        usbDisableAllRequests();
//}
//
//static void hardwareInit(void) {
//
//	/* activate pull-ups except on USB lines */
//	USB_CFG_IOPORT = (uchar) ~((1 << USB_CFG_DMINUS_BIT)
//			| (1 << USB_CFG_DPLUS_BIT));
//	/* all pins input except USB (-> USB reset) */
//#ifdef USB_CFG_PULLUP_IOPORT    /* use usbDeviceConnect()/usbDeviceDisconnect() if available */
//	USBDDR = 0; /* we do RESET by deactivating pullup */
//	usbDeviceDisconnect();
//#else
//	USBDDR = (1 << USB_CFG_DMINUS_BIT) | (1 << USB_CFG_DPLUS_BIT);
//#endif
//
//	/* 250 ms disconnect */wdt_reset();
//	_delay_ms(250);
//
//#ifdef USB_CFG_PULLUP_IOPORT
//	usbDeviceConnect();
//#else
//	USBDDR = 0; /*  remove USB reset condition */
//#endif
//
//	/*    USART configuration    */
//	baud.dword = 9600;
//	stopbit = 0;
//	parity = 0;
//	databit = 8;
////	resetUart();
//}
//
////void uartPoll(void) {
////	uchar next;
//
//	/*  device => RS-232C  */
////        while( (UCSR0A&(1<<UDRE0)) && uwptr!=irptr && (UART_CTRL_PIN&(1<<UART_CTRL_CTS)) ) {
////        UDR0    = tx_buf[irptr];
////        irptr   = (irptr+1) & TX_MASK;
////
////        if( usbAllRequestsAreDisabled() && uartTxBytesFree()>HW_CDC_BULK_OUT_SIZE ) {
////            usbEnableAllRequests();
////        }
////    }
//	/*  device <= RS-232C  */
////	while (UCSR0A & (1 << RXC0)) {
////		next = (iwptr + 1) & RX_MASK;
////		if (next != urptr) {
////			uchar status, data;
////
////			status = UCSR0A;
////			data = UDR0;
////			status &= (1 << FE0) | (1 << DOR0) | (1 << UPE0);
////			if (status == 0) { /* no receiver error occurred */
////				rx_buf[iwptr] = data;
////				iwptr = next;
////			}
////		} else {
////			UART_CTRL_PORT &= ~(1 << UART_CTRL_RTS);
////			break;
////		}
////	}
//	/*  USB <= device  */
////	if (usbInterruptIsReady() && (iwptr != urptr || sendEmptyFrame)) {
////		uchar bytesRead, i;
////
////		bytesRead = (iwptr - urptr) & RX_MASK;
////		if (bytesRead > 8)
////			bytesRead = 8;
////		next = urptr + bytesRead;
////		if (next >= RX_SIZE) {
////			next &= RX_MASK;
////			for (i = 0; i < next; i++)
////				rx_buf[RX_SIZE + i] = rx_buf[i];
////		}
////		usbSetInterrupt(rx_buf + urptr, bytesRead);
////		urptr = next;
////		if (bytesRead)
////			UART_CTRL_PORT |= (1 << UART_CTRL_RTS);
////
////		/* send an empty block after last data block to indicate transfer end */
////		sendEmptyFrame =
////				(bytesRead == HW_CDC_BULK_IN_SIZE && iwptr == urptr) ? 1 : 0;
////	}
////}
//
////int main2(void) {
////
////	wdt_enable(WDTO_1S);
//////	odDebugInit();
////	hardwareInit();
////	usbInit();
////
////	intr3Status = 0;
////	sendEmptyFrame = 0;
////
////	sei();
////	for (int xx = 0;; xx++) { /* main event loop */
////		wdt_reset();
////		usbPoll();
////
////		if (usbInterruptIsReady())
////		{
////			unsigned char x[20];
////			sprintf(x, "hallo %d....", xx);
////			usbSetInterrupt(x, 8);
////		}
////
//////#if USB_CFG_HAVE_INTRIN_ENDPOINT3
//////		/* We need to report rx and tx carrier after open attempt */
//////		if (intr3Status != 0 && usbInterruptIsReady3()) {
//////			static uchar serialStateNotification[10] = { 0xa1, 0x20, 0, 0, 0, 0,
//////					2, 0, 3, 0 };
//////
//////			if (intr3Status == 2) {
//////				usbSetInterrupt3(serialStateNotification, 8);
//////			} else {
//////				usbSetInterrupt3(serialStateNotification + 8, 2);
//////			}
//////			intr3Status--;
//////		}
//////#endif
////	}
////
////	return 0;
////}
//
//#define TBUF_SZ     256
//#define TBUF_MSK    (TBUF_SZ-1)
//
//static uchar tos, val, val2;
//static uchar rcnt, twcnt, trcnt;
//static char rbuf[8], tbuf[TBUF_SZ];
//
//static uchar u2h( uchar u )
//{
//    if( u>9 )
//        u    += 7;
//    return u+'0';
//}
//
//static uchar h2u( uchar h )
//{
//    h    -= '0';
//    if( h>9 )
//        h    -= 7;
//    return h;
//}
//
//static void out_char( uchar c )
//{
//    tbuf[twcnt++]    = c;
//#if TBUF_SZ<256
//    twcnt   &= TBUF_MSK;
//#endif
//}
//
//
//
//static uchar   intr_flag[4];
//
//#define INTR_REG(x)     { intr_flag[x>>3] |= 1<<(x&7); }
//
//#define INTR_MIN        4
//    ISR( TIMER2_COMP_vect )     INTR_REG(4)
//    ISR( TIMER2_OVF_vect )      INTR_REG(5)
//    ISR( TIMER1_CAPT_vect )     INTR_REG(6)
//    ISR( TIMER1_COMPA_vect )    INTR_REG(7)
//    ISR( TIMER1_COMPB_vect )    INTR_REG(8)
//    ISR( TIMER1_OVF_vect )      INTR_REG(9)
//    ISR( TIMER0_OVF_vect )      INTR_REG(10)
//    ISR( SPI_STC_vect )         INTR_REG(11)
//    ISR( USART_RXC_vect )       INTR_REG(12)
//    ISR( USART_UDRE_vect )      INTR_REG(13)
//    ISR( USART_TXC_vect )       INTR_REG(14)
//    ISR( ADC_vect )             INTR_REG(15)
//    ISR( EE_RDY_vect )          INTR_REG(16)
//    ISR( ANA_COMP_vect )        INTR_REG(17)
//    ISR( TWI_vect )             INTR_REG(18)
//#define INTR_MAX        19
//    ISR( SPM_RDY_vect )         INTR_REG(19)
//
//
//static void report_interrupt(void)
//{
//uchar    i, j;
//
//    for( i=4; i<=19; i++ ) {
//        j   = i >> 3;
//        if( intr_flag[j]==0 ) {
//            i   = ( ++j << 3 ) - 1;
//            continue;
//        }
//        if( intr_flag[j] & 1<<(i&7) ) {
//            intr_flag[j] &= ~(1<<(i&7));
//
//            out_char( '\\' );
//            out_char( u2h(i>>4) );
//            out_char( u2h(i&0x0f) );
//            out_char( '\r' );
//            out_char( '\n' );
//            break;
//        }
//    }
//}
//
//int main(void) {
//
//	DDRD |= (1 << LED1) | (1 << LED2); // Port D: Ausgang für LED1 und LED2
//
//	unsigned int xxxx = UBRR_VAL;
//	UBRRH = xxxx >> 8;
//	UBRRL = xxxx & 0xFF;
//
//	UCSRB |= (1 << TXEN); // UART TX einschalten
//	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); // Asynchron 8N1
//
//	uuart_puts("#Uart-Init...\r\n#");
//
//	LED_AN(LED1);
//	LED_AN(LED2);
//
//	rfm12_init();
//
//	wdt_enable(WDTO_1S);
//	odDebugInit();
//	hardwareInit();
//	usbInit();
//
//	intr3Status = 0;
//	sendEmptyFrame = 0;
//
//	sei();
//
//	long x = 0;
//	for (;;) {
//		wdt_reset();
//		usbPoll ();
//
//        /*    device -> host    */
//        if( usbInterruptIsReady() ) {
//            if( twcnt!=trcnt || sendEmptyFrame ) {
//                uchar    tlen;
//
//                tlen    = twcnt>=trcnt? (twcnt-trcnt):(TBUF_SZ-trcnt);
//                if( tlen>8 )
//                    tlen    = 8;
//                usbSetInterrupt((uchar *)tbuf+trcnt, tlen);
//                trcnt   += tlen;
//                trcnt   &= TBUF_MSK;
//                /* send an empty block after last data block to indicate transfer end */
//                sendEmptyFrame = (tlen==8 && twcnt==trcnt)? 1:0;
//            }
//        }
//
//		out_char ('x');
////		x++;
////		if( (x % 4000) == 0)
////		{
////		out_char ('\r');
////		out_char ('\n');
//////			uuart_putc('.');
////		}
////		if (x > 120000) {
////		}
//
////		rfm12_int_process();
//
//		if (intr3Status != 0 && usbInterruptIsReady3()) {
//			static uchar serialStateNotification[10] = { 0xa1, 0x20, 0, 0, 0, 0,
//					2, 0, 3, 0 };
//
//			if (intr3Status == 2) {
//				usbSetInterrupt3(serialStateNotification, 8);
//			} else {
//				usbSetInterrupt3(serialStateNotification + 8, 2);
//			}
//			intr3Status--;
//		}
//
//	}
//	return (1);
//}
