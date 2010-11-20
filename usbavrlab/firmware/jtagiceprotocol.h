/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2
 ***********************************************************************************************/

#ifndef __jtagiceprotocol_h_included__
#define __jtagiceprotocol_h_included__

#include <stdint.h>


void JTAGICE_byterecived(uint8_t data);
void JTAGICE_init();

#endif /* __jtagiceprotocol_h_included__ */
