	.file	"uip_rfm12.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	rfm12_stack_init
	.type	rfm12_stack_init, @function
rfm12_stack_init:
	push r29
	push r28
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
	ldi r24,lo8(266)
	ldi r25,hi8(266)
	std Y+2,r25
	std Y+1,r24
	movw r30,r28
	adiw r30,3
	ldi r24,lo8(-6144)
	ldi r25,hi8(-6144)
	std Z+1,r25
	st Z,r24
	lds r30,uip_stack
	lds r31,(uip_stack)+1
	ld __tmp_reg__,Z+
	ld r31,Z
	mov r30,__tmp_reg__
	ldd r24,Y+1
	ldd r25,Y+2
	std Z+1,r25
	st Z,r24
	lds r30,uip_stack
	lds r31,(uip_stack)+1
	ld r24,Z
	ldd r25,Z+1
	movw r26,r24
	adiw r26,2
	movw r30,r28
	adiw r30,3
	ld r24,Z
	ldd r25,Z+1
	st X+,r24
	st X,r25
	ldi r24,lo8(-1)
	ldi r25,hi8(-1)
	std Y+2,r25
	std Y+1,r24
	movw r30,r28
	adiw r30,3
	ldi r24,lo8(-769)
	ldi r25,hi8(-769)
	std Z+1,r25
	st Z,r24
	lds r30,uip_stack
	lds r31,(uip_stack)+1
	ldd __tmp_reg__,Z+2
	ldd r31,Z+3
	mov r30,__tmp_reg__
	ldd r24,Y+1
	ldd r25,Y+2
	std Z+1,r25
	st Z,r24
	lds r30,uip_stack
	lds r31,(uip_stack)+1
	ldd r24,Z+2
	ldd r25,Z+3
	movw r26,r24
	adiw r26,2
	movw r30,r28
	adiw r30,3
	ld r24,Z
	ldd r25,Z+1
	adiw r26,1
	st X,r25
	st -X,r24
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	rfm12_stack_init, .-rfm12_stack_init
	.comm rfm12_stack_stat,52,1
	.comm rfm12_stack_hostaddr,4,1
	.comm rfm12_stack_netmask,4,1
	.comm rfm12_stack_prefix_len,1,1
	.comm rfm12_status,2,1
.global __do_clear_bss
