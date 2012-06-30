	.file	"rfm12.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
.global	rfm12_bandwidth
	.data
	.type	rfm12_bandwidth, @object
	.size	rfm12_bandwidth, 1
rfm12_bandwidth:
	.byte	5
.global	rfm12_gain
	.type	rfm12_gain, @object
	.size	rfm12_gain, 1
rfm12_gain:
	.byte	1
.global	rfm12_drssi
	.type	rfm12_drssi, @object
	.size	rfm12_drssi, 1
rfm12_drssi:
	.byte	4
	.text
.global	rf12_trans
	.type	rf12_trans, @function
rf12_trans:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,29
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 29 */
	std Y+29,r25
	std Y+28,r24
	std Y+27,__zero_reg__
	std Y+26,__zero_reg__
	ldi r26,lo8(40)
	ldi r27,hi8(40)
	ldi r30,lo8(40)
	ldi r31,hi8(40)
	ld r24,Z
	andi r24,lo8(-5)
	st X,r24
	std Y+25,__zero_reg__
	rjmp .L2
.L20:
	ldd r24,Y+28
	ldd r25,Y+29
	tst r25
	brge .L3
	ldi r26,lo8(40)
	ldi r27,hi8(40)
	ldi r30,lo8(40)
	ldi r31,hi8(40)
	ld r24,Z
	ori r24,lo8(1)
	st X,r24
	rjmp .L4
.L3:
	ldi r26,lo8(40)
	ldi r27,hi8(40)
	ldi r30,lo8(40)
	ldi r31,hi8(40)
	ld r24,Z
	andi r24,lo8(-2)
	st X,r24
.L4:
	ldd r24,Y+26
	ldd r25,Y+27
	lsl r24
	rol r25
	std Y+27,r25
	std Y+26,r24
	ldi r30,lo8(38)
	ldi r31,hi8(38)
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(8)
	andi r25,hi8(8)
	sbiw r24,0
	breq .L5
	ldd r24,Y+26
	ldd r25,Y+27
	ori r24,lo8(1)
	std Y+27,r25
	std Y+26,r24
.L5:
	ldi r26,lo8(40)
	ldi r27,hi8(40)
	ldi r30,lo8(40)
	ldi r31,hi8(40)
	ld r24,Z
	ori r24,lo8(2)
	st X,r24
	ldd r24,Y+28
	ldd r25,Y+29
	lsl r24
	rol r25
	std Y+29,r25
	std Y+28,r24
	ldi r24,lo8(0x3e99999a)
	ldi r25,hi8(0x3e99999a)
	ldi r26,hlo8(0x3e99999a)
	ldi r27,hhi8(0x3e99999a)
	std Y+21,r24
	std Y+22,r25
	std Y+23,r26
	std Y+24,r27
	ldd r22,Y+21
	ldd r23,Y+22
	ldd r24,Y+23
	ldd r25,Y+24
	ldi r18,lo8(0x40aaaaab)
	ldi r19,hi8(0x40aaaaab)
	ldi r20,hlo8(0x40aaaaab)
	ldi r21,hhi8(0x40aaaaab)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	std Y+17,r24
	std Y+18,r25
	std Y+19,r26
	std Y+20,r27
	ldd r22,Y+17
	ldd r23,Y+18
	ldd r24,Y+19
	ldd r25,Y+20
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L26
.L22:
	ldi r24,lo8(1)
	std Y+16,r24
	rjmp .L8
.L26:
	ldd r22,Y+17
	ldd r23,Y+18
	ldd r24,Y+19
	ldd r25,Y+20
	ldi r18,lo8(0x437f0000)
	ldi r19,hi8(0x437f0000)
	ldi r20,hlo8(0x437f0000)
	ldi r21,hhi8(0x437f0000)
	call __gtsf2
	cp __zero_reg__,r24
	brlt .+2
	rjmp .L27
