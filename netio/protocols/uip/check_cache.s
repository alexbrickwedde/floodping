	.file	"check_cache.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	uip_check_cache
	.type	uip_check_cache, @function
uip_check_cache:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,7
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 7 */
	std Y+6,r25
	std Y+5,r24
	ldi r24,lo8(uip_stacks+4)
	ldi r25,hi8(uip_stacks+4)
	sts (uip_stack)+1,r25
	sts uip_stack,r24
	ldd r30,Y+5
	ldd r31,Y+6
	ld r18,Z
	ldd r19,Z+1
	lds r30,uip_stack
	lds r31,(uip_stack)+1
	ld __tmp_reg__,Z+
	ld r31,Z
	mov r30,__tmp_reg__
	ld r24,Z
	ldd r25,Z+1
	eor r18,r24
	eor r19,r25
	lds r30,uip_stack
	lds r31,(uip_stack)+1
	ldd __tmp_reg__,Z+2
	ldd r31,Z+3
	mov r30,__tmp_reg__
	ld r24,Z
	ldd r25,Z+1
	and r24,r18
	and r25,r19
	sbiw r24,0
	brne .L2
	ldd r24,Y+5
	ldd r25,Y+6
	movw r30,r24
	adiw r30,2
	ld r18,Z
	ldd r19,Z+1
	lds r30,uip_stack
	lds r31,(uip_stack)+1
	ld r24,Z
	ldd r25,Z+1
	movw r30,r24
	adiw r30,2
	ld r24,Z
	ldd r25,Z+1
	eor r18,r24
	eor r19,r25
	lds r30,uip_stack
	lds r31,(uip_stack)+1
	ldd r24,Z+2
	ldd r25,Z+3
	movw r30,r24
	adiw r30,2
	ld r24,Z
	ldd r25,Z+1
	and r24,r18
	and r25,r19
	sbiw r24,0
	breq .L3
.L2:
	lds r24,uip_draddr
	lds r25,(uip_draddr)+1
	std Y+2,r25
	std Y+1,r24
	movw r26,r28
	adiw r26,3
	ldi r30,lo8(uip_draddr+2)
	ldi r31,hi8(uip_draddr+2)
	ld r24,Z
	ldd r25,Z+1
	adiw r26,1
	st X,r25
	st -X,r24
	rjmp .L4
.L3:
	ldd r30,Y+5
	ldd r31,Y+6
	ld r24,Z
	ldd r25,Z+1
	std Y+2,r25
	std Y+1,r24
	movw r26,r28
	adiw r26,3
	ldd r24,Y+5
	ldd r25,Y+6
	movw r30,r24
	adiw r30,2
	ld r24,Z
	ldd r25,Z+1
	st X+,r24
	st X,r25
.L4:
	movw r24,r28
	adiw r24,1
	call uip_arp_lookup
	sbiw r24,0
	breq .L5
	std Y+7,__zero_reg__
	rjmp .L6
.L5:
	ldi r24,lo8(1)
	std Y+7,r24
.L6:
	ldd r24,Y+7
/* epilogue start */
	adiw r28,7
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	uip_check_cache, .-uip_check_cache
	.comm rfm12_status,2,1
.global __do_clear_bss
