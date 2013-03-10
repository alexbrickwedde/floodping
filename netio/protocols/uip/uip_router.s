	.file	"uip_router.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	router_find_stack
	.type	router_find_stack, @function
router_find_stack:
	push r29
	push r28
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
	std Y+3,r25
	std Y+2,r24
.L2:
	std Y+1,__zero_reg__
	rjmp .L3
.L7:
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(uip_stacks))
	sbci r25,hi8(-(uip_stacks))
	sts (uip_stack)+1,r25
	sts uip_stack,r24
	ldd r24,Y+2
	ldd r25,Y+3
	sbiw r24,0
	brne .L4
	ldi r30,lo8(uip_buf+30)
	ldi r31,hi8(uip_buf+30)
	ld r18,Z
	ldd r19,Z+1
	lds r30,uip_stack
	lds r31,(uip_stack)+1
	ld __tmp_reg__,Z+
	ld r31,Z
	mov r30,__tmp_reg__
	ld r24,Z
	ldd r25,Z+1
	cp r18,r24
	cpc r19,r25
	brne .L4
	ldi r30,lo8(uip_buf+32)
	ldi r31,hi8(uip_buf+32)
	ld r18,Z
	ldd r19,Z+1
	lds r30,uip_stack
	lds r31,(uip_stack)+1
	ld r24,Z
	ldd r25,Z+1
	movw r30,r24
	adiw r30,2
	ld r24,Z
	ldd r25,Z+1
	cp r18,r24
	cpc r19,r25
	brne .L4
	ldd r18,Y+1
	std Y+4,r18
	rjmp .L5
.L4:
	ldd r24,Y+2
	ldd r25,Y+3
	sbiw r24,0
	brne .+2
	rjmp .L6
	ldd r30,Y+2
	ldd r31,Y+3
	ld r18,Z
	ldd r19,Z+1
	lds r30,uip_stack
	lds r31,(uip_stack)+1
	ld __tmp_reg__,Z+
	ld r31,Z
	mov r30,__tmp_reg__
	ld r24,Z
	ldd r25,Z+1
	eor r18,r24
	eor r19,r25
	lds r30,uip_stack
	lds r31,(uip_stack)+1
	ldd __tmp_reg__,Z+2
	ldd r31,Z+3
	mov r30,__tmp_reg__
	ld r24,Z
	ldd r25,Z+1
	and r24,r18
	and r25,r19
	sbiw r24,0
	brne .L6
	ldd r24,Y+2
	ldd r25,Y+3
	movw r30,r24
	adiw r30,2
	ld r18,Z
	ldd r19,Z+1
	lds r30,uip_stack
	lds r31,(uip_stack)+1
	ld r24,Z
	ldd r25,Z+1
	movw r30,r24
	adiw r30,2
	ld r24,Z
	ldd r25,Z+1
	eor r18,r24
	eor r19,r25
	lds r30,uip_stack
	lds r31,(uip_stack)+1
	ldd r24,Z+2
	ldd r25,Z+3
	movw r30,r24
	adiw r30,2
	ld r24,Z
	ldd r25,Z+1
	and r24,r18
	and r25,r19
	sbiw r24,0
	brne .L6
	ldd r24,Y+1
	std Y+4,r24
	rjmp .L5
.L6:
	ldd r24,Y+1
	subi r24,lo8(-(1))
	std Y+1,r24
.L3:
	ldd r24,Y+1
	cpi r24,lo8(2)
	brsh .+2
	rjmp .L7
	ldd r24,Y+2
	ldd r25,Y+3
	sbiw r24,0
	breq .L8
	ldd r24,Y+2
	ldd r25,Y+3
	ldi r18,hi8(uip_draddr)
	cpi r24,lo8(uip_draddr)
	cpc r25,r18
	breq .L8
	ldi r24,lo8(uip_draddr)
	ldi r25,hi8(uip_draddr)
	std Y+3,r25
	std Y+2,r24
	rjmp .L2
.L8:
	ldi r24,lo8(-1)
	std Y+4,r24
.L5:
	ldd r24,Y+4
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	router_find_stack, .-router_find_stack
.global	router_input
	.type	router_input, @function
router_input:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	std Y+2,r24
	ldi r24,lo8(0)
	ldi r25,hi8(0)
	call router_find_stack
	std Y+1,r24
	ldd r24,Y+1
	cpi r24,lo8(-1)
	breq .L11
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(uip_stacks))
	sbci r25,hi8(-(uip_stacks))
	sts (uip_stack)+1,r25
	sts uip_stack,r24
	ldi r24,lo8(1)
	call uip_process
	rjmp .L13
.L11:
	sts (uip_len)+1,__zero_reg__
	sts uip_len,__zero_reg__
.L13:
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	router_input, .-router_input
.global	router_output
	.type	router_output, @function
router_output:
	push r29
	push r28
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 1 */
	ldi r24,lo8(uip_buf+30)
	ldi r25,hi8(uip_buf+30)
	call router_find_stack
	std Y+1,r24
	ldd r24,Y+1
	cpi r24,lo8(-1)
	brne .L15
	sts (uip_len)+1,__zero_reg__
	sts uip_len,__zero_reg__
	rjmp .L17
.L15:
	ldd r24,Y+1
	call router_output_to
.L17:
/* epilogue start */
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	router_output, .-router_output
.global	router_output_to
	.type	router_output_to, @function
router_output_to:
	push r29
	push r28
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
	std Y+2,r24
	std Y+1,__zero_reg__
	ldd r24,Y+2
	mov r24,r24
	ldi r25,lo8(0)
	lsl r24
	rol r25
	lsl r24
	rol r25
	subi r24,lo8(-(uip_stacks))
	sbci r25,hi8(-(uip_stacks))
	sts (uip_stack)+1,r25
	sts uip_stack,r24
	ldd r24,Y+2
	mov r18,r24
	ldi r19,lo8(0)
	std Y+4,r19
	std Y+3,r18
	ldd r24,Y+3
	ldd r25,Y+4
	sbiw r24,0
	breq .L20
	ldd r18,Y+3
	ldd r19,Y+4
	cpi r18,1
	cpc r19,__zero_reg__
	brne .L19
.L21:
	call enc28j60_txstart
	rjmp .L19
.L20:
	lds r24,uip_len
	lds r25,(uip_len)+1
	call rfm12_txstart
.L19:
	ldd r24,Y+1
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	router_output_to, .-router_output_to
	.type	enc28j60_txstart, @function
enc28j60_txstart:
	push r29
	push r28
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 1 */
	call uip_arp_out
	std Y+1,r24
	call transmit_packet
	ldd r24,Y+1
/* epilogue start */
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	enc28j60_txstart, .-enc28j60_txstart
	.comm rfm12_status,2,1
.global __do_clear_bss
