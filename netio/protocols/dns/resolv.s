	.file	"resolv.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.lcomm resolv_conn,2
	.text
	.type	parse_name, @function
parse_name:
	push r29
	push r28
	rcall .
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
	std Y+3,r25
	std Y+2,r24
.L5:
	ldd r30,Y+2
	ldd r31,Y+3
	ld r24,Z
	std Y+1,r24
	ldd r24,Y+2
	ldd r25,Y+3
	adiw r24,1
	std Y+3,r25
	std Y+2,r24
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(192)
	andi r25,hi8(192)
	sbiw r24,0
	brne .L2
	rjmp .L3
.L4:
	ldd r24,Y+2
	ldd r25,Y+3
	adiw r24,1
	std Y+3,r25
	std Y+2,r24
	ldd r24,Y+1
	subi r24,lo8(-(-1))
	std Y+1,r24
.L3:
	ldd r24,Y+1
	tst r24
	brne .L4
	ldd r30,Y+2
	ldd r31,Y+3
	ld r24,Z
	tst r24
	brne .L5
.L2:
	ldd r24,Y+2
	ldd r25,Y+3
	adiw r24,1
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	parse_name, .-parse_name
	.section	.progmem.data,"a",@progbits
	.type	endquery.2147, @object
	.size	endquery.2147, 5
endquery.2147:
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.lcomm n.2139,1
	.lcomm i.2138,1
	.text
.global	resolv_periodic
	.type	resolv_periodic, @function
resolv_periodic:
	push r16
	push r17
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
	sts i.2138,__zero_reg__
	rjmp .L8
.L20:
	lds r24,i.2138
	mov r18,r24
	ldi r19,lo8(0)
	ldi r24,lo8(43)
	ldi r25,hi8(43)
	movw r20,r24
	mul r18,r20
	movw r24,r0
	mul r18,r21
	add r25,r0
	mul r19,r20
	add r25,r0
	clr r1
	movw r26,r24
	subi r26,lo8(-(names))
	sbci r27,hi8(-(names))
	std Y+8,r27
	std Y+7,r26
	ldd r30,Y+7
	ldd r31,Y+8
	ld r24,Z
	cpi r24,lo8(1)
	breq .L9
	ldd r26,Y+7
	ldd r27,Y+8
	ld r24,X
	cpi r24,lo8(2)
	breq .+2
	rjmp .L10
.L9:
	ldd r30,Y+7
	ldd r31,Y+8
	ld r24,Z
	cpi r24,lo8(2)
	breq .+2
	rjmp .L11
	ldd r26,Y+7
	ldd r27,Y+8
	adiw r26,1
	ld r24,X
	subi r24,lo8(-(-1))
	ldd r30,Y+7
	ldd r31,Y+8
	std Z+1,r24
	ldd r26,Y+7
	ldd r27,Y+8
	adiw r26,1
	ld r24,X
	sbiw r26,1
	tst r24
	breq .+2
	rjmp .L10
	ldd r30,Y+7
	ldd r31,Y+8
	ldd r24,Z+2
	subi r24,lo8(-(1))
	ldd r26,Y+7
	ldd r27,Y+8
	adiw r26,2
	st X,r24
	sbiw r26,2
	ldd r30,Y+7
	ldd r31,Y+8
	ldd r24,Z+2
	cpi r24,lo8(8)
	brne .L12
	ldi r24,lo8(4)
	ldd r26,Y+7
	ldd r27,Y+8
	st X,r24
	ldd r30,Y+7
	ldd r31,Y+8
	ldd r24,Z+41
	ldd r25,Z+42
	sbiw r24,0
	brne .+2
	rjmp .L10
	ldd r26,Y+7
	ldd r27,Y+8
	adiw r26,41
	ld r30,X+
	ld r31,X
	sbiw r26,41+1
	ldd r24,Y+7
	ldd r25,Y+8
	adiw r24,5
	ldi r22,lo8(0)
	ldi r23,hi8(0)
	icall
	rjmp .L10
.L12:
	ldd r30,Y+7
	ldd r31,Y+8
	ldd r24,Z+2
	ldd r26,Y+7
	ldd r27,Y+8
	adiw r26,1
	st X,r24
	sbiw r26,1
	rjmp .L14
.L11:
	ldi r24,lo8(2)
	ldd r30,Y+7
	ldd r31,Y+8
	st Z,r24
	ldi r24,lo8(1)
	ldd r26,Y+7
	ldd r27,Y+8
	adiw r26,1
	st X,r24
	ldd r30,Y+7
	ldd r31,Y+8
	std Z+2,__zero_reg__
