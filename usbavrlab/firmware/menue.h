/************************************************************************************************
 * Project: generic
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-03-22
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2
 ***********************************************************************************************/

#ifndef _MENUE_H_
 #define _MENUE_H_

#include <stdint.h>

extern const int MENUE_size;

struct menueentry_t
{
  int level;
  char name[16];
  void (*func)(void);
};

extern const struct menueentry_t menue[];

extern uint8_t MENUE_entry;

void MENUE_init(void);
void MENUE_show(int);

#define KEY_back	1
#define KEY_next	2
#define KEY_ok		3

#define KEY_backp	0
#define KEY_nextp	2
#define KEY_okp		1

int MENUE_is_key(unsigned char key);
void MENUE_task(unsigned char key);
void MENUE_prevlevel(void);
void MENUE_update(void);


#endif //_MENUE_H_
