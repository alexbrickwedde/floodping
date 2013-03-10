	.file	"meta.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	ethersex_meta_init
	.type	ethersex_meta_init, @function
ethersex_meta_init:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	call network_init
	call periodic_init
	call rfm12_init
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	ethersex_meta_init, .-ethersex_meta_init
.global	ethersex_meta_netinit
	.type	ethersex_meta_netinit, @function
ethersex_meta_netinit:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	call init_enc28j60
	call resolv_init
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	ethersex_meta_netinit, .-ethersex_meta_netinit
.global	ethersex_meta_startup
	.type	ethersex_meta_startup, @function
ethersex_meta_startup:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	ethersex_meta_startup, .-ethersex_meta_startup
.global	ethersex_meta_mainloop
	.type	ethersex_meta_mainloop, @function
ethersex_meta_mainloop:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	call debug_process_uart
	call network_process
	call rfm12_int_process
	call rfm12_process
	call periodic_process
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	ethersex_meta_mainloop, .-ethersex_meta_mainloop
	.lcomm counter.2167,2
.global	periodic_process
	.type	periodic_process, @function
periodic_process:
	push r29
	push r28
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 1 */
	lds r24,newtick
	tst r24
	brne .+2
	rjmp .L21
	sts newtick,__zero_reg__
	lds r24,counter.2167
	lds r25,(counter.2167)+1
	adiw r24,1
	sts (counter.2167)+1,r25
	sts counter.2167,r24
	call uip_buf_lock
	tst r24
	breq .L11
	lds r24,_uip_buf_lock
	subi r24,lo8(-(-1))
	sts _uip_buf_lock,r24
	call uip_buf_lock
	tst r24
	breq .+2
	rjmp .L21
	sts (rfm12_status)+1,__zero_reg__
	sts rfm12_status,__zero_reg__
	call rfm12_rxstart
.L11:
	lds r24,counter.2167
	lds r25,(counter.2167)+1
	ldi r18,lo8(10)
	ldi r19,hi8(10)
	movw r22,r18
	call __udivmodhi4
	sbiw r24,0
	breq .+2
	rjmp .L12
	std Y+1,__zero_reg__
	rjmp .L13
.L15:
	ldd r24,Y+1
	mov r18,r24
	ldi r19,lo8(0)
	ldi r24,lo8(33)
	ldi r25,hi8(33)
	movw r20,r24
	mul r18,r20
	movw r24,r0
	mul r18,r21
	add r25,r0
	mul r19,r20
	add r25,r0
	clr r1
	movw r30,r24
	subi r30,lo8(-(uip_conns+32))
	sbci r31,hi8(-(uip_conns+32))
	ld r24,Z
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
	ldd r24,Y+1
	mov r18,r24
	ldi r19,lo8(0)
	ldi r24,lo8(33)
	ldi r25,hi8(33)
	movw r20,r24
	mul r18,r20
	movw r24,r0
	mul r18,r21
	add r25,r0
	mul r19,r20
	add r25,r0
	clr r1
	subi r24,lo8(-(uip_conns))
	sbci r25,hi8(-(uip_conns))
	sts (uip_conn)+1,r25
	sts uip_conn,r24
	ldi r24,lo8(2)
	call uip_process
	lds r24,uip_len
	lds r25,(uip_len)+1
	sbiw r24,0
	breq .L14
	call router_output
.L14:
	ldd r24,Y+1
	subi r24,lo8(-(1))
	std Y+1,r24
.L13:
	ldd r24,Y+1
	cpi r24,lo8(3)
	brsh .+2
	rjmp .L15
	std Y+1,__zero_reg__
	rjmp .L16
.L18:
	ldd r24,Y+1
	mov r20,r24
	ldi r21,lo8(0)
	movw r24,r20
	lsl r24
	rol r25
	movw r18,r24
	lsl r18
	rol r19
	lsl r18
	rol r19
	add r24,r18
	adc r25,r19
	add r24,r20
	adc r25,r21
	movw r30,r24
	subi r30,lo8(-(uip_udp_conns+10))
	sbci r31,hi8(-(uip_udp_conns+10))
	ld r24,Z
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
	ldd r24,Y+1
	mov r20,r24
	ldi r21,lo8(0)
	movw r24,r20
	lsl r24
	rol r25
	movw r18,r24
	lsl r18
	rol r19
	lsl r18
	rol r19
	add r24,r18
	adc r25,r19
	add r24,r20
	adc r25,r21
	subi r24,lo8(-(uip_udp_conns))
	sbci r25,hi8(-(uip_udp_conns))
	sts (uip_udp_conn)+1,r25
	sts uip_udp_conn,r24
	ldi r24,lo8(5)
	call uip_process
	lds r24,uip_len
	lds r25,(uip_len)+1
	sbiw r24,0
	breq .L17
	call router_output
.L17:
	ldd r24,Y+1
	subi r24,lo8(-(1))
	std Y+1,r24
.L16:
	ldd r24,Y+1
	cpi r24,lo8(5)
	brsh .+2
	rjmp .L18
.L12:
	lds r24,counter.2167
	lds r25,(counter.2167)+1
	ldi r18,lo8(50)
	ldi r19,hi8(50)
	movw r22,r18
	call __udivmodhi4
	sbiw r24,0
	brne .L19
	call enc28j60_periodic
.L19:
	lds r24,counter.2167
	lds r25,(counter.2167)+1
	ldi r18,lo8(500)
	ldi r19,hi8(500)
	movw r22,r18
	call __udivmodhi4
	sbiw r24,0
	brne .L20
	sts (counter.2167)+1,__zero_reg__
	sts counter.2167,__zero_reg__
	call uip_arp_timer
.L20:
	lds r24,rfm12_status
	lds r25,(rfm12_status)+1
	cpi r24,3
	cpc r25,__zero_reg__
	brsh .L21
	sts _uip_buf_lock,__zero_reg__
.L21:
/* epilogue start */
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	periodic_process, .-periodic_process
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
 ;  1657 "protocols/uip/uip.h" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	lds r24,_uip_buf_lock
	tst r24
	breq .L23
	ldi r24,lo8(1)
	std Y+2,r24
	rjmp .L24
.L23:
	ldi r24,lo8(8)
	sts _uip_buf_lock,r24
.L24:
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
	.comm newtick,1,1
	.comm rfm12_status,2,1
.global __do_clear_bss