.L14:
	lds r24,uip_appdata
	lds r25,(uip_appdata)+1
	movw r16,r24
	movw r24,r16
	ldi r22,lo8(0)
	ldi r23,hi8(0)
	ldi r20,lo8(12)
	ldi r21,hi8(12)
	call memset
	lds r24,i.2138
	mov r24,r24
	ldi r25,lo8(0)
	std Y+10,r24
	std Y+9,r25
	ldd r30,Y+9
	ldd r31,Y+10
	movw r26,r16
	st X+,r30
	st X,r31
	ldi r24,lo8(1)
	movw r26,r16
	adiw r26,2
	st X,r24
	ldi r24,lo8(16)
	movw r30,r16
	std Z+3,r24
	ldi r24,lo8(256)
	ldi r25,hi8(256)
	movw r26,r16
	adiw r26,4+1
	st X,r25
	st -X,r24
	sbiw r26,4
	lds r24,uip_appdata
	lds r25,(uip_appdata)+1
	adiw r24,12
	std Y+6,r25
	std Y+5,r24
	ldd r24,Y+7
	ldd r25,Y+8
	adiw r24,5
	std Y+2,r25
	std Y+1,r24
	ldd r24,Y+1
	ldd r25,Y+2
	sbiw r24,1
	std Y+2,r25
	std Y+1,r24
.L18:
	ldd r24,Y+1
	ldd r25,Y+2
	adiw r24,1
	std Y+2,r25
	std Y+1,r24
	ldd r24,Y+5
	ldd r25,Y+6
	std Y+4,r25
	std Y+3,r24
	ldd r24,Y+5
	ldd r25,Y+6
	adiw r24,1
	std Y+6,r25
	std Y+5,r24
	sts n.2139,__zero_reg__
	rjmp .L15
.L17:
	ldd r30,Y+1
	ldd r31,Y+2
	ld r24,Z
	ldd r30,Y+5
	ldd r31,Y+6
	st Z,r24
	ldd r24,Y+5
	ldd r25,Y+6
	adiw r24,1
	std Y+6,r25
	std Y+5,r24
	lds r24,n.2139
	subi r24,lo8(-(1))
	sts n.2139,r24
	ldd r24,Y+1
	ldd r25,Y+2
	adiw r24,1
	std Y+2,r25
	std Y+1,r24
.L15:
	ldd r30,Y+1
	ldd r31,Y+2
	ld r24,Z
	cpi r24,lo8(46)
	breq .L16
	ldd r30,Y+1
	ldd r31,Y+2
	ld r24,Z
	tst r24
	brne .L17
.L16:
	lds r24,n.2139
	ldd r30,Y+3
	ldd r31,Y+4
	st Z,r24
	ldd r30,Y+1
	ldd r31,Y+2
	ld r24,Z
	tst r24
	brne .L18
	ldd r24,Y+5
	ldd r25,Y+6
	ldi r18,lo8(endquery.2147)
	ldi r19,hi8(endquery.2147)
	movw r22,r18
	ldi r20,lo8(5)
	ldi r21,hi8(5)
	call memcpy_P
	lds r20,uip_appdata
	lds r21,(uip_appdata)+1
	ldd r24,Y+5
	ldd r25,Y+6
	adiw r24,5
	mov r18,r24
	lds r24,uip_appdata
	lds r25,(uip_appdata)+1
	mov r27,r18
	sub r27,r24
	mov r24,r27
	mov r18,r24
	ldi r19,lo8(0)
	movw r24,r20
	movw r22,r18
	call uip_send
	rjmp .L21
.L10:
	lds r24,i.2138
	subi r24,lo8(-(1))
	sts i.2138,r24
.L8:
	lds r24,i.2138
	cpi r24,lo8(4)
	brsh .+2
	rjmp .L20
.L21:
/* epilogue start */
	adiw r28,10
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
	.size	resolv_periodic, .-resolv_periodic
	.lcomm i.2213,1
	.lcomm nanswers.2212,1
	.lcomm nquestions.2211,1
.global	resolv_newdata
	.type	resolv_newdata, @function
