	.file	"ethersex.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
.global	jump_to_bootloader
	.data
	.type	jump_to_bootloader, @object
	.size	jump_to_bootloader, 2
jump_to_bootloader:
	.word	-8192
	.section	.progmem.data,"a",@progbits
	.type	__c.2817, @object
	.size	__c.2817, 27
__c.2817:
	.string	"D: mac: %x:%x:%x:%x:%x:%x\n"
	.type	__c.2815, @object
	.size	__c.2815, 27
__c.2815:
	.string	"D: enc28j60 revision 0x%x\n"
	.type	__c.2813, @object
	.size	__c.2813, 23
__c.2813:
	.string	"D: disabling watchdog\n"
	.type	__c.2811, @object
	.size	__c.2811, 19
__c.2811:
	.string	"D: reset: Unknown\n"
	.type	__c.2809, @object
	.size	__c.2809, 18
__c.2809:
	.string	"D: reset: Extern\n"
	.type	__c.2807, @object
	.size	__c.2807, 20
__c.2807:
	.string	"D: reset: Watchdog\n"
	.type	__c.2805, @object
	.size	__c.2805, 20
__c.2805:
	.string	"D: reset: Power on\n"
	.type	__c.2803, @object
	.size	__c.2803, 21
__c.2803:
	.string	"D: reset: Brown-out\n"
	.type	__c.2801, @object
	.size	__c.2801, 47
__c.2801:
	.string	"D: Ethersex Jun 30 2012 22:05:25 (Debug mode)\n"
	.text
.global	main
	.type	main, @function
main:
	push r14
	push r15
	push r16
	push r17
	push r29
	push r28
	rcall .
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
	std Y+3,__zero_reg__
	ldi r30,lo8(84)
	ldi r31,hi8(84)
	ld r24,Z
	std Y+3,r24
	ldi r30,lo8(84)
	ldi r31,hi8(84)
	st Z,__zero_reg__
	ldi r30,lo8(36)
	ldi r31,hi8(36)
	ldi r24,lo8(-80)
	st Z,r24
	ldi r30,lo8(39)
	ldi r31,hi8(39)
	ldi r24,lo8(4)
	st Z,r24
	call debug_init_uart
	ldi r24,lo8(__c.2801)
	ldi r25,hi8(__c.2801)
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r25
	st Z,r24
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
	movw r30,r28
	adiw r30,3
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(4)
	andi r25,hi8(4)
	sbiw r24,0
	breq .L2
	ldi r24,lo8(__c.2803)
	ldi r25,hi8(__c.2803)
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r25
	st Z,r24
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
	rjmp .L3
.L2:
	movw r30,r28
	adiw r30,3
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(1)
	andi r25,hi8(1)
	tst r24
	breq .L4
	ldi r24,lo8(__c.2805)
	ldi r25,hi8(__c.2805)
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r25
	st Z,r24
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
	rjmp .L3
.L4:
	movw r30,r28
	adiw r30,3
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(8)
	andi r25,hi8(8)
	sbiw r24,0
	breq .L5
	ldi r24,lo8(__c.2807)
	ldi r25,hi8(__c.2807)
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r25
	st Z,r24
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
	rjmp .L3
.L5:
	movw r30,r28
	adiw r30,3
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(2)
	andi r25,hi8(2)
	sbiw r24,0
	breq .L6
	ldi r24,lo8(__c.2809)
	ldi r25,hi8(__c.2809)
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r25
	st Z,r24
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
	rjmp .L3
.L6:
	ldi r24,lo8(__c.2811)
	ldi r25,hi8(__c.2811)
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r25
	st Z,r24
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
.L3:
/* #APP */
 ;  119 "ethersex.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
	ldi r24,lo8(__c.2813)
	ldi r25,hi8(__c.2813)
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r25
	st Z,r24
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
	ldi r24,lo8(24)
/* #APP */
 ;  136 "ethersex.c" 1
	in __tmp_reg__, __SREG__
	cli
	sts 96, r24
	sts 96, __zero_reg__
	out __SREG__,__tmp_reg__
	
 ;  0 "" 2
/* #NOAPP */
	call spi_init
	call ethersex_meta_init
	ldi r16,lo8(__c.2815)
	ldi r17,hi8(__c.2815)
	ldi r24,lo8(114)
	call read_control_register
	mov r24,r24
	ldi r25,lo8(0)
	rcall .
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r17
	st Z,r16
	std Z+3,r25
	std Z+2,r24
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	ldi r20,lo8(__c.2817)
	ldi r21,hi8(__c.2817)
	lds r24,uip_ethaddr
	mov r22,r24
	ldi r23,lo8(0)
	lds r24,uip_ethaddr+1
	mov r26,r24
	ldi r27,lo8(0)
	lds r24,uip_ethaddr+2
	mov r16,r24
	ldi r17,lo8(0)
	lds r24,uip_ethaddr+3
	mov r14,r24
	clr r15
	lds r24,uip_ethaddr+4
	mov r18,r24
	ldi r19,lo8(0)
	lds r24,uip_ethaddr+5
	mov r24,r24
	ldi r25,lo8(0)
	in r30,__SP_L__
	in r31,__SP_H__
	sbiw r30,14
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r31
	out __SREG__,__tmp_reg__
	out __SP_L__,r30
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r21
	st Z,r20
	std Z+3,r23
	std Z+2,r22
	std Z+5,r27
	std Z+4,r26
	std Z+7,r17
	std Z+6,r16
	std Z+9,r15
	std Z+8,r14
	std Z+11,r19
	std Z+10,r18
	std Z+13,r25
	std Z+12,r24
	call printf_P
	in r24,__SP_L__
	in r25,__SP_H__
	adiw r24,14
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r25
	out __SREG__,__tmp_reg__
	out __SP_L__,r24
	call ethersex_meta_startup
.L11:
	call ethersex_meta_mainloop
	lds r24,status
	andi r24,lo8(2)
	tst r24
	breq .L7
/* #APP */
 ;  202 "ethersex.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	lds r30,jump_to_bootloader
	lds r31,(jump_to_bootloader)+1
	icall
.L7:
	lds r24,status
	andi r24,lo8(8)
	tst r24
	breq .L8
/* #APP */
 ;  208 "ethersex.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	ldi r24,lo8(24)
	ldi r25,hi8(24)
	ldi r18,lo8(8)
/* #APP */
 ;  209 "ethersex.c" 1
	in __tmp_reg__,__SREG__
	cli
	wdr
	sts 96,r24
	out __SREG__,__tmp_reg__
	sts 96,r18
	
 ;  0 "" 2
/* #NOAPP */
.L9:
	rjmp .L9
.L8:
	lds r24,status
	andi r24,lo8(4)
	tst r24
	breq .L11
/* #APP */
 ;  215 "ethersex.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	std Y+2,__zero_reg__
	std Y+1,__zero_reg__
	ldd r30,Y+1
	ldd r31,Y+2
	icall
	rjmp .L11
	.size	main, .-main
	.comm rfm12_status,2,1
	.comm status,1,1
	.comm vfs_sd_rootnode,2,1
.global __do_copy_data
.global __do_clear_bss
