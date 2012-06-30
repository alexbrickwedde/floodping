	.file	"hostname.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.section	.progmem.data,"a",@progbits
	.type	__c.1488, @object
	.size	__c.1488, 6
__c.1488:
	.string	"netio"
	.text
.global	parse_cmd_hostname
	.type	parse_cmd_hostname, @function
parse_cmd_hostname:
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
	ldi r18,lo8(__c.1488)
	ldi r19,hi8(__c.1488)
	rcall .
	rcall .
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	ldd r24,Y+3
	ldd r25,Y+4
	std Z+1,r25
	st Z,r24
	ldd r24,Y+5
	ldd r25,Y+6
	std Z+3,r25
	std Z+2,r24
	std Z+5,r19
	std Z+4,r18
	call snprintf_P
	in r18,__SP_L__
	in r19,__SP_H__
	subi r18,lo8(-(6))
	sbci r19,hi8(-(6))
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r19
	out __SREG__,__tmp_reg__
	out __SP_L__,r18
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
	.size	parse_cmd_hostname, .-parse_cmd_hostname