resolv_newdata:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,14
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 14 */
	lds r24,uip_appdata
	lds r25,(uip_appdata)+1
	std Y+2,r25
	std Y+1,r24
	ldd r30,Y+1
	ldd r31,Y+2
	ld r18,Z
	ldd r19,Z+1
	mov r25,r18
	mov r24,r19
	sts i.2213,r24
	lds r24,i.2213
	mov r18,r24
	ldi r19,lo8(0)
	ldi r24,lo8(43)
	ldi r25,hi8(43)
	movw r20,r24
	mul r18,r20
	movw r24,r0
	mul r18,r21
	add r25,r0
	mul r19,r20
	add r25,r0
	clr r1
	movw r26,r24
	subi r26,lo8(-(names))
	sbci r27,hi8(-(names))
	std Y+8,r27
	std Y+7,r26
	lds r24,i.2213
	cpi r24,lo8(4)
	brlo .+2
	rjmp .L33
	ldd r30,Y+7
	ldd r31,Y+8
	ld r24,Z
	cpi r24,lo8(2)
	breq .+2
	rjmp .L33
	ldi r24,lo8(3)
	ldd r26,Y+7
	ldd r27,Y+8
	st X,r24
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+3
	andi r24,lo8(15)
	ldd r30,Y+7
	ldd r31,Y+8
	std Z+4,r24
	ldd r26,Y+7
	ldd r27,Y+8
	adiw r26,4
	ld r24,X
	sbiw r26,4
	tst r24
	brne .L24
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	ldd r25,Z+7
	sbiw r24,0
	brne .L25
.L24:
	ldi r24,lo8(4)
	ldd r30,Y+7
	ldd r31,Y+8
	st Z,r24
	ldd r26,Y+7
	ldd r27,Y+8
	adiw r26,41
	ld r24,X+
	ld r25,X
	sbiw r26,41+1
	sbiw r24,0
	brne .+2
	rjmp .L33
	ldd r26,Y+7
	ldd r27,Y+8
	adiw r26,41
	ld r30,X+
	ld r31,X
	sbiw r26,41+1
	ldd r24,Y+7
	ldd r25,Y+8
	adiw r24,5
	ldi r22,lo8(0)
	ldi r23,hi8(0)
	icall
	rjmp .L33
.L25:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+4
	ldd r25,Z+5
	std Y+14,r24
	std Y+13,r25
	ldd r24,Y+13
	sts nquestions.2211,r24
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	ldd r25,Z+7
	std Y+12,r24
	std Y+11,r25
	ldd r24,Y+11
	sts nanswers.2212,r24
	lds r24,uip_appdata
	lds r25,(uip_appdata)+1
	adiw r24,12
	call parse_name
	adiw r24,4
	std Y+6,r25
	std Y+5,r24
	rjmp .L27
.L32:
	ldd r30,Y+5
	ldd r31,Y+6
	ld r24,Z
	clr r25
	sbrc r24,7
	com r25
	andi r24,lo8(192)
	andi r25,hi8(192)
	sbiw r24,0
	breq .L28
	ldd r24,Y+5
	ldd r25,Y+6
	adiw r24,2
	std Y+6,r25
	std Y+5,r24
	rjmp .L29
.L28:
	ldd r24,Y+5
	ldd r25,Y+6
	call parse_name
	std Y+6,r25
	std Y+5,r24
.L29:
	ldd r24,Y+5
	ldd r25,Y+6
	std Y+4,r25
	std Y+3,r24
	ldd r30,Y+3
	ldd r31,Y+4
	ld r24,Z
	ldd r25,Z+1
	ldi r27,hi8(256)
	cpi r24,lo8(256)
	cpc r25,r27
	brne .L30
	ldd r30,Y+3
	ldd r31,Y+4
	ldd r24,Z+2
	ldd r25,Z+3
	ldi r30,hi8(256)
	cpi r24,lo8(256)
	cpc r25,r30
	brne .L30
	ldd r30,Y+3
	ldd r31,Y+4
	ldd r24,Z+8
	ldd r25,Z+9
	ldi r31,hi8(1024)
	cpi r24,lo8(1024)
	cpc r25,r31
	brne .L30
	ldd r30,Y+3
	ldd r31,Y+4
	ldd r24,Z+10
	ldd r25,Z+11
	ldd r26,Y+7
	ldd r27,Y+8
	adiw r26,37+1
	st X,r25
	st -X,r24
	sbiw r26,37
	ldd r30,Y+3
	ldd r31,Y+4
	ldd r24,Z+12
	ldd r25,Z+13
	ldd r30,Y+7
	ldd r31,Y+8
	std Z+40,r25
	std Z+39,r24
	ldd r26,Y+7
	ldd r27,Y+8
	adiw r26,41
	ld r24,X+
	ld r25,X
	sbiw r26,41+1
	sbiw r24,0
	breq .L33
	ldd r26,Y+7
	ldd r27,Y+8
	adiw r26,41
	ld r30,X+
	ld r31,X
	sbiw r26,41+1
	ldd r24,Y+7
	ldd r25,Y+8
	adiw r24,5
	ldd r18,Y+7
	ldd r19,Y+8
	subi r18,lo8(-(37))
	sbci r19,hi8(-(37))
	movw r22,r18
	icall
	rjmp .L33
