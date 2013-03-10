	.file	"periodic.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	periodic_init
	.type	periodic_init, @function
periodic_init:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r30,lo8(129)
	ldi r31,hi8(129)
	ldi r24,lo8(13)
	st Z,r24
	ldi r30,lo8(136)
	ldi r31,hi8(136)
	ldi r24,lo8(311)
	ldi r25,hi8(311)
	std Z+1,r25
	st Z,r24
	ldi r26,lo8(111)
	ldi r27,hi8(111)
	ldi r30,lo8(111)
	ldi r31,hi8(111)
	ld r24,Z
	ori r24,lo8(2)
	st X,r24
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	periodic_init, .-periodic_init
.global	__vector_13
	.type	__vector_13, @function
__vector_13:
	push __zero_reg__
	push r0
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r24
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: Signal */
/* frame size = 0 */
	ldi r24,lo8(1)
	sts newtick,r24
	lds r24,milliticks
	subi r24,lo8(-(1))
	sts milliticks,r24
	lds r24,milliticks
	cpi r24,lo8(50)
	brlo .L5
	sts milliticks,__zero_reg__
.L5:
/* epilogue start */
	pop r28
	pop r29
	pop r24
	pop r0
	out __SREG__,r0
	pop r0
	pop __zero_reg__
	reti
	.size	__vector_13, .-__vector_13
	.comm milliticks,1,1
.global __do_clear_bss
