	.file	"fuse.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.section	.progmem.data,"a",@progbits
	.type	__c.1504, @object
	.size	__c.1504, 34
__c.1504:
	.string	"Fuses: low=%02X high=%02X ex=%02X"
	.text
.global	parse_cmd_fuse
	.type	parse_cmd_fuse, @function
parse_cmd_fuse:
	push r16
	push r17
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,22
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 22 */
	std Y+18,r25
	std Y+17,r24
	std Y+20,r23
	std Y+19,r22
	std Y+22,r21
	std Y+21,r20
	ldi r30,lo8(87)
	ldi r31,hi8(87)
	ldi r24,lo8(9)
	st Z,r24
	std Y+12,__zero_reg__
	std Y+11,__zero_reg__
	ldd r30,Y+11
	ldd r31,Y+12
/* #APP */
 ;  33 "hardware/avr/fuse.c" 1
	lpm r24, Z
	
 ;  0 "" 2
/* #NOAPP */
	std Y+10,r24
	ldd r24,Y+10
	std Y+16,r24
	ldi r30,lo8(87)
	ldi r31,hi8(87)
	ldi r24,lo8(9)
	st Z,r24
	ldi r24,lo8(3)
	ldi r25,hi8(3)
	std Y+9,r25
	std Y+8,r24
	ldd r30,Y+8
	ldd r31,Y+9
/* #APP */
 ;  35 "hardware/avr/fuse.c" 1
	lpm r24, Z
	
 ;  0 "" 2
/* #NOAPP */
	std Y+7,r24
	ldd r24,Y+7
	std Y+15,r24
	ldi r30,lo8(87)
	ldi r31,hi8(87)
	ldi r24,lo8(9)
	st Z,r24
	ldi r24,lo8(2)
	ldi r25,hi8(2)
	std Y+6,r25
	std Y+5,r24
	ldd r30,Y+5
	ldd r31,Y+6
/* #APP */
 ;  37 "hardware/avr/fuse.c" 1
	lpm r24, Z
	
 ;  0 "" 2
/* #NOAPP */
	std Y+4,r24
	ldd r24,Y+4
	std Y+14,r24
	ldi r30,lo8(87)
	ldi r31,hi8(87)
	ldi r24,lo8(9)
	st Z,r24
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+3,r25
	std Y+2,r24
	ldd r30,Y+2
	ldd r31,Y+3
/* #APP */
 ;  39 "hardware/avr/fuse.c" 1
	lpm r24, Z
	
 ;  0 "" 2
/* #NOAPP */
	std Y+1,r24
	ldd r24,Y+1
	std Y+13,r24
	ldi r18,lo8(__c.1504)
	ldi r19,hi8(__c.1504)
	ldd r24,Y+16
	mov r20,r24
	ldi r21,lo8(0)
	ldd r24,Y+15
	mov r22,r24
	ldi r23,lo8(0)
	ldd r24,Y+14
	mov r26,r24
	ldi r27,lo8(0)
	ldd r24,Y+13
	mov r16,r24
	ldi r17,lo8(0)
	in r24,__SP_L__
	in r25,__SP_H__
	sbiw r24,14
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r25
	out __SREG__,__tmp_reg__
	out __SP_L__,r24
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	ldd r24,Y+19
	ldd r25,Y+20
	std Z+1,r25
	st Z,r24
	ldd r24,Y+21
	ldd r25,Y+22
	std Z+3,r25
	std Z+2,r24
	std Z+5,r19
	std Z+4,r18
	std Z+7,r21
	std Z+6,r20
	std Z+9,r23
	std Z+8,r22
	std Z+11,r27
	std Z+10,r26
	std Z+13,r17
	std Z+12,r16
	call snprintf_P
	in r18,__SP_L__
	in r19,__SP_H__
	subi r18,lo8(-(14))
	sbci r19,hi8(-(14))
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r19
	out __SREG__,__tmp_reg__
	out __SP_L__,r18
/* epilogue start */
	adiw r28,22
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	pop r17
	pop r16
	ret
	.size	parse_cmd_fuse, .-parse_cmd_fuse