.L30:
	ldd r30,Y+3
	ldd r31,Y+4
	ldd r24,Z+8
	ldd r25,Z+9
	std Y+10,r24
	std Y+9,r25
	ldd r18,Y+9
	ldd r19,Y+10
	subi r18,lo8(-(10))
	sbci r19,hi8(-(10))
	ldd r24,Y+5
	ldd r25,Y+6
	add r24,r18
	adc r25,r19
	std Y+6,r25
	std Y+5,r24
	lds r24,nanswers.2212
	subi r24,lo8(-(-1))
	sts nanswers.2212,r24
.L27:
	lds r24,nanswers.2212
	tst r24
	breq .+2
	rjmp .L32
.L33:
/* epilogue start */
	adiw r28,14
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	resolv_newdata, .-resolv_newdata
	.lcomm lseqi.2290,1
	.lcomm lseq.2289,1
	.lcomm i.2288,1
.global	resolv_query
	.type	resolv_query, @function
resolv_query:
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
	std Y+6,__zero_reg__
	std Y+5,__zero_reg__
	sts lseqi.2290,__zero_reg__
	lds r24,lseqi.2290
	sts lseq.2289,r24
	sts i.2288,__zero_reg__
	rjmp .L35
.L38:
	lds r24,i.2288
	mov r18,r24
	ldi r19,lo8(0)
	ldi r24,lo8(43)
	ldi r25,hi8(43)
	movw r20,r24
	mul r18,r20
	movw r24,r0
	mul r18,r21
	add r25,r0
	mul r19,r20
	add r25,r0
	clr r1
	movw r30,r24
	subi r30,lo8(-(names))
	sbci r31,hi8(-(names))
	std Y+6,r31
	std Y+5,r30
	ldd r30,Y+5
	ldd r31,Y+6
	ld r24,Z
	tst r24
	breq .L36
	lds r24,seqno
	mov r18,r24
	ldi r19,lo8(0)
	ldd r30,Y+5
	ldd r31,Y+6
	ldd r24,Z+3
	mov r24,r24
	ldi r25,lo8(0)
	sub r18,r24
	sbc r19,r25
	lds r24,lseq.2289
	mov r24,r24
	ldi r25,lo8(0)
	cp r24,r18
	cpc r25,r19
	brge .L37
	lds r25,seqno
	ldd r30,Y+5
	ldd r31,Y+6
	ldd r24,Z+3
	mov r31,r25
	sub r31,r24
	mov r24,r31
	sts lseq.2289,r24
	lds r24,i.2288
	sts lseqi.2290,r24
.L37:
	lds r24,i.2288
	subi r24,lo8(-(1))
	sts i.2288,r24
.L35:
	lds r24,i.2288
	cpi r24,lo8(4)
	brsh .+2
	rjmp .L38
.L36:
	lds r24,i.2288
	cpi r24,lo8(4)
	brne .L39
	lds r24,lseqi.2290
	sts i.2288,r24
	lds r24,i.2288
	mov r18,r24
	ldi r19,lo8(0)
	ldi r24,lo8(43)
	ldi r25,hi8(43)
	movw r20,r24
	mul r18,r20
	movw r24,r0
	mul r18,r21
	add r25,r0
	mul r19,r20
	add r25,r0
	clr r1
	movw r30,r24
	subi r30,lo8(-(names))
	sbci r31,hi8(-(names))
	std Y+6,r31
	std Y+5,r30
.L39:
	ldd r24,Y+5
	ldd r25,Y+6
	adiw r24,5
	ldd r18,Y+1
	ldd r19,Y+2
	movw r22,r18
	call strcpy
	ldi r24,lo8(1)
	ldd r30,Y+5
	ldd r31,Y+6
	st Z,r24
	lds r24,seqno
	ldd r30,Y+5
	ldd r31,Y+6
	std Z+3,r24
	ldd r24,Y+3
	ldd r25,Y+4
	ldd r30,Y+5
	ldd r31,Y+6
	std Z+42,r25
	std Z+41,r24
	lds r24,seqno
	subi r24,lo8(-(1))
	sts seqno,r24
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
	.size	resolv_query, .-resolv_query
	.lcomm i.2331,1
