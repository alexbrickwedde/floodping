#include <avr/io.h>

        .section .text

        .global main                  
main:
        rcall   avrlab_init

;your code goes here

polling_loop:
        rcall   avrlab_poll

;your code goes here

		rjmp polling_loop
        ret

        .global __vector_default 
__vector_default:
        reti

        .end
