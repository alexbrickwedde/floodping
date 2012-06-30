	.file	"dns_net.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	dns_net_main
	.type	dns_net_main, @function
dns_net_main:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	lds r24,uip_flags
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(8)
	andi r25,hi8(8)
	sbiw r24,0
	breq .L2
	call resolv_periodic
.L2:
	lds r24,uip_flags
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(2)
	andi r25,hi8(2)
	sbiw r24,0
	breq .L4
	call resolv_newdata
.L4:
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	dns_net_main, .-dns_net_main
	.comm rfm12_status,2,1
.global __do_clear_bss
