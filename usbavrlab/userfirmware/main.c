/************************************************************************************************
 * Project: USB AVR-Lab
 * Author: Christian Ulrich
 * Contact: christian at ullihome dot de
 *
 * Creation Date: 2007-09-24
 * Copyright: (c) 2007 by Christian Ulrich
 * License: GPLv2
 *
 * Changes:
 ***********************************************************************************************/


#include "avrlab.h"

int main(void)
{
  avrlab_init();
  
  //your code goes here 
    
  while (1)
    {

	  //or here

      avrlab_poll(); //must be called at least every 40 ms
                     //muss mindestens alle 40 ms aufgerufen werden  
	}
}
