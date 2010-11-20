/************************************************************************************************
 * Project: USB AVR-ISP
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2 for private use
 *	        commercial use prohibited 
 ***********************************************************************************************/

#include "buffer.h"

void BUF_flush(BUF_t *buffer)
{
  buffer->get=0;
  buffer->put=0;
  buffer->n=0;
}

void BUF_init(BUF_t *buffer,unsigned char *buf,uint16_t size)
{
  buffer->buf = buf;
  buffer->size = size;
}

int BUF_get(BUF_t *buffer)
{
	if(buffer->n>0)
	  {
		uint8_t pos;
		pos=buffer->get;
		buffer->get=BUF_newpos(buffer->get,buffer->size);
		buffer->n--;
        return buffer->buf[pos];
	  }
	else
      return -1;
}

void BUF_put(uint8_t val, BUF_t *buffer)
{
    buffer->buf[buffer->put]=val;
    buffer->put=BUF_newpos(buffer->put,buffer->size);
    buffer->n++;
}