.L23:
	ldd r22,Y+21
	ldd r23,Y+22
	ldd r24,Y+23
	ldd r25,Y+24
	ldi r18,lo8(0x447a0000)
	ldi r19,hi8(0x447a0000)
	ldi r20,hlo8(0x447a0000)
	ldi r21,hhi8(0x447a0000)
	call __divsf3
	movw r26,r24
	movw r24,r22
	std Y+12,r24
	std Y+13,r25
	std Y+14,r26
	std Y+15,r27
	ldd r22,Y+12
	ldd r23,Y+13
	ldd r24,Y+14
	ldd r25,Y+15
	ldi r18,lo8(0x457a0000)
	ldi r19,hi8(0x457a0000)
	ldi r20,hlo8(0x457a0000)
	ldi r21,hhi8(0x457a0000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	std Y+8,r24
	std Y+9,r25
	std Y+10,r26
	std Y+11,r27
	ldd r22,Y+8
	ldd r23,Y+9
	ldd r24,Y+10
	ldd r25,Y+11
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L28
.L24:
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+7,r25
	std Y+6,r24
	rjmp .L13
.L28:
	ldd r22,Y+8
	ldd r23,Y+9
	ldd r24,Y+10
	ldd r25,Y+11
	ldi r18,lo8(0x477fff00)
	ldi r19,hi8(0x477fff00)
	ldi r20,hlo8(0x477fff00)
	ldi r21,hhi8(0x477fff00)
	call __gtsf2
	cp __zero_reg__,r24
	brge .L29
.L25:
	ldd r22,Y+12
	ldd r23,Y+13
	ldd r24,Y+14
	ldd r25,Y+15
	ldi r18,lo8(0x41200000)
	ldi r19,hi8(0x41200000)
	ldi r20,hlo8(0x41200000)
	ldi r21,hhi8(0x41200000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r22,r24
	movw r24,r26
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+7,r25
	std Y+6,r24
	rjmp .L16
.L17:
	ldi r24,lo8(400)
	ldi r25,hi8(400)
	std Y+5,r25
	std Y+4,r24
	ldd r24,Y+4
	ldd r25,Y+5
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+5,r25
	std Y+4,r24
	ldd r24,Y+6
	ldd r25,Y+7
	sbiw r24,1
	std Y+7,r25
	std Y+6,r24
.L16:
	ldd r24,Y+6
	ldd r25,Y+7
	sbiw r24,0
	brne .L17
	rjmp .L19
.L29:
	ldd r22,Y+8
	ldd r23,Y+9
	ldd r24,Y+10
	ldd r25,Y+11
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+7,r25
	std Y+6,r24
.L13:
	ldd r24,Y+6
	ldd r25,Y+7
	std Y+3,r25
	std Y+2,r24
	ldd r24,Y+2
	ldd r25,Y+3
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+3,r25
	std Y+2,r24
	rjmp .L19
.L27:
	ldd r22,Y+17
	ldd r23,Y+18
	ldd r24,Y+19
	ldd r25,Y+20
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+16,r24
.L8:
	ldd r24,Y+16
	std Y+1,r24
	ldd r24,Y+1
/* #APP */
 ;  83 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: dec r24
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+1,r24
.L19:
	ldi r26,lo8(40)
	ldi r27,hi8(40)
	ldi r30,lo8(40)
	ldi r31,hi8(40)
	ld r24,Z
	andi r24,lo8(-3)
	st X,r24
	ldd r24,Y+25
	subi r24,lo8(-(1))
	std Y+25,r24
.L2:
	ldd r24,Y+25
	cpi r24,lo8(16)
	brsh .+2
	rjmp .L20
	ldi r26,lo8(40)
	ldi r27,hi8(40)
	ldi r30,lo8(40)
	ldi r31,hi8(40)
	ld r24,Z
	ori r24,lo8(4)
	st X,r24
	ldd r24,Y+26
	ldd r25,Y+27
/* epilogue start */
	adiw r28,29
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	rf12_trans, .-rf12_trans
.global	rf12_init
	.type	rf12_init, @function
rf12_init:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,15
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 15 */
	ldi r30,lo8(39)
	ldi r31,hi8(39)
	ldi r24,lo8(23)
	st Z,r24
	ldi r26,lo8(40)
	ldi r27,hi8(40)
	ldi r30,lo8(40)
	ldi r31,hi8(40)
	ld r24,Z
	ori r24,lo8(4)
	st X,r24
	ldi r26,lo8(40)
	ldi r27,hi8(40)
	ldi r30,lo8(40)
	ldi r31,hi8(40)
	ld r24,Z
	ori r24,lo8(16)
	st X,r24
	std Y+15,__zero_reg__
	rjmp .L31
.L40:
	ldi r24,lo8(0x41200000)
	ldi r25,hi8(0x41200000)
	ldi r26,hlo8(0x41200000)
	ldi r27,hhi8(0x41200000)
	std Y+11,r24
	std Y+12,r25
	std Y+13,r26
	std Y+14,r27
	ldd r22,Y+11
	ldd r23,Y+12
	ldd r24,Y+13
	ldd r25,Y+14
	ldi r18,lo8(0x457a0000)
	ldi r19,hi8(0x457a0000)
	ldi r20,hlo8(0x457a0000)
	ldi r21,hhi8(0x457a0000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	std Y+7,r24
	std Y+8,r25
	std Y+9,r26
	std Y+10,r27
	ldd r22,Y+7
	ldd r23,Y+8
	ldd r24,Y+9
	ldd r25,Y+10
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L44
.L42:
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+6,r25
	std Y+5,r24
	rjmp .L34
.L44:
	ldd r22,Y+7
	ldd r23,Y+8
	ldd r24,Y+9
	ldd r25,Y+10
	ldi r18,lo8(0x477fff00)
	ldi r19,hi8(0x477fff00)
	ldi r20,hlo8(0x477fff00)
	ldi r21,hhi8(0x477fff00)
	call __gtsf2
	cp __zero_reg__,r24
	brge .L45
.L43:
	ldd r22,Y+11
	ldd r23,Y+12
	ldd r24,Y+13
	ldd r25,Y+14
	ldi r18,lo8(0x41200000)
	ldi r19,hi8(0x41200000)
	ldi r20,hlo8(0x41200000)
	ldi r21,hhi8(0x41200000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r22,r24
	movw r24,r26
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+6,r25
	std Y+5,r24
	rjmp .L37
.L38:
	ldi r24,lo8(400)
	ldi r25,hi8(400)
	std Y+4,r25
	std Y+3,r24
	ldd r24,Y+3
	ldd r25,Y+4
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+4,r25
	std Y+3,r24
	ldd r24,Y+5
	ldd r25,Y+6
	sbiw r24,1
	std Y+6,r25
	std Y+5,r24
.L37:
	ldd r24,Y+5
	ldd r25,Y+6
	sbiw r24,0
	brne .L38
	rjmp .L39
.L45:
	ldd r22,Y+7
	ldd r23,Y+8
	ldd r24,Y+9
	ldd r25,Y+10
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+6,r25
	std Y+5,r24
.L34:
	ldd r24,Y+5
	ldd r25,Y+6
	std Y+2,r25
	std Y+1,r24
	ldd r24,Y+1
	ldd r25,Y+2
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+2,r25
	std Y+1,r24
.L39:
	ldd r24,Y+15
	subi r24,lo8(-(1))
	std Y+15,r24
.L31:
	ldd r24,Y+15
	cpi r24,lo8(10)
	brsh .+2
	rjmp .L40
	ldi r24,lo8(-16160)
	ldi r25,hi8(-16160)
	call rf12_trans
	ldi r24,lo8(-32537)
	ldi r25,hi8(-32537)
	call rf12_trans
	ldi r24,lo8(-15701)
	ldi r25,hi8(-15701)
	call rf12_trans
	ldi r24,lo8(-13695)
	ldi r25,hi8(-13695)
	call rf12_trans
	ldi r24,lo8(-8192)
	ldi r25,hi8(-8192)
	call rf12_trans
	ldi r24,lo8(-14336)
	ldi r25,hi8(-14336)
	call rf12_trans
	ldi r24,lo8(-15113)
	ldi r25,hi8(-15113)
	call rf12_trans
	ldi r24,lo8(1659)
	ldi r25,hi8(1659)
	call rfm12_setfreq
	ldi r24,lo8(4)
	ldi r22,lo8(1)
	ldi r20,lo8(4)
	call rfm12_setbandwidth
	ldi r24,lo8(666)
	ldi r25,hi8(666)
	call rfm12_setbaud
	ldi r24,lo8(0)
	ldi r22,lo8(6)
	call rfm12_setpower
/* epilogue start */
	adiw r28,15
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	rf12_init, .-rf12_init
.global	rfm12_setbandwidth
	.type	rfm12_setbandwidth, @function
rfm12_setbandwidth:
	push r29
	push r28
	rcall .
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
	std Y+1,r24
	std Y+2,r22
	std Y+3,r20
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	lsl r24
	rol r25
	swap r24
	swap r25
	andi r25,0xf0
	eor r25,r24
	andi r24,0xf0
	eor r25,r24
	movw r18,r24
	andi r19,hi8(255)
	ldd r24,Y+2
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(3)
	andi r25,hi8(3)
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	or r18,r24
	or r19,r25
	ldd r24,Y+3
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(7)
	andi r25,hi8(7)
	or r24,r18
	or r25,r19
	ori r25,hi8(-27648)
	call rf12_trans
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	rfm12_setbandwidth, .-rfm12_setbandwidth
.global	rfm12_setfreq
	.type	rfm12_setfreq, @function
rfm12_setfreq:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	std Y+2,r25
	std Y+1,r24
	ldd r24,Y+1
	ldd r25,Y+2
	cpi r24,96
	cpc r25,__zero_reg__
	brsh .L49
	ldi r24,lo8(96)
	ldi r25,hi8(96)
	std Y+2,r25
	std Y+1,r24
	rjmp .L50
.L49:
	ldd r24,Y+1
	ldd r25,Y+2
	ldi r18,hi8(3904)
	cpi r24,lo8(3904)
	cpc r25,r18
	brlo .L50
	ldi r24,lo8(3903)
	ldi r25,hi8(3903)
	std Y+2,r25
	std Y+1,r24
.L50:
	ldd r24,Y+1
	ldd r25,Y+2
	ori r25,hi8(-24576)
	call rf12_trans
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	rfm12_setfreq, .-rfm12_setfreq
.global	rfm12_setbaud
	.type	rfm12_setbaud, @function
rfm12_setbaud:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	std Y+2,r25
	std Y+1,r24
	ldd r24,Y+1
	ldd r25,Y+2
	ldi r18,hi8(663)
	cpi r24,lo8(663)
	cpc r25,r18
	brlo .L55
	ldd r24,Y+1
	ldd r25,Y+2
	ldi r18,hi8(5400)
	cpi r24,lo8(5400)
	cpc r25,r18
	brsh .L54
	ldd r24,Y+1
	ldd r25,Y+2
	movw r18,r24
	ldi r20,lo8(0)
	ldi r21,hi8(0)
	ldi r24,lo8(43104)
	ldi r25,hi8(43104)
	ldi r26,hlo8(43104)
	ldi r27,hhi8(43104)
	movw r22,r24
	movw r24,r26
	call __divmodsi4
	movw r26,r20
	movw r24,r18
	sbiw r24,1
	ori r24,lo8(-14720)
	ori r25,hi8(-14720)
	call rf12_trans
	rjmp .L55
.L54:
	ldd r24,Y+1
	ldd r25,Y+2
	movw r18,r24
	ldi r20,lo8(0)
	ldi r21,hi8(0)
	ldi r24,lo8(344828)
	ldi r25,hi8(344828)
	ldi r26,hlo8(344828)
	ldi r27,hhi8(344828)
	movw r22,r24
	movw r24,r26
	call __udivmodsi4
	movw r26,r20
	movw r24,r18
	sbiw r24,1
	ori r25,hi8(-14848)
	call rf12_trans
.L55:
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	rfm12_setbaud, .-rfm12_setbaud
.global	rfm12_setpower
	.type	rfm12_setpower, @function
rfm12_setpower:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	std Y+1,r24
	std Y+2,r22
	ldd r24,Y+1
	mov r24,r24
	ldi r25,lo8(0)
	movw r18,r24
	andi r18,lo8(7)
	andi r19,hi8(7)
	ldd r24,Y+2
	mov r24,r24
	ldi r25,lo8(0)
	swap r24
	swap r25
	andi r25,0xf0
	eor r25,r24
	andi r24,0xf0
	eor r25,r24
	andi r25,hi8(255)
	or r24,r18
	or r25,r19
	ori r25,hi8(-26624)
	call rf12_trans
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	rfm12_setpower, .-rfm12_setpower
.global	rf12_ready
	.type	rf12_ready, @function
rf12_ready:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,28
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 28 */
	std Y+27,r24
	ldi r24,lo8(10000)
	ldi r25,hi8(10000)
	std Y+26,r25
	std Y+25,r24
	ldi r26,lo8(40)
	ldi r27,hi8(40)
	ldi r30,lo8(40)
	ldi r31,hi8(40)
	ld r24,Z
	andi r24,lo8(-2)
	st X,r24
	ldi r26,lo8(40)
	ldi r27,hi8(40)
	ldi r30,lo8(40)
	ldi r31,hi8(40)
	ld r24,Z
	andi r24,lo8(-5)
	st X,r24
/* #APP */
 ;  142 "hardware/radio/rfm12/rfm12.c" 1
	nop
 ;  0 "" 2
/* #NOAPP */
	rjmp .L59
.L75:
	ldd r24,Y+27
	tst r24
	brne .+2
	rjmp .L59
	ldd r24,Y+25
	ldd r25,Y+26
	sbiw r24,1
	std Y+26,r25
	std Y+25,r24
	ldi r24,lo8(0x3f800000)
	ldi r25,hi8(0x3f800000)
	ldi r26,hlo8(0x3f800000)
	ldi r27,hhi8(0x3f800000)
	std Y+21,r24
	std Y+22,r25
	std Y+23,r26
	std Y+24,r27
	ldd r22,Y+21
	ldd r23,Y+22
	ldd r24,Y+23
	ldd r25,Y+24
	ldi r18,lo8(0x40aaaaab)
	ldi r19,hi8(0x40aaaaab)
	ldi r20,hlo8(0x40aaaaab)
	ldi r21,hhi8(0x40aaaaab)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	std Y+17,r24
	std Y+18,r25
	std Y+19,r26
	std Y+20,r27
	ldd r22,Y+17
	ldd r23,Y+18
	ldd r24,Y+19
	ldd r25,Y+20
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L83
.L79:
	ldi r24,lo8(1)
	std Y+16,r24
	rjmp .L62
.L83:
	ldd r22,Y+17
	ldd r23,Y+18
	ldd r24,Y+19
	ldd r25,Y+20
	ldi r18,lo8(0x437f0000)
	ldi r19,hi8(0x437f0000)
	ldi r20,hlo8(0x437f0000)
	ldi r21,hhi8(0x437f0000)
	call __gtsf2
	cp __zero_reg__,r24
	brlt .+2
	rjmp .L84
.L80:
	ldd r22,Y+21
	ldd r23,Y+22
	ldd r24,Y+23
	ldd r25,Y+24
	ldi r18,lo8(0x447a0000)
	ldi r19,hi8(0x447a0000)
	ldi r20,hlo8(0x447a0000)
	ldi r21,hhi8(0x447a0000)
	call __divsf3
	movw r26,r24
	movw r24,r22
	std Y+12,r24
	std Y+13,r25
	std Y+14,r26
	std Y+15,r27
	ldd r22,Y+12
	ldd r23,Y+13
	ldd r24,Y+14
	ldd r25,Y+15
	ldi r18,lo8(0x457a0000)
	ldi r19,hi8(0x457a0000)
	ldi r20,hlo8(0x457a0000)
	ldi r21,hhi8(0x457a0000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	std Y+8,r24
	std Y+9,r25
	std Y+10,r26
	std Y+11,r27
	ldd r22,Y+8
	ldd r23,Y+9
	ldd r24,Y+10
	ldd r25,Y+11
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L85
.L81:
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+7,r25
	std Y+6,r24
	rjmp .L67
.L85:
	ldd r22,Y+8
	ldd r23,Y+9
	ldd r24,Y+10
	ldd r25,Y+11
	ldi r18,lo8(0x477fff00)
	ldi r19,hi8(0x477fff00)
	ldi r20,hlo8(0x477fff00)
	ldi r21,hhi8(0x477fff00)
	call __gtsf2
	cp __zero_reg__,r24
	brge .L86
.L82:
	ldd r22,Y+12
	ldd r23,Y+13
	ldd r24,Y+14
	ldd r25,Y+15
	ldi r18,lo8(0x41200000)
	ldi r19,hi8(0x41200000)
	ldi r20,hlo8(0x41200000)
	ldi r21,hhi8(0x41200000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r22,r24
	movw r24,r26
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+7,r25
	std Y+6,r24
	rjmp .L70
.L71:
	ldi r24,lo8(400)
	ldi r25,hi8(400)
	std Y+5,r25
	std Y+4,r24
	ldd r24,Y+4
	ldd r25,Y+5
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+5,r25
	std Y+4,r24
	ldd r24,Y+6
	ldd r25,Y+7
	sbiw r24,1
	std Y+7,r25
	std Y+6,r24
.L70:
	ldd r24,Y+6
	ldd r25,Y+7
	sbiw r24,0
	brne .L71
	rjmp .L59
.L86:
	ldd r22,Y+8
	ldd r23,Y+9
	ldd r24,Y+10
	ldd r25,Y+11
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+7,r25
	std Y+6,r24
.L67:
	ldd r24,Y+6
	ldd r25,Y+7
	std Y+3,r25
	std Y+2,r24
	ldd r24,Y+2
	ldd r25,Y+3
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+3,r25
	std Y+2,r24
	rjmp .L59
.L84:
	ldd r22,Y+17
	ldd r23,Y+18
	ldd r24,Y+19
	ldd r25,Y+20
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+16,r24
.L62:
	ldd r24,Y+16
	std Y+1,r24
	ldd r24,Y+1
/* #APP */
 ;  83 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: dec r24
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+1,r24
.L59:
	ldi r30,lo8(38)
	ldi r31,hi8(38)
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(8)
	andi r25,hi8(8)
	sbiw r24,0
	brne .L74
	ldd r24,Y+25
	ldd r25,Y+26
	sbiw r24,0
	breq .+2
	rjmp .L75
.L74:
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	ori r24,lo8(4)
	st X,r24
	ldd r24,Y+25
	ldd r25,Y+26
	sbiw r24,0
	brne .L76
	std Y+28,__zero_reg__
	rjmp .L77
.L76:
	ldi r24,lo8(1)
	std Y+28,r24
.L77:
	ldd r24,Y+28
/* epilogue start */
	adiw r28,28
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	rf12_ready, .-rf12_ready
.global	rf12_data
	.type	rf12_data, @function
rf12_data:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	ldi r26,lo8(40)
	ldi r27,hi8(40)
	ldi r30,lo8(40)
	ldi r31,hi8(40)
	ld r24,Z
	andi r24,lo8(-5)
	st X,r24
	ldi r26,lo8(40)
	ldi r27,hi8(40)
	ldi r30,lo8(40)
	ldi r31,hi8(40)
	ld r24,Z
	andi r24,lo8(-2)
	st X,r24
/* #APP */
 ;  163 "hardware/radio/rfm12/rfm12.c" 1
	nop
 ;  0 "" 2
/* #NOAPP */
	ldi r30,lo8(38)
	ldi r31,hi8(38)
	ld r24,Z
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(8)
	andi r25,hi8(8)
	sbiw r24,0
	breq .L88
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+2,r25
	std Y+1,r24
	rjmp .L89
.L88:
	std Y+2,__zero_reg__
	std Y+1,__zero_reg__
.L89:
	ldd r24,Y+1
	ldd r25,Y+2
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	rf12_data, .-rf12_data
.global	rf12_txdata
	.type	rf12_txdata, @function
rf12_txdata:
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
	std Y+4,r22
	ldi r26,lo8(40)
	ldi r27,hi8(40)
	ldi r30,lo8(40)
	ldi r31,hi8(40)
	ld r24,Z
	ori r24,lo8(16)
	st X,r24
	ldi r24,lo8(-32200)
	ldi r25,hi8(-32200)
	call rf12_trans
	ldi r24,lo8(0)
	call rf12_ready
	ldi r24,lo8(-18262)
	ldi r25,hi8(-18262)
	call rf12_trans
	ldi r24,lo8(0)
	call rf12_ready
	ldi r24,lo8(-18262)
	ldi r25,hi8(-18262)
	call rf12_trans
	ldi r24,lo8(0)
	call rf12_ready
	ldi r24,lo8(-18262)
	ldi r25,hi8(-18262)
	call rf12_trans
	ldi r24,lo8(0)
	call rf12_ready
	ldi r24,lo8(-18387)
	ldi r25,hi8(-18387)
	call rf12_trans
	ldi r24,lo8(0)
	call rf12_ready
	ldi r24,lo8(-18220)
	ldi r25,hi8(-18220)
	call rf12_trans
	ldi r24,lo8(0)
	call rf12_ready
	ldi r24,lo8(0)
	ldi r25,hi8(0)
	call rf12_trans
	std Y+1,__zero_reg__
	rjmp .L92
.L93:
	ldi r24,lo8(0)
	call rf12_ready
	ldd r30,Y+2
	ldd r31,Y+3
	ld r24,Z
	clr r25
	sbrc r24,7
	com r25
	movw r18,r24
	ori r19,hi8(-18432)
	ldd r24,Y+2
	ldd r25,Y+3
	adiw r24,1
	std Y+3,r25
	std Y+2,r24
	movw r24,r18
	call rf12_trans
	ldd r24,Y+1
	subi r24,lo8(-(1))
	std Y+1,r24
.L92:
	ldd r25,Y+1
	ldd r24,Y+4
	cp r25,r24
	brlo .L93
	ldi r24,lo8(0)
	call rf12_ready
	ldi r24,lo8(-32248)
	ldi r25,hi8(-32248)
	call rf12_trans
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	rf12_txdata, .-rf12_txdata
.global	rf12_rxdata
	.type	rf12_rxdata, @function
rf12_rxdata:
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
	std Y+4,r22
	ldi r24,lo8(-32056)
	ldi r25,hi8(-32056)
	call rf12_trans
	ldi r24,lo8(-13695)
	ldi r25,hi8(-13695)
	call rf12_trans
	ldi r24,lo8(-13693)
	ldi r25,hi8(-13693)
	call rf12_trans
	std Y+1,__zero_reg__
	rjmp .L96
.L97:
	ldi r24,lo8(0)
	call rf12_ready
	ldi r24,lo8(-20480)
	ldi r25,hi8(-20480)
	call rf12_trans
	ldd r30,Y+2
	ldd r31,Y+3
	st Z,r24
	ldd r24,Y+2
	ldd r25,Y+3
	adiw r24,1
	std Y+3,r25
	std Y+2,r24
	ldd r24,Y+1
	subi r24,lo8(-(1))
	std Y+1,r24
.L96:
	ldd r25,Y+1
	ldd r24,Y+4
	cp r25,r24
	brlo .L97
	ldi r24,lo8(-32248)
	ldi r25,hi8(-32248)
	call rf12_trans
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	rf12_rxdata, .-rf12_rxdata
.global	rf12_rxbyte
	.type	rf12_rxbyte, @function
rf12_rxbyte:
	push r29
	push r28
	rcall .
	rcall .
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 5 */
	std Y+4,r25
	std Y+3,r24
	ldi r24,lo8(1)
	call rf12_ready
	mov r24,r24
	ldi r25,lo8(0)
	std Y+2,r25
	std Y+1,r24
	ldd r24,Y+1
	ldd r25,Y+2
	sbiw r24,0
	brne .L100
	std Y+5,__zero_reg__
	rjmp .L101
.L100:
	ldi r24,lo8(-20480)
	ldi r25,hi8(-20480)
	call rf12_trans
	ldd r30,Y+3
	ldd r31,Y+4
	st Z,r24
	ldi r24,lo8(1)
	std Y+5,r24
.L101:
	ldd r24,Y+5
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	rf12_rxbyte, .-rf12_rxbyte
.global	enable_rx
	.type	enable_rx, @function
enable_rx:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,42
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 42 */
	ldi r24,lo8(-32056)
	ldi r25,hi8(-32056)
	call rf12_trans
	ldi r24,lo8(0x41200000)
	ldi r25,hi8(0x41200000)
	ldi r26,hlo8(0x41200000)
	ldi r27,hhi8(0x41200000)
	std Y+39,r24
	std Y+40,r25
	std Y+41,r26
	std Y+42,r27
	ldd r22,Y+39
	ldd r23,Y+40
	ldd r24,Y+41
	ldd r25,Y+42
	ldi r18,lo8(0x457a0000)
	ldi r19,hi8(0x457a0000)
	ldi r20,hlo8(0x457a0000)
	ldi r21,hhi8(0x457a0000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	std Y+35,r24
	std Y+36,r25
	std Y+37,r26
	std Y+38,r27
	ldd r22,Y+35
	ldd r23,Y+36
	ldd r24,Y+37
	ldd r25,Y+38
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L135
.L129:
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+34,r25
	std Y+33,r24
	rjmp .L106
.L135:
	ldd r22,Y+35
	ldd r23,Y+36
	ldd r24,Y+37
	ldd r25,Y+38
	ldi r18,lo8(0x477fff00)
	ldi r19,hi8(0x477fff00)
	ldi r20,hlo8(0x477fff00)
	ldi r21,hhi8(0x477fff00)
	call __gtsf2
	cp __zero_reg__,r24
	brge .L136
.L130:
	ldd r22,Y+39
	ldd r23,Y+40
	ldd r24,Y+41
	ldd r25,Y+42
	ldi r18,lo8(0x41200000)
	ldi r19,hi8(0x41200000)
	ldi r20,hlo8(0x41200000)
	ldi r21,hhi8(0x41200000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r22,r24
	movw r24,r26
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+34,r25
	std Y+33,r24
	rjmp .L109
.L110:
	ldi r24,lo8(400)
	ldi r25,hi8(400)
	std Y+32,r25
	std Y+31,r24
	ldd r24,Y+31
	ldd r25,Y+32
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+32,r25
	std Y+31,r24
	ldd r24,Y+33
	ldd r25,Y+34
	sbiw r24,1
	std Y+34,r25
	std Y+33,r24
.L109:
	ldd r24,Y+33
	ldd r25,Y+34
	sbiw r24,0
	brne .L110
	rjmp .L111
.L136:
	ldd r22,Y+35
	ldd r23,Y+36
	ldd r24,Y+37
	ldd r25,Y+38
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+34,r25
	std Y+33,r24
.L106:
	ldd r24,Y+33
	ldd r25,Y+34
	std Y+30,r25
	std Y+29,r24
	ldd r24,Y+29
	ldd r25,Y+30
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+30,r25
	std Y+29,r24
.L111:
	ldi r24,lo8(-13695)
	ldi r25,hi8(-13695)
	call rf12_trans
	ldi r24,lo8(0x41200000)
	ldi r25,hi8(0x41200000)
	ldi r26,hlo8(0x41200000)
	ldi r27,hhi8(0x41200000)
	std Y+25,r24
	std Y+26,r25
	std Y+27,r26
	std Y+28,r27
	ldd r22,Y+25
	ldd r23,Y+26
	ldd r24,Y+27
	ldd r25,Y+28
	ldi r18,lo8(0x457a0000)
	ldi r19,hi8(0x457a0000)
	ldi r20,hlo8(0x457a0000)
	ldi r21,hhi8(0x457a0000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	std Y+21,r24
	std Y+22,r25
	std Y+23,r26
	std Y+24,r27
	ldd r22,Y+21
	ldd r23,Y+22
	ldd r24,Y+23
	ldd r25,Y+24
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L137
.L131:
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+20,r25
	std Y+19,r24
	rjmp .L114
.L137:
	ldd r22,Y+21
	ldd r23,Y+22
	ldd r24,Y+23
	ldd r25,Y+24
	ldi r18,lo8(0x477fff00)
	ldi r19,hi8(0x477fff00)
	ldi r20,hlo8(0x477fff00)
	ldi r21,hhi8(0x477fff00)
	call __gtsf2
	cp __zero_reg__,r24
	brge .L138
.L132:
	ldd r22,Y+25
	ldd r23,Y+26
	ldd r24,Y+27
	ldd r25,Y+28
	ldi r18,lo8(0x41200000)
	ldi r19,hi8(0x41200000)
	ldi r20,hlo8(0x41200000)
	ldi r21,hhi8(0x41200000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r22,r24
	movw r24,r26
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+20,r25
	std Y+19,r24
	rjmp .L117
.L118:
	ldi r24,lo8(400)
	ldi r25,hi8(400)
	std Y+18,r25
	std Y+17,r24
	ldd r24,Y+17
	ldd r25,Y+18
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+18,r25
	std Y+17,r24
	ldd r24,Y+19
	ldd r25,Y+20
	sbiw r24,1
	std Y+20,r25
	std Y+19,r24
.L117:
	ldd r24,Y+19
	ldd r25,Y+20
	sbiw r24,0
	brne .L118
	rjmp .L119
.L138:
	ldd r22,Y+21
	ldd r23,Y+22
	ldd r24,Y+23
	ldd r25,Y+24
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+20,r25
	std Y+19,r24
.L114:
	ldd r24,Y+19
	ldd r25,Y+20
	std Y+16,r25
	std Y+15,r24
	ldd r24,Y+15
	ldd r25,Y+16
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+16,r25
	std Y+15,r24
.L119:
	ldi r24,lo8(-13693)
	ldi r25,hi8(-13693)
	call rf12_trans
	ldi r24,lo8(0x41200000)
	ldi r25,hi8(0x41200000)
	ldi r26,hlo8(0x41200000)
	ldi r27,hhi8(0x41200000)
	std Y+11,r24
	std Y+12,r25
	std Y+13,r26
	std Y+14,r27
	ldd r22,Y+11
	ldd r23,Y+12
	ldd r24,Y+13
	ldd r25,Y+14
	ldi r18,lo8(0x457a0000)
	ldi r19,hi8(0x457a0000)
	ldi r20,hlo8(0x457a0000)
	ldi r21,hhi8(0x457a0000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	std Y+7,r24
	std Y+8,r25
	std Y+9,r26
	std Y+10,r27
	ldd r22,Y+7
	ldd r23,Y+8
	ldd r24,Y+9
	ldd r25,Y+10
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L139
.L133:
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+6,r25
	std Y+5,r24
	rjmp .L122
.L139:
	ldd r22,Y+7
	ldd r23,Y+8
	ldd r24,Y+9
	ldd r25,Y+10
	ldi r18,lo8(0x477fff00)
	ldi r19,hi8(0x477fff00)
	ldi r20,hlo8(0x477fff00)
	ldi r21,hhi8(0x477fff00)
	call __gtsf2
	cp __zero_reg__,r24
	brge .L140
.L134:
	ldd r22,Y+11
	ldd r23,Y+12
	ldd r24,Y+13
	ldd r25,Y+14
	ldi r18,lo8(0x41200000)
	ldi r19,hi8(0x41200000)
	ldi r20,hlo8(0x41200000)
	ldi r21,hhi8(0x41200000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r22,r24
	movw r24,r26
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+6,r25
	std Y+5,r24
	rjmp .L125
.L126:
	ldi r24,lo8(400)
	ldi r25,hi8(400)
	std Y+4,r25
	std Y+3,r24
	ldd r24,Y+3
	ldd r25,Y+4
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+4,r25
	std Y+3,r24
	ldd r24,Y+5
	ldd r25,Y+6
	sbiw r24,1
	std Y+6,r25
	std Y+5,r24
.L125:
	ldd r24,Y+5
	ldd r25,Y+6
	sbiw r24,0
	brne .L126
	rjmp .L128
.L140:
	ldd r22,Y+7
	ldd r23,Y+8
	ldd r24,Y+9
	ldd r25,Y+10
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+6,r25
	std Y+5,r24
.L122:
	ldd r24,Y+5
	ldd r25,Y+6
	std Y+2,r25
	std Y+1,r24
	ldd r24,Y+1
	ldd r25,Y+2
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+2,r25
	std Y+1,r24
.L128:
/* epilogue start */
	adiw r28,42
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	enable_rx, .-enable_rx
.global	disable_rx
	.type	disable_rx, @function
disable_rx:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r24,lo8(-32248)
	ldi r25,hi8(-32248)
	call rf12_trans
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	disable_rx, .-disable_rx
.global	rf12_rxdata_if_available
	.type	rf12_rxdata_if_available, @function
rf12_rxdata_if_available:
	push r29
	push r28
	rcall .
	rcall .
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 5 */
	std Y+3,r25
	std Y+2,r24
	std Y+5,r23
	std Y+4,r22
	ldi r24,lo8(0)
	ldi r25,hi8(0)
	call rf12_trans
	ldd r30,Y+4
	ldd r31,Y+5
	std Z+1,r25
	st Z,r24
	ldd r30,Y+4
	ldd r31,Y+5
	ld r24,Z
	ldd r25,Z+1
	andi r24,lo8(512)
	andi r25,hi8(512)
	std Y+1,__zero_reg__
	sbiw r24,0
	brne .L144
	ldi r24,lo8(1)
	std Y+1,r24
.L144:
	ldd r24,Y+1
	tst r24
	breq .L145
	ldi r24,lo8(-20480)
	ldi r25,hi8(-20480)
	call rf12_trans
	ldd r30,Y+2
	ldd r31,Y+3
	st Z,r24
.L145:
	ldd r24,Y+1
	clr r25
	sbrc r24,7
	com r25
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	rf12_rxdata_if_available, .-rf12_rxdata_if_available
.global	udpsend
	.type	udpsend, @function
udpsend:
	push r29
	push r28
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
	std Y+2,r25
	std Y+1,r24
	std Y+4,r23
	std Y+3,r22
	ldd r24,Y+1
	ldd r25,Y+2
	sts (g_buf)+1,r25
	sts g_buf,r24
	ldd r24,Y+3
	ldd r25,Y+4
	sts (g_len)+1,r25
	sts g_len,r24
	lds r24,g_conn
	lds r25,(g_conn)+1
	sts (uip_udp_conn)+1,r25
	sts uip_udp_conn,r24
	ldi r24,lo8(5)
	call uip_process
	call router_output
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	udpsend, .-udpsend
	.section	.progmem.data,"a",@progbits
	.type	__c.2426, @object
	.size	__c.2426, 49
__c.2426:
	.string	"D: status 0b%d%d%d%d %d%d%d%d %d%d%d%d %d%d%d%d\n"
	.type	__c.2418, @object
	.size	__c.2418, 28
__c.2418:
	.string	"D: rfm12/overflow -> init.\n"
	.type	__c.2416, @object
	.size	__c.2416, 23
__c.2416:
	.string	"D: rfm12/por -> init.\n"
	.text
.global	rfm12_int_process
	.type	rfm12_int_process, @function
rfm12_int_process:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	subi r28,lo8(-(-109))
	sbci r29,hi8(-(-109))
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 109 */
	ldi r24,lo8(0)
	ldi r25,hi8(0)
	call rf12_trans
	std Y+27,r25
	std Y+26,r24
	ldd r24,Y+26
	ldd r25,Y+27
	andi r24,lo8(16384)
	andi r25,hi8(16384)
	sbiw r24,0
	breq .L150
	ldi r24,lo8(__c.2416)
	ldi r25,hi8(__c.2416)
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r25
	st Z,r24
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
	call rfm12_init
	rjmp .L173
.L150:
	ldd r24,Y+26
	ldd r25,Y+27
	andi r24,lo8(8192)
	andi r25,hi8(8192)
	sbiw r24,0
	breq .L152
	ldi r24,lo8(__c.2418)
	ldi r25,hi8(__c.2418)
	rcall .
	in r30,__SP_L__
	in r31,__SP_H__
	adiw r30,1
	std Z+1,r25
	st Z,r24
	call printf_P
	pop __tmp_reg__
	pop __tmp_reg__
	call rfm12_init
	rjmp .L173
.L152:
	ldd r24,Y+26
	ldd r25,Y+27
	andi r24,lo8(512)
	andi r25,hi8(512)
	std Y+25,__zero_reg__
	sbiw r24,0
	brne .L153
	ldi r24,lo8(1)
	std Y+25,r24
.L153:
	ldd r24,Y+25
	tst r24
	brne .+2
	rjmp .L173
	std Y+20,__zero_reg__
	std Y+19,__zero_reg__
	ldi r24,lo8(5)
	ldi r25,hi8(5)
	std Y+18,r25
	std Y+17,r24
.L164:
	ldd r18,Y+19
	ldd r19,Y+20
	movw r24,r28
	adiw r24,44
	movw r30,r24
	add r30,r18
	adc r31,r19
	st Z,__zero_reg__
	movw r24,r28
	adiw r24,44
	ldd r18,Y+19
	ldd r19,Y+20
	add r24,r18
	adc r25,r19
	call rf12_rxbyte
	mov r24,r24
	ldi r25,lo8(0)
	std Y+16,r25
	std Y+15,r24
	ldd r24,Y+48
	mov r18,r24
	clr r19
	sbrc r18,7
	com r19
	adiw r28,108-62
	std Y+63,r19
	std Y+62,r18
	sbiw r28,108-62
	adiw r28,108-62
	ldd r24,Y+62
	ldd r25,Y+63
	sbiw r28,108-62
	cpi r24,101
	cpc r25,__zero_reg__
	breq .L158
	adiw r28,108-62
	ldd r18,Y+62
	ldd r19,Y+63
	sbiw r28,108-62
	cpi r18,102
	cpc r19,__zero_reg__
	brge .L161
	adiw r28,108-62
	ldd r24,Y+62
	ldd r25,Y+63
	sbiw r28,108-62
	cpi r24,77
	cpc r25,__zero_reg__
	breq .L156
	adiw r28,108-62
	ldd r18,Y+62
	ldd r19,Y+63
	sbiw r28,108-62
	cpi r18,84
	cpc r19,__zero_reg__
	breq .L157
	rjmp .L155
.L161:
	adiw r28,108-62
	ldd r24,Y+62
	ldd r25,Y+63
	sbiw r28,108-62
	cpi r24,102
	cpc r25,__zero_reg__
	breq .L159
	adiw r28,108-62
	ldd r18,Y+62
	ldd r19,Y+63
	sbiw r28,108-62
	cpi r18,103
	cpc r19,__zero_reg__
	breq .L160
	rjmp .L155
.L156:
	ldi r24,lo8(11)
	ldi r25,hi8(11)
	std Y+18,r25
	std Y+17,r24
	rjmp .L162
.L158:
	ldi r24,lo8(9)
	ldi r25,hi8(9)
	std Y+18,r25
	std Y+17,r24
	rjmp .L162
.L159:
	ldi r24,lo8(19)
	ldi r25,hi8(19)
	std Y+18,r25
	std Y+17,r24
	rjmp .L162
.L157:
	ldi r24,lo8(25)
	ldi r25,hi8(25)
	std Y+18,r25
	std Y+17,r24
	rjmp .L162
.L160:
	ldi r24,lo8(19)
	ldi r25,hi8(19)
	std Y+18,r25
	std Y+17,r24
	rjmp .L162
.L155:
	ldi r24,lo8(6)
	ldi r25,hi8(6)
	std Y+18,r25
	std Y+17,r24
.L162:
	ldd r24,Y+19
	ldd r25,Y+20
	adiw r24,1
	std Y+20,r25
	std Y+19,r24
	ldd r18,Y+19
	ldd r19,Y+20
	ldd r24,Y+17
	ldd r25,Y+18
	cp r18,r24
	cpc r19,r25
	brsh .+2
	rjmp .L164
.L163:
	call disable_rx
	ldi r24,lo8(0x3f800000)
	ldi r25,hi8(0x3f800000)
	ldi r26,hlo8(0x3f800000)
	ldi r27,hhi8(0x3f800000)
	std Y+11,r24
	std Y+12,r25
	std Y+13,r26
	std Y+14,r27
	ldd r22,Y+11
	ldd r23,Y+12
	ldd r24,Y+13
	ldd r25,Y+14
	ldi r18,lo8(0x457a0000)
	ldi r19,hi8(0x457a0000)
	ldi r20,hlo8(0x457a0000)
	ldi r21,hhi8(0x457a0000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	std Y+7,r24
	std Y+8,r25
	std Y+9,r26
	std Y+10,r27
	ldd r22,Y+7
	ldd r23,Y+8
	ldd r24,Y+9
	ldd r25,Y+10
	ldi r18,lo8(0x3f800000)
	ldi r19,hi8(0x3f800000)
	ldi r20,hlo8(0x3f800000)
	ldi r21,hhi8(0x3f800000)
	call __ltsf2
	tst r24
	brge .L176
.L174:
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+6,r25
	std Y+5,r24
	rjmp .L167
.L176:
	ldd r22,Y+7
	ldd r23,Y+8
	ldd r24,Y+9
	ldd r25,Y+10
	ldi r18,lo8(0x477fff00)
	ldi r19,hi8(0x477fff00)
	ldi r20,hlo8(0x477fff00)
	ldi r21,hhi8(0x477fff00)
	call __gtsf2
	cp __zero_reg__,r24
	brge .L177
.L175:
	ldd r22,Y+11
	ldd r23,Y+12
	ldd r24,Y+13
	ldd r25,Y+14
	ldi r18,lo8(0x41200000)
	ldi r19,hi8(0x41200000)
	ldi r20,hlo8(0x41200000)
	ldi r21,hhi8(0x41200000)
	call __mulsf3
	movw r26,r24
	movw r24,r22
	movw r22,r24
	movw r24,r26
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+6,r25
	std Y+5,r24
	rjmp .L170
.L171:
	ldi r24,lo8(400)
	ldi r25,hi8(400)
	std Y+4,r25
	std Y+3,r24
	ldd r24,Y+3
	ldd r25,Y+4
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+4,r25
	std Y+3,r24
	ldd r24,Y+5
	ldd r25,Y+6
	sbiw r24,1
	std Y+6,r25
	std Y+5,r24
.L170:
	ldd r24,Y+5
	ldd r25,Y+6
	sbiw r24,0
	brne .L171
	rjmp .L172
.L177:
	ldd r22,Y+7
	ldd r23,Y+8
	ldd r24,Y+9
	ldd r25,Y+10
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+6,r25
	std Y+5,r24
.L167:
	ldd r24,Y+5
	ldd r25,Y+6
	std Y+2,r25
	std Y+1,r24
	ldd r24,Y+1
	ldd r25,Y+2
/* #APP */
 ;  105 "c:/winavr-20100110/lib/gcc/../../avr/include/util/delay_basic.h" 1
	1: sbiw r24,1
	brne 1b
 ;  0 "" 2
/* #NOAPP */
	std Y+2,r25
	std Y+1,r24
.L172:
	call enable_rx
	ldd r18,Y+17
	ldd r19,Y+18
	movw r24,r28
	adiw r24,44
	movw r22,r18
	call udpsend
.L173:
/* epilogue start */
	subi r28,lo8(-(109))
	sbci r29,hi8(-(109))
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	rfm12_int_process, .-rfm12_int_process
.global	rfm12_txstart
	.type	rfm12_txstart, @function
rfm12_txstart:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	std Y+2,r25
	std Y+1,r24
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	rfm12_txstart, .-rfm12_txstart
.global	rfm12_rxstart
	.type	rfm12_rxstart, @function
rfm12_rxstart:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r24,lo8(0)
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	rfm12_rxstart, .-rfm12_rxstart
.global	rfm12_rxfinish
	.type	rfm12_rxfinish, @function
rfm12_rxfinish:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r24,lo8(0)
	ldi r25,hi8(0)
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	rfm12_rxfinish, .-rfm12_rxfinish
.global	rfm12_get_status
	.type	rfm12_get_status, @function
rfm12_get_status:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	ldi r24,lo8(0)
	ldi r25,hi8(0)
	call rf12_trans
	std Y+2,r25
	std Y+1,r24
	ldd r24,Y+1
	ldd r25,Y+2
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	rfm12_get_status, .-rfm12_get_status
.global	x
	.type	x, @function
x:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	lds r24,g_len
	lds r25,(g_len)+1
	sbiw r24,0
	breq .L187
	lds r24,g_buf
	lds r25,(g_buf)+1
	lds r18,g_len
	lds r19,(g_len)+1
	movw r22,r18
	call uip_send
.L187:
	sts (g_len)+1,__zero_reg__
	sts g_len,__zero_reg__
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	x, .-x
.global	rfm12_init
	.type	rfm12_init, @function
rfm12_init:
	push r29
	push r28
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
	call rf12_init
	sts (g_len)+1,__zero_reg__
	sts g_len,__zero_reg__
	ldi r24,lo8(266)
	ldi r25,hi8(266)
	std Y+2,r25
	std Y+1,r24
	movw r30,r28
	adiw r30,3
	ldi r24,lo8(-256)
	ldi r25,hi8(-256)
	std Z+1,r25
	st Z,r24
	ldi r18,lo8(gs(x))
	ldi r19,hi8(gs(x))
	movw r24,r28
	adiw r24,1
	ldi r22,lo8(14640)
	ldi r23,hi8(14640)
	movw r20,r18
	call uip_udp_new
	sts (g_conn)+1,r25
	sts g_conn,r24
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	rfm12_init, .-rfm12_init
	.comm rfm12_status,2,1
	.comm g_buf,2,1
	.comm g_len,2,1
	.comm g_conn,2,1
.global __do_copy_data
.global __do_clear_bss
