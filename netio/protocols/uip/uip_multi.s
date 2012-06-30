	.file	"uip_multi.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
.global	uip_stacks
	.data
	.type	uip_stacks, @object
	.size	uip_stacks, 8
uip_stacks:
	.word	rfm12_stack_hostaddr
	.word	rfm12_stack_netmask
	.word	enc_stack_hostaddr
	.word	enc_stack_netmask
.global	uip_stack
	.type	uip_stack, @object
	.size	uip_stack, 2
uip_stack:
	.word	uip_stacks
	.comm enc_stack_stat,52,1
	.comm enc_stack_hostaddr,4,1
	.comm enc_stack_netmask,4,1
	.comm enc_stack_prefix_len,1,1
	.comm rfm12_status,2,1
.global __do_copy_data
.global __do_clear_bss
