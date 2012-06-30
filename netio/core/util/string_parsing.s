	.file	"string_parsing.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	next_uint16
	.type	next_uint16, @function
next_uint16:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,8
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 8 */
	std Y+5,r25
	std Y+4,r24
	std Y+7,r23
	std Y+6,r22
	std Y+3,__zero_reg__
	ldd r24,Y+4
	ldd r25,Y+5
	std Y+2,r25
	std Y+1,r24
	ldd r30,Y+6
	ldd r31,Y+7
	std Z+1,__zero_reg__
	st Z,__zero_reg__
	rjmp .L2
.L3:
	ldd r24,Y+4
	ldd r25,Y+5
	adiw r24,1
	std Y+5,r25
	std Y+4,r24
.L2:
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	cpi r24,lo8(32)
	breq .L3
	rjmp .L4
.L6:
	ldd r30,Y+6
	ldd r31,Y+7
	ld r24,Z
	ldd r25,Z+1
	movw r18,r24
	lsl r18
	rol r19
	movw r24,r18
	lsl r24
	rol r25
	lsl r24
	rol r25
	add r18,r24
	adc r19,r25
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	clr r25
	sbrc r24,7
	com r25
	add r24,r18
	adc r25,r19
	sbiw r24,48
	ldd r30,Y+6
	ldd r31,Y+7
	std Z+1,r25
	st Z,r24
	ldd r24,Y+4
	ldd r25,Y+5
	adiw r24,1
	std Y+5,r25
	std Y+4,r24
	ldi r24,lo8(1)
	std Y+3,r24
.L4:
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	cpi r24,lo8(48)
	brlt .L5
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	cpi r24,lo8(58)
	brlt .L6
.L5:
	ldd r24,Y+3
	tst r24
	breq .L7
	ldd r24,Y+4
	ldd r25,Y+5
	mov r18,r24
	ldd r24,Y+1
	ldd r25,Y+2
	mov r25,r18
	sub r25,r24
	std Y+8,r25
	rjmp .L8
.L7:
	std Y+8,__zero_reg__
.L8:
	ldd r24,Y+8
/* epilogue start */
	adiw r28,8
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	next_uint16, .-next_uint16
.global	next_hexbyte
	.type	next_hexbyte, @function
next_hexbyte:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,8
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 8 */
	std Y+5,r25
	std Y+4,r24
	std Y+7,r23
	std Y+6,r22
	ldd r24,Y+4
	ldd r25,Y+5
	std Y+3,r25
	std Y+2,r24
	rjmp .L11
.L12:
	ldd r24,Y+4
	ldd r25,Y+5
	adiw r24,1
	std Y+5,r25
	std Y+4,r24
.L11:
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	cpi r24,lo8(32)
	breq .L12
	ldd r30,Y+6
	ldd r31,Y+7
	st Z,__zero_reg__
	std Y+1,__zero_reg__
	rjmp .L13
.L19:
	ldd r30,Y+6
	ldd r31,Y+7
	ld r24,Z
	swap r24
	andi r24,lo8(-16)
	ldd r30,Y+6
	ldd r31,Y+7
	st Z,r24
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	cpi r24,lo8(48)
	brlt .L14
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	cpi r24,lo8(58)
	brge .L14
	ldd r30,Y+6
	ldd r31,Y+7
	ld r24,Z
	mov r25,r24
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	subi r24,lo8(-(-48))
	or r24,r25
	ldd r30,Y+6
	ldd r31,Y+7
	st Z,r24
	rjmp .L15
.L14:
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	cpi r24,lo8(97)
	brlt .L16
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	cpi r24,lo8(103)
	brge .L16
	ldd r30,Y+6
	ldd r31,Y+7
	ld r24,Z
	mov r25,r24
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	subi r24,lo8(-(-87))
	or r24,r25
	ldd r30,Y+6
	ldd r31,Y+7
	st Z,r24
	rjmp .L15
.L16:
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	cpi r24,lo8(65)
	brlt .L17
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	cpi r24,lo8(71)
	brge .L17
	ldd r30,Y+6
	ldd r31,Y+7
	ld r24,Z
	mov r25,r24
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	subi r24,lo8(-(-55))
	or r24,r25
	ldd r30,Y+6
	ldd r31,Y+7
	st Z,r24
	rjmp .L15
.L17:
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	ldd r30,Y+6
	ldd r31,Y+7
	st Z,r24
	std Y+8,__zero_reg__
	rjmp .L18
.L15:
	ldd r24,Y+4
	ldd r25,Y+5
	adiw r24,1
	std Y+5,r25
	std Y+4,r24
	ldd r24,Y+1
	subi r24,lo8(-(1))
	std Y+1,r24
.L13:
	ldd r24,Y+1
	cpi r24,lo8(2)
	brsh .+2
	rjmp .L19
	ldd r24,Y+4
	ldd r25,Y+5
	mov r18,r24
	ldd r24,Y+2
	ldd r25,Y+3
	mov r25,r18
	sub r25,r24
	std Y+8,r25
.L18:
	ldd r24,Y+8
/* epilogue start */
	adiw r28,8
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	next_hexbyte, .-next_hexbyte
