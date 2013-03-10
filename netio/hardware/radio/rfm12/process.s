	.file	"process.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	rfm12_process
	.type	rfm12_process, @function
rfm12_process:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	call rfm12_rxfinish
	sts (uip_len)+1,r25
	sts uip_len,r24
	lds r24,uip_len
	lds r25,(uip_len)+1
	sbiw r24,0
	breq .L5
	lds r24,uip_len
	lds r25,(uip_len)+1
	adiw r24,14
	sts (uip_len)+1,r25
	sts uip_len,r24
	call rfm12_rxstart
	ldi r24,lo8(0)
	call router_input
	lds r24,uip_len
	lds r25,(uip_len)+1
	sbiw r24,0
	brne .L3
	lds r24,rfm12_status
	lds r25,(rfm12_status)+1
	cpi r24,3
	cpc r25,__zero_reg__
	brsh .L5
	sts _uip_buf_lock,__zero_reg__
	rjmp .L5
.L3:
	call router_output
.L5:
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	rfm12_process, .-rfm12_process
	.comm rfm12_status,2,1
.global __do_clear_bss