.global	resolv_lookup
	.type	resolv_lookup, @function
resolv_lookup:
	push r29
	push r28
	rcall .
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 6 */
	std Y+4,r25
	std Y+3,r24
	sts i.2331,__zero_reg__
	rjmp .L42
.L45:
	lds r24,i.2331
	mov r18,r24
	ldi r19,lo8(0)
	ldi r24,lo8(43)
	ldi r25,hi8(43)
	movw r20,r24
	mul r18,r20
	movw r24,r0
	mul r18,r21
	add r25,r0
	mul r19,r20
	add r25,r0
	clr r1
	subi r24,lo8(-(names))
	sbci r25,hi8(-(names))
	std Y+2,r25
	std Y+1,r24
	ldd r30,Y+1
	ldd r31,Y+2
	ld r24,Z
	cpi r24,lo8(3)
	brne .L43
	ldd r24,Y+1
	ldd r25,Y+2
	movw r18,r24
	subi r18,lo8(-(5))
	sbci r19,hi8(-(5))
	ldd r24,Y+3
	ldd r25,Y+4
	movw r22,r18
	call strcmp
	sbiw r24,0
	brne .L43
	ldd r24,Y+1
	ldd r25,Y+2
	movw r18,r24
	subi r18,lo8(-(37))
	sbci r19,hi8(-(37))
	std Y+6,r19
	std Y+5,r18
	rjmp .L44
.L43:
	lds r24,i.2331
	subi r24,lo8(-(1))
	sts i.2331,r24
.L42:
	lds r24,i.2331
	cpi r24,lo8(4)
	brlo .L45
	std Y+6,__zero_reg__
	std Y+5,__zero_reg__
.L44:
	ldd r24,Y+5
	ldd r25,Y+6
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
	.size	resolv_lookup, .-resolv_lookup
.global	resolv_getserver
	.type	resolv_getserver, @function
resolv_getserver:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	lds r24,resolv_conn
	lds r25,(resolv_conn)+1
	sbiw r24,0
	brne .L48
	std Y+2,__zero_reg__
	std Y+1,__zero_reg__
	rjmp .L49
.L48:
	lds r24,resolv_conn
	lds r25,(resolv_conn)+1
	std Y+2,r25
	std Y+1,r24
.L49:
	ldd r24,Y+1
	ldd r25,Y+2
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	resolv_getserver, .-resolv_getserver
.global	resolv_conf
	.type	resolv_conf, @function
resolv_conf:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	std Y+2,r25
	std Y+1,r24
	lds r24,resolv_conn
	lds r25,(resolv_conn)+1
	sbiw r24,0
	breq .L52
	lds r30,resolv_conn
	lds r31,(resolv_conn)+1
	std Z+5,__zero_reg__
	std Z+4,__zero_reg__
.L52:
	ldd r24,Y+1
	ldd r25,Y+2
	ldi r18,lo8(gs(dns_net_main))
	ldi r19,hi8(gs(dns_net_main))
	ldi r22,lo8(13568)
	ldi r23,hi8(13568)
	movw r20,r18
	call uip_udp_new
	sts (resolv_conn)+1,r25
	sts resolv_conn,r24
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	resolv_conf, .-resolv_conf
	.lcomm i.2371,1
.global	resolv_init
	.type	resolv_init, @function
resolv_init:
	push r29
	push r28
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
	movw r24,r28
	adiw r24,1
	ldi r22,lo8(18)
	ldi r23,hi8(18)
	ldi r20,lo8(4)
	ldi r21,hi8(4)
	call __eerd_block_m644p
	movw r24,r28
	adiw r24,1
	call resolv_conf
	sts i.2371,__zero_reg__
	rjmp .L55
.L56:
	lds r24,i.2371
	mov r18,r24
	ldi r19,lo8(0)
	ldi r24,lo8(43)
	ldi r25,hi8(43)
	movw r20,r24
	mul r18,r20
	movw r24,r0
	mul r18,r21
	add r25,r0
	mul r19,r20
	add r25,r0
	clr r1
	movw r30,r24
	subi r30,lo8(-(names))
	sbci r31,hi8(-(names))
	ldi r24,lo8(3)
	st Z,r24
	lds r24,i.2371
	subi r24,lo8(-(1))
	sts i.2371,r24
.L55:
	lds r24,i.2371
	cpi r24,lo8(4)
	brlo .L56
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	resolv_init, .-resolv_init
	.lcomm names,172
	.lcomm seqno,1
	.comm rfm12_status,2,1
.global __do_clear_bss
