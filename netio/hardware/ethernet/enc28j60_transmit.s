	.file	"enc28j60_transmit.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.section	.progmem.data,"a",@progbits
	.type	__c.2233, @object
	.size	__c.2233, 55
__c.2233:
	.string	"D: net: timeout waiting for TXRTS, aborting transmit!\n"
	.text
.global	transmit_packet
	.type	transmit_packet, @function
transmit_packet:
	push r29
	push r28
	rcall .
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 6 */
	ldi r24,lo8(100)
	std Y+5,r24
.L4:
	ldi r24,lo8(31)
	call read_control_register
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(8)
	andi r25,hi8(8)
	sbiw r24,0
	breq .L2
	ldd r24,Y+5
	std Y+6,r24
	ldd r24,Y+6
	tst r24
	breq .L3
	ldi r24,lo8(1)
	std Y+6,r24
.L3:
	ldd r24,Y+6
	ldd r25,Y+5
	subi r25,lo8(-(-1))
	std Y+5,r25
	tst r24
	brne .L4
.L2:
	ldd r24,Y+5
	tst r24
	brne .L5
	ldi r24,lo8(__c.2233)
	ldi r25,hi8(__c.2233)
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r25
	st Z,r24
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
	rjmp .L9
.L5:
	ldi r24,lo8(4096)
	ldi r25,hi8(4096)
	std Y+4,r25
	std Y+3,r24
	ldd r25,Y+3
	ldi r24,lo8(4)
	mov r22,r25
	call write_control_register
	ldd r24,Y+3
	ldd r25,Y+4
	mov r24,r25
	clr r25
	mov r25,r24
	ldi r24,lo8(5)
	mov r22,r25
	call write_control_register
	ldd r18,Y+3
	lds r24,uip_len
	lds r25,(uip_len)+1
	mov r25,r18
	add r25,r24
	ldi r24,lo8(6)
	mov r22,r25
	call write_control_register
	lds r18,uip_len
	lds r19,(uip_len)+1
	ldd r24,Y+3
	ldd r25,Y+4
	add r24,r18
	adc r25,r19
	mov r24,r25
	clr r25
	mov r25,r24
	ldi r24,lo8(7)
	mov r22,r25
	call write_control_register
	ldd r24,Y+3
	ldd r25,Y+4
	call set_write_buffer_pointer
	ldi r24,lo8(0)
	call write_buffer_memory
	std Y+2,__zero_reg__
	std Y+1,__zero_reg__
	rjmp .L7
.L8:
	ldd r24,Y+1
	ldd r25,Y+2
	movw r30,r24
	subi r30,lo8(-(uip_buf))
	sbci r31,hi8(-(uip_buf))
	ld r24,Z
	call write_buffer_memory
	ldd r24,Y+1
	ldd r25,Y+2
	adiw r24,1
	std Y+2,r25
	std Y+1,r24
.L7:
	lds r18,uip_len
	lds r19,(uip_len)+1
	ldd r24,Y+1
	ldd r25,Y+2
	cp r24,r18
	cpc r25,r19
	brlo .L8
	ldi r24,lo8(31)
	ldi r22,lo8(-128)
	ldi r20,lo8(-128)
	call bit_field_modify
	ldi r24,lo8(31)
	ldi r22,lo8(-128)
	ldi r20,lo8(-96)
	call bit_field_modify
	ldi r24,lo8(31)
	ldi r22,lo8(8)
	ldi r20,lo8(-128)
	call bit_field_modify
.L9:
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
	.size	transmit_packet, .-transmit_packet
	.comm rfm12_status,2,1
.global __do_clear_bss
