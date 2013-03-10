	.file	"enc28j60_process.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.section	.progmem.data,"a",@progbits
	.type	__c.2252, @object
	.size	__c.2252, 25
__c.2252:
	.string	"D: net: transmit error!\n"
	.type	__c.2250, @object
	.size	__c.2250, 24
__c.2250:
	.string	"D: net: receive error!\n"
	.type	__c.2247, @object
	.size	__c.2247, 32
__c.2247:
	.string	"D: net: packet transmit failed\n"
	.type	__c.2244, @object
	.size	__c.2244, 18
__c.2244:
	.string	"D: net: no link!\n"
	.type	__c.2242, @object
	.size	__c.2242, 19
__c.2242:
	.string	"D: net: got link!\n"
	.text
.global	network_process
	.type	network_process, @function
network_process:
	push r29
	push r28
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
	ldi r24,lo8(57)
	call read_control_register
	std Y+4,r24
	ldd r24,Y+4
	tst r24
	brne .+2
	rjmp .L11
	ldi r24,lo8(28)
	call read_control_register
	std Y+3,r24
	ldi r24,lo8(27)
	ldi r22,lo8(-128)
	ldi r20,lo8(-96)
	call bit_field_modify
	ldd r24,Y+3
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(16)
	andi r25,hi8(16)
	sbiw r24,0
	breq .L3
	ldi r24,lo8(19)
	call read_phy
	ldi r24,lo8(17)
	call read_phy
	andi r24,lo8(1024)
	andi r25,hi8(1024)
	std Y+2,__zero_reg__
	sbiw r24,0
	breq .L4
	ldi r24,lo8(1)
	std Y+2,r24
.L4:
	ldd r24,Y+2
	tst r24
	breq .L5
	ldi r24,lo8(__c.2242)
	ldi r25,hi8(__c.2242)
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
	ldi r24,lo8(__c.2244)
	ldi r25,hi8(__c.2244)
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
	ldd r24,Y+3
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(8)
	andi r25,hi8(8)
	sbiw r24,0
	breq .L6
	ldi r24,lo8(29)
	call read_control_register
	std Y+1,r24
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(2)
	andi r25,hi8(2)
	sbiw r24,0
	breq .L7
	ldi r24,lo8(__c.2247)
	ldi r25,hi8(__c.2247)
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r25
	st Z,r24
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
.L7:
	ldi r24,lo8(28)
	ldi r22,lo8(8)
	ldi r20,lo8(-96)
	call bit_field_modify
	ldi r24,lo8(29)
	ldi r22,lo8(10)
	ldi r20,lo8(-96)
	call bit_field_modify
.L6:
	ldd r24,Y+3
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(64)
	andi r25,hi8(64)
	sbiw r24,0
	breq .L8
	call uip_buf_lock
	tst r24
	breq .+2
	rjmp .L11
	call process_packet
	lds r24,rfm12_status
	lds r25,(rfm12_status)+1
	cpi r24,3
	cpc r25,__zero_reg__
	brsh .L8
	sts _uip_buf_lock,__zero_reg__
.L8:
	ldd r24,Y+3
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(1)
	andi r25,hi8(1)
	tst r24
	breq .L9
	ldi r24,lo8(__c.2250)
	ldi r25,hi8(__c.2250)
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r25
	st Z,r24
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
	ldi r24,lo8(28)
	ldi r22,lo8(1)
	ldi r20,lo8(-96)
	call bit_field_modify
	call init_enc28j60
.L9:
	ldd r24,Y+3
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(2)
	andi r25,hi8(2)
	sbiw r24,0
	breq .L10
	ldi r24,lo8(__c.2252)
	ldi r25,hi8(__c.2252)
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r25
	st Z,r24
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
	ldi r24,lo8(28)
	ldi r22,lo8(2)
	ldi r20,lo8(-96)
	call bit_field_modify
.L10:
	ldi r24,lo8(27)
	ldi r22,lo8(-128)
	ldi r20,lo8(-128)
	call bit_field_modify
.L11:
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	network_process, .-network_process
	.type	uip_buf_lock, @function
uip_buf_lock:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	std Y+2,__zero_reg__
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ld r24,Z
	std Y+1,r24
/* #APP */
 ;  1657 "./protocols/uip/uip.h" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	lds r24,_uip_buf_lock
	tst r24
	breq .L13
	ldi r24,lo8(1)
	std Y+2,r24
	rjmp .L14
.L13:
	ldi r24,lo8(8)
	sts _uip_buf_lock,r24
.L14:
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ldd r24,Y+1
	st Z,r24
	ldd r24,Y+2
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	uip_buf_lock, .-uip_buf_lock
	.section	.progmem.data
	.type	__c.2302, @object
	.size	__c.2302, 66
__c.2302:
	.ascii	"D"
	.string	": net: packet too large or too small for an ethernet header: %d\n"
	.text
.global	process_packet
	.type	process_packet, @function
process_packet:
	push r16
	push r17
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
	ldi r24,lo8(57)
	call read_control_register
	tst r24
	brne .+2
	rjmp .L31
	lds r24,enc28j60_next_packet_pointer
	lds r25,(enc28j60_next_packet_pointer)+1
	call set_read_buffer_pointer
	call read_buffer_memory
	mov r16,r24
	ldi r17,lo8(0)
	call read_buffer_memory
	mov r24,r24
	ldi r25,lo8(0)
	mov r25,r24
	clr r24
	or r24,r16
	or r25,r17
	sts (enc28j60_next_packet_pointer)+1,r25
	sts enc28j60_next_packet_pointer,r24
	movw r24,r28
	adiw r24,8
	std Y+7,r25
	std Y+6,r24
	std Y+3,__zero_reg__
	rjmp .L18
