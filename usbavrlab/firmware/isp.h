/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2
 ***********************************************************************************************/

#ifndef __isp_h_included__
#define	__isp_h_included__

#define ISP_SUPPLY_PORT PORTC
#define ISP_SUPPLY 		PC1
#define	ISP_OUT   		PORTB
#define ISP_IN    		PINB
#define ISP_DDR   		DDRB
#define ISP_RST   		PB2
#define ISP_MOSI  		PB3
#define ISP_MISO  		PB4
#define ISP_SCK   		PB5

#define ISP_DELAY 		1

extern uint8_t ISP_Speed;

#define ISP_STATUS_CONNECTED_OK		1
#define ISP_STATUS_DISCONNECTED		2
#define ISP_STATUS_CONNECTED_NOT_OK 3

extern uint8_t 	ISP_Status;
void 			ISP_connect();
void 			ISP_disconnect();
uint8_t 		ISP_transmit(uint8_t send_byte);
uint8_t 		ISP_enterprogrammingmode();
void    		ISP_erase();
uint8_t 		ISP_readsignaturebyte(uint8_t addr);
uint8_t 		ISP_getsupplyvoltage(void);
void 			(*ISP_statuschanged)(uint8_t); 
void 			ISP_checkstatus(void);
uint8_t 		ISP_deviceisbusy();

#endif /* __isp_h_included__ */
