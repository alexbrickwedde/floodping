	.file	"dump_ecmd.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.section	.progmem.data,"a",@progbits
	.type	__c.1619, @object
	.size	__c.1619, 5
__c.1619:
	.string	"%02x"
	.type	__c.1615, @object
	.size	__c.1615, 3
__c.1615:
	.string	"%x"
	.text
.global	parse_cmd_d
	.type	parse_cmd_d, @function
parse_cmd_d:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,14
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 14 */
	std Y+8,r25
	std Y+7,r24
	std Y+10,r23
	std Y+9,r22
	std Y+12,r21
	std Y+11,r20
	rjmp .L2
.L3:
	ldd r24,Y+7
	ldd r25,Y+8
	adiw r24,1
	std Y+8,r25
	std Y+7,r24
.L2:
	ldd r30,Y+7
	ldd r31,Y+8
	ld r24,Z
	cpi r24,lo8(32)
	breq .L3
	ldi r18,lo8(__c.1615)
	ldi r19,hi8(__c.1615)
	rcall .
	rcall .
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	ldd r24,Y+7
	ldd r25,Y+8
	std Z+1,r25
	st Z,r24
	std Z+3,r19
	std Z+2,r18
	movw r24,r28
	adiw r24,5
	std Z+5,r25
	std Z+4,r24
	call sscanf_P
	in r18,__SP_L__
	in r19,__SP_H__
	subi r18,lo8(-(6))
	sbci r19,hi8(-(6))
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r19
	out __SREG__,__tmp_reg__
	out __SP_L__,r18
	cpi r24,1
	cpc r25,__zero_reg__
	breq .L4
	ldi r24,lo8(-1)
	ldi r25,hi8(-1)
	std Y+14,r25
	std Y+13,r24
	rjmp .L5
.L4:
	ldd r24,Y+5
	ldd r25,Y+6
	std Y+4,r25
	std Y+3,r24
	std Y+2,__zero_reg__
	std Y+1,__zero_reg__
	rjmp .L6
.L7:
	ldd r24,Y+1
	ldd r25,Y+2
	lsl r24
	rol r25
	movw r18,r24
	ldd r24,Y+9
	ldd r25,Y+10
	add r18,r24
	adc r19,r25
	ldi r20,lo8(__c.1619)
	ldi r21,hi8(__c.1619)
	ldd r30,Y+3
	ldd r31,Y+4
	ld r24,Z
	mov r22,r24
	ldi r23,lo8(0)
	ldd r24,Y+3
	ldd r25,Y+4
	adiw r24,1
	std Y+4,r25
	std Y+3,r24
	rcall .
	rcall .
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r19
	st Z,r18
	std Z+3,r21
	std Z+2,r20
	std Z+5,r23
	std Z+4,r22
	call sprintf_P
	in r18,__SP_L__
	in r19,__SP_H__
	subi r18,lo8(-(6))
	sbci r19,hi8(-(6))
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r19
	out __SREG__,__tmp_reg__
	out __SP_L__,r18
	ldd r24,Y+1
	ldd r25,Y+2
	adiw r24,1
	std Y+2,r25
	std Y+1,r24
.L6:
	ldd r24,Y+1
	ldd r25,Y+2
	cpi r24,16
	cpc r25,__zero_reg__
	brlt .L7
	ldi r24,lo8(32)
	ldi r25,hi8(32)
	std Y+14,r25
	std Y+13,r24
.L5:
	ldd r24,Y+13
	ldd r25,Y+14
/* epilogue start */
	adiw r28,14
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	parse_cmd_d, .-parse_cmd_d