.L19:
	call read_buffer_memory
	ldd r30,Y+6
	ldd r31,Y+7
	st Z,r24
	ldd r24,Y+6
	ldd r25,Y+7
	adiw r24,1
	std Y+7,r25
	std Y+6,r24
	ldd r24,Y+3
	subi r24,lo8(-(1))
	std Y+3,r24
.L18:
	ldd r24,Y+3
	cpi r24,lo8(4)
	brlo .L19
	ldd r24,Y+8
	ldd r25,Y+9
	sbiw r24,4
	std Y+9,r25
	std Y+8,r24
	ldd r24,Y+8
	ldd r25,Y+9
	ldi r18,hi8(1501)
	cpi r24,lo8(1501)
	cpc r25,r18
	brsh .L20
	ldd r24,Y+8
	ldd r25,Y+9
	cpi r24,14
	cpc r25,__zero_reg__
	brlo .L20
	ldd r24,Y+8
	ldd r25,Y+9
	ldi r18,hi8(1501)
	cpi r24,lo8(1501)
	cpc r25,r18
	brlo .L21
.L20:
	ldi r24,lo8(__c.2302)
	ldi r25,hi8(__c.2302)
	ldd r18,Y+8
	ldd r19,Y+9
	rcall .
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r25
	st Z,r24
	std Z+3,r19
	std Z+2,r18
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	call init_enc28j60
	rjmp .L31
.L21:
	ldi r24,lo8(uip_buf)
	ldi r25,hi8(uip_buf)
	std Y+7,r25
	std Y+6,r24
	std Y+2,__zero_reg__
	std Y+1,__zero_reg__
	rjmp .L22
.L23:
	call read_buffer_memory
	ldd r30,Y+6
	ldd r31,Y+7
	st Z,r24
	ldd r24,Y+6
	ldd r25,Y+7
	adiw r24,1
	std Y+7,r25
	std Y+6,r24
	ldd r24,Y+1
	ldd r25,Y+2
	adiw r24,1
	std Y+2,r25
	std Y+1,r24
.L22:
	ldd r18,Y+8
	ldd r19,Y+9
	ldd r24,Y+1
	ldd r25,Y+2
	cp r24,r18
	cpc r25,r19
	brlo .L23
	ldd r24,Y+8
	ldd r25,Y+9
	sts (uip_len)+1,r25
	sts uip_len,r24
	ldi r24,lo8(uip_stacks+4)
	ldi r25,hi8(uip_stacks+4)
	sts (uip_stack)+1,r25
	sts uip_stack,r24
	ldi r24,lo8(uip_buf)
	ldi r25,hi8(uip_buf)
	std Y+5,r25
	std Y+4,r24
	ldd r30,Y+4
	ldd r31,Y+5
	ldd r24,Z+12
	ldd r25,Z+13
	std Y+13,r24
	std Y+12,r25
	ldd r24,Y+12
	ldd r25,Y+13
	ldi r18,hi8(2048)
	cpi r24,lo8(2048)
	cpc r25,r18
	breq .L25
	ldd r24,Y+12
	ldd r25,Y+13
	ldi r18,hi8(2054)
	cpi r24,lo8(2054)
	cpc r25,r18
	brne .L24
.L26:
	call uip_arp_arpin
	lds r24,uip_len
	lds r25,(uip_len)+1
	sbiw r24,0
	breq .L24
	call transmit_packet
	rjmp .L24
.L25:
	call uip_arp_ipin
	ldi r24,lo8(1)
	call router_input
	lds r24,uip_len
	lds r25,(uip_len)+1
	sbiw r24,0
	breq .L24
	call router_output
.L24:
	lds r24,enc28j60_next_packet_pointer
	lds r25,(enc28j60_next_packet_pointer)+1
	sbiw r24,1
	tst r25
	brlt .L28
	lds r24,enc28j60_next_packet_pointer
	lds r25,(enc28j60_next_packet_pointer)+1
	sbiw r24,1
	ldi r18,hi8(4096)
	cpi r24,lo8(4096)
	cpc r25,r18
	brlt .L29
.L28:
	ldi r24,lo8(12)
	ldi r22,lo8(-1)
	call write_control_register
	ldi r24,lo8(13)
	ldi r22,lo8(15)
	call write_control_register
	rjmp .L30
.L29:
	lds r24,enc28j60_next_packet_pointer
	lds r25,(enc28j60_next_packet_pointer)+1
	mov r25,r24
	subi r25,lo8(-(-1))
	ldi r24,lo8(12)
	mov r22,r25
	call write_control_register
	lds r24,enc28j60_next_packet_pointer
	lds r25,(enc28j60_next_packet_pointer)+1
	sbiw r24,1
	mov r24,r25
	lsl r25
	sbc r25,r25
	mov r25,r24
	ldi r24,lo8(13)
	mov r22,r25
	call write_control_register
.L30:
	ldi r24,lo8(30)
	ldi r22,lo8(64)
	ldi r20,lo8(-128)
	call bit_field_modify
.L31:
/* epilogue start */
	adiw r28,13
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
	.size	process_packet, .-process_packet
	.comm rfm12_status,2,1
.global __do_clear_bss
