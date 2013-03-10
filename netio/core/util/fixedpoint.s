	.file	"fixedpoint.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	itoa_fixedpoint
	.type	itoa_fixedpoint, @function
itoa_fixedpoint:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,9
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 9 */
	std Y+6,r25
	std Y+5,r24
	std Y+7,r22
	std Y+9,r21
	std Y+8,r20
	std Y+4,__zero_reg__
	std Y+3,__zero_reg__
	std Y+2,__zero_reg__
	std Y+1,__zero_reg__
	ldd r24,Y+5
	ldd r25,Y+6
	tst r25
	brge .L2
	ldi r24,lo8(1)
	std Y+2,r24
	ldd r24,Y+5
	ldd r25,Y+6
	com r25
	neg r24
	sbci r25,lo8(-1)
	std Y+6,r25
	std Y+5,r24
.L2:
	ldd r24,Y+4
	mov r18,r24
	ldi r19,lo8(0)
	ldd r24,Y+8
	ldd r25,Y+9
	movw r30,r24
	add r30,r18
	adc r31,r19
	ldd r24,Y+5
	ldd r25,Y+6
	ldi r18,lo8(10)
	ldi r19,hi8(10)
	movw r22,r18
	call __divmodhi4
	subi r24,lo8(-(48))
	st Z,r24
	ldd r24,Y+4
	subi r24,lo8(-(1))
	std Y+4,r24
	ldd r25,Y+4
	ldd r24,Y+7
	cp r25,r24
	brne .L3
	ldd r24,Y+7
	tst r24
	breq .L3
	ldd r24,Y+4
	mov r18,r24
	ldi r19,lo8(0)
	ldd r24,Y+8
	ldd r25,Y+9
	movw r30,r24
	add r30,r18
	adc r31,r19
	ldi r24,lo8(46)
	st Z,r24
	ldd r24,Y+4
	subi r24,lo8(-(1))
	std Y+4,r24
.L3:
	ldd r24,Y+5
	ldd r25,Y+6
	ldi r18,lo8(10)
	ldi r19,hi8(10)
	movw r22,r18
	call __divmodhi4
	movw r24,r22
	std Y+6,r25
	std Y+5,r24
	ldd r24,Y+5
	ldd r25,Y+6
	cp __zero_reg__,r24
	cpc __zero_reg__,r25
	brlt .L2
	ldd r25,Y+4
	ldd r24,Y+7
	cp r25,r24
	brsh .L4
	rjmp .L5
.L6:
	ldd r24,Y+4
	mov r18,r24
	ldi r19,lo8(0)
	ldd r24,Y+8
	ldd r25,Y+9
	movw r30,r24
	add r30,r18
	adc r31,r19
	ldi r24,lo8(48)
	st Z,r24
	ldd r24,Y+4
	subi r24,lo8(-(1))
	std Y+4,r24
.L5:
	ldd r25,Y+4
	ldd r24,Y+7
	cp r25,r24
	brlo .L6
	ldd r24,Y+4
	mov r18,r24
	ldi r19,lo8(0)
	ldd r24,Y+8
	ldd r25,Y+9
	movw r30,r24
	add r30,r18
	adc r31,r19
	ldi r24,lo8(46)
	st Z,r24
	ldd r24,Y+4
	subi r24,lo8(-(1))
	std Y+4,r24
.L4:
	ldd r24,Y+2
	tst r24
	breq .L7
	ldd r24,Y+4
	mov r18,r24
	ldi r19,lo8(0)
	ldd r24,Y+8
	ldd r25,Y+9
	movw r30,r24
	add r30,r18
	adc r31,r19
	ldi r24,lo8(45)
	st Z,r24
	ldd r24,Y+4
	subi r24,lo8(-(1))
	std Y+4,r24
.L7:
	ldd r24,Y+4
	mov r18,r24
	ldi r19,lo8(0)
	ldd r24,Y+8
	ldd r25,Y+9
	movw r30,r24
	add r30,r18
	adc r31,r19
	st Z,__zero_reg__
	ldd r24,Y+4
	std Y+1,r24
	ldd r24,Y+4
	subi r24,lo8(-(-1))
	std Y+4,r24
	rjmp .L8
.L9:
	ldd r24,Y+3
	mov r18,r24
	ldi r19,lo8(0)
	ldd r24,Y+8
	ldd r25,Y+9
	movw r30,r24
	add r30,r18
	adc r31,r19
	ld r24,Z
	std Y+2,r24
	ldd r24,Y+3
	mov r18,r24
	ldi r19,lo8(0)
	ldd r24,Y+8
	ldd r25,Y+9
	movw r26,r24
	add r26,r18
	adc r27,r19
	ldd r24,Y+4
	mov r18,r24
	ldi r19,lo8(0)
	ldd r24,Y+8
	ldd r25,Y+9
	movw r30,r24
	add r30,r18
	adc r31,r19
	ld r24,Z
	st X,r24
	ldd r24,Y+4
	mov r18,r24
	ldi r19,lo8(0)
	ldd r24,Y+8
	ldd r25,Y+9
	movw r30,r24
	add r30,r18
	adc r31,r19
	ldd r24,Y+2
	st Z,r24
	ldd r24,Y+4
	subi r24,lo8(-(-1))
	std Y+4,r24
	ldd r24,Y+3
	subi r24,lo8(-(1))
	std Y+3,r24
.L8:
	ldd r25,Y+3
	ldd r24,Y+4
	cp r25,r24
	brlo .L9
	ldd r24,Y+1
/* epilogue start */
	adiw r28,9
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	itoa_fixedpoint, .-itoa_fixedpoint
