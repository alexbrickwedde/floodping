	.file	"network.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	network_init
	.type	network_init, @function
network_init:
	push r29
	push r28
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
	call uip_init
	ldi r24,lo8(uip_stacks)
	ldi r25,hi8(uip_stacks)
	sts (uip_stack)+1,r25
	sts uip_stack,r24
	call rfm12_stack_init
	ldi r24,lo8(uip_stacks+4)
	ldi r25,hi8(uip_stacks+4)
	sts (uip_stack)+1,r25
	sts uip_stack,r24
	call network_config_load
	call ethersex_meta_netinit
	call init_enc28j60
	call uip_arp_init
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	network_init, .-network_init
	.comm rfm12_status,2,1
.global __do_clear_bss
