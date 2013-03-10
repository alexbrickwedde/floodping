	.file	"ethernet_config.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.section	.progmem.data,"a",@progbits
	.type	__c.2057, @object
	.size	__c.2057, 7
__c.2057:
	.string	""
	.string	"\"\371\001\fe"
	.text
.global	network_config_load
	.type	network_config_load, @function
network_config_load:
	push r29
	push r28
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
	ldi r18,lo8(__c.2057)
	ldi r19,hi8(__c.2057)
	ldi r24,lo8(uip_ethaddr)
	ldi r25,hi8(uip_ethaddr)
	movw r22,r18
	ldi r20,lo8(6)
	ldi r21,hi8(6)
	call memcpy_P
	ldi r24,lo8(266)
	ldi r25,hi8(266)
	std Y+2,r25
	std Y+1,r24
	movw r30,r28
	adiw r30,3
	ldi r24,lo8(-11776)
	ldi r25,hi8(-11776)
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
	ldi r24,lo8(255)
	ldi r25,hi8(255)
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
	st X+,r24
	st X,r25
	ldi r24,lo8(266)
	ldi r25,hi8(266)
	std Y+2,r25
	std Y+1,r24
	movw r30,r28
	adiw r30,3
	ldi r24,lo8(256)
	ldi r25,hi8(256)
	std Z+1,r25
	st Z,r24
	ldd r24,Y+1
	ldd r25,Y+2
	sts (uip_draddr)+1,r25
	sts uip_draddr,r24
	ldi r26,lo8(uip_draddr+2)
	ldi r27,hi8(uip_draddr+2)
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
	.size	network_config_load, .-network_config_load
	.comm rfm12_status,2,1
.global __do_clear_bss
