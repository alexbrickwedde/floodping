	.file	"dns_ecmd.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	parse_cmd_dns_server
	.type	parse_cmd_dns_server, @function
parse_cmd_dns_server:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,13
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 13 */
	std Y+7,r25
	std Y+6,r24
	std Y+9,r23
	std Y+8,r22
	std Y+11,r21
	std Y+10,r20
	rjmp .L2
.L3:
	ldd r24,Y+6
	ldd r25,Y+7
	adiw r24,1
	std Y+7,r25
	std Y+6,r24
.L2:
	ldd r30,Y+6
	ldd r31,Y+7
	ld r24,Z
	cpi r24,lo8(32)
	breq .L3
	ldd r30,Y+6
	ldd r31,Y+7
	ld r24,Z
	tst r24
	breq .L4
	ldd r24,Y+6
	ldd r25,Y+7
	movw r18,r28
	subi r18,lo8(-(1))
	sbci r19,hi8(-(1))
	movw r22,r18
	call parse_ip
	tst r24
	breq .L5
	ldi r24,lo8(-1)
	ldi r25,hi8(-1)
	std Y+13,r25
	std Y+12,r24
	rjmp .L6
.L5:
	movw r24,r28
	adiw r24,1
	call resolv_conf
	ldi r24,lo8(18)
	ldi r25,hi8(18)
	movw r18,r28
	subi r18,lo8(-(1))
	sbci r19,hi8(-(1))
	movw r22,r18
	ldi r20,lo8(4)
	ldi r21,hi8(4)
	call eeprom_write_block_hack
	call eeprom_get_chksum
	std Y+5,r24
	movw r18,r28
	subi r18,lo8(-(5))
	sbci r19,hi8(-(5))
	ldi r24,lo8(22)
	ldi r25,hi8(22)
	movw r22,r18
	ldi r20,lo8(1)
	ldi r21,hi8(1)
	call eeprom_write_block_hack
	std Y+13,__zero_reg__
	std Y+12,__zero_reg__
	rjmp .L6
.L4:
	call resolv_getserver
	ldd r18,Y+8
	ldd r19,Y+9
	ldd r20,Y+10
	ldd r21,Y+11
	movw r22,r18
	call print_ipaddr
	std Y+13,r25
	std Y+12,r24
.L6:
	ldd r24,Y+12
	ldd r25,Y+13
/* epilogue start */
	adiw r28,13
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	parse_cmd_dns_server, .-parse_cmd_dns_server
	.section	.progmem.data,"a",@progbits
	.type	__c.2131, @object
	.size	__c.2131, 42
__c.2131:
	.string	"nslookup triggered, try again for result."
	.text
.global	parse_cmd_nslookup
	.type	parse_cmd_nslookup, @function
parse_cmd_nslookup:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,10
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 10 */
	std Y+4,r25
	std Y+3,r24
	std Y+6,r23
	std Y+5,r22
	std Y+8,r21
	std Y+7,r20
	rjmp .L9
.L10:
	ldd r24,Y+3
	ldd r25,Y+4
	adiw r24,1
	std Y+4,r25
	std Y+3,r24
.L9:
	ldd r30,Y+3
	ldd r31,Y+4
	ld r24,Z
	cpi r24,lo8(32)
	breq .L10
	ldd r24,Y+3
	ldd r25,Y+4
	call resolv_lookup
	std Y+2,r25
	std Y+1,r24
	ldd r24,Y+1
	ldd r25,Y+2
	sbiw r24,0
	breq .L11
	ldd r24,Y+1
	ldd r25,Y+2
	ldd r18,Y+5
	ldd r19,Y+6
	ldd r20,Y+7
	ldd r21,Y+8
	movw r22,r18
	call print_ipaddr
	std Y+10,r25
	std Y+9,r24
	rjmp .L12
.L11:
	ldd r24,Y+3
	ldd r25,Y+4
	ldi r22,lo8(0)
	ldi r23,hi8(0)
	call resolv_query
	ldi r18,lo8(__c.2131)
	ldi r19,hi8(__c.2131)
	rcall .
	rcall .
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	ldd r24,Y+5
	ldd r25,Y+6
	std Z+1,r25
	st Z,r24
	ldd r24,Y+7
	ldd r25,Y+8
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
	std Y+10,r25
	std Y+9,r24
.L12:
	ldd r24,Y+9
	ldd r25,Y+10
/* epilogue start */
	adiw r28,10
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	parse_cmd_nslookup, .-parse_cmd_nslookup
	.comm rfm12_status,2,1
.global __do_clear_bss
