/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2008-12-10
 * Copyright: (c) 2008 by Christian Ulrich
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 *
 * Changes:
 ***********************************************************************************************/

#define JTAG_PIN				PINB
#define JTAG_PORT				PORTB
#define JTAG_DDR				DDRB
#define JTAG_TMS				PB2
#define JTAG_TCK				PB5
#define JTAG_TDO				PB3
#define JTAG_TDI				PB4

#define TAP_STATE_UNKNOWN			0
#define TAP_STATE_RESET				1
#define TAP_STATE_IDLE				2
#define TAP_STATE_SELECT_DR_SCAN	3
#define TAP_STATE_CAPTURE_DR		4
#define TAP_STATE_SHIFT_DR			5
#define TAP_STATE_EXIT1_DR			6
#define TAP_STATE_PAUSE_DR			7
#define TAP_STATE_EXIT2_DR			8
#define TAP_STATE_UPDATE_DR			9
#define TAP_STATE_SELECT_IR_SCAN	10
#define TAP_STATE_CAPTURE_IR		11
#define TAP_STATE_SHIFT_IR		    12
#define TAP_STATE_EXIT1_IR			13
#define TAP_STATE_PAUSE_IR			14
#define TAP_STATE_EXIT2_IR			15
#define TAP_STATE_UPDATE_IR			16

extern unsigned char JTAG_TAP_STATE;

void JTAG_attatch();
void JTAG_detatch();

void JTAG_goto_tap_state(unsigned char targetstate);

unsigned char JTAG_shift_bit(unsigned char TDI_on);
void JTAG_shift_bytes(unsigned char *chain,unsigned int len);
