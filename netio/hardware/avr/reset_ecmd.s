	.file	"reset_ecmd.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	parse_cmd_reset
	.type	parse_cmd_reset, @function
parse_cmd_reset:
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
	std Y+2,r25
	std Y+1,r24
	std Y+4,r23
	std Y+3,r22
	std Y+6,r21
	std Y+5,r20
	ldd r30,Y+1
	ldd r31,Y+2
	ld r24,Z
	tst r24
	breq .L2
	ldi r24,lo8(-1)
	ldi r25,hi8(-1)
	std Y+8,r25
	std Y+7,r24
	rjmp .L3
.L2:
	lds r24,status
	ori r24,lo8(4)
	sts status,r24
	std Y+8,__zero_reg__
	std Y+7,__zero_reg__
.L3:
	ldd r24,Y+7
	ldd r25,Y+8
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
	.size	parse_cmd_reset, .-parse_cmd_reset
.global	parse_cmd_wdreset
	.type	parse_cmd_wdreset, @function
parse_cmd_wdreset:
	push r29
	push r28
	rcall .
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 6 */
	std Y+2,r25
	std Y+1,r24
	std Y+4,r23
	std Y+3,r22
	std Y+6,r21
	std Y+5,r20
	lds r24,status
	ori r24,lo8(8)
	sts status,r24
	ldi r24,lo8(0)
	ldi r25,hi8(0)
/* epilogue start */
	adiw r28,6
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	parse_cmd_wdreset, .-parse_cmd_wdreset
