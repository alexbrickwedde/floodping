	.file	"enc28j60.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
.global	enc28j60_current_bank
.global	enc28j60_current_bank
	.section .bss
	.type	enc28j60_current_bank, @object
	.size	enc28j60_current_bank, 1
enc28j60_current_bank:
	.skip 1,0
	.text
.global	read_control_register
	.type	read_control_register, @function
read_control_register:
	push r29
	push r28
	rcall .
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
	std Y+3,r24
	ldd r24,Y+3
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(31)
	andi r25,hi8(31)
	cpi r24,27
	cpc r25,__zero_reg__
	brge .L2
	ldd r24,Y+3
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(96)
	andi r25,hi8(96)
	movw r18,r24
	asr r19
	ror r18
	asr r19
	ror r18
	asr r19
	ror r18
	asr r19
	ror r18
	asr r19
	ror r18
	lds r24,enc28j60_current_bank
	mov r24,r24
	ldi r25,lo8(0)
	cp r18,r24
	cpc r19,r25
	breq .L2
	ldd r24,Y+3
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(96)
	andi r25,hi8(96)
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	call switch_bank
.L2:
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ld r24,Z
	std Y+2,r24
/* #APP */
 ;  62 "hardware/ethernet/enc28j60.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	andi r24,lo8(-17)
	st X,r24
	ldd r24,Y+3
	andi r24,lo8(31)
	call spi_send
	ldi r24,lo8(0)
	call spi_send
	std Y+1,r24
	ldd r24,Y+3
	tst r24
	brge .L3
	ldi r24,lo8(0)
	call spi_send
	std Y+1,r24
.L3:
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	ori r24,lo8(16)
	st X,r24
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ldd r24,Y+2
	st Z,r24
	ldd r24,Y+1
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	read_control_register, .-read_control_register
.global	read_buffer_memory
	.type	read_buffer_memory, @function
read_buffer_memory:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ld r24,Z
	std Y+2,r24
/* #APP */
 ;  87 "hardware/ethernet/enc28j60.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	andi r24,lo8(-17)
	st X,r24
	ldi r24,lo8(58)
	call spi_send
	ldi r24,lo8(0)
	call spi_send
	std Y+1,r24
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	ori r24,lo8(16)
	st X,r24
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ldd r24,Y+2
	st Z,r24
	ldd r24,Y+1
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	read_buffer_memory, .-read_buffer_memory
.global	write_control_register
	.type	write_control_register, @function
write_control_register:
	push r29
	push r28
	rcall .
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
	std Y+2,r24
	std Y+3,r22
	ldd r24,Y+2
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(31)
	andi r25,hi8(31)
	cpi r24,27
	cpc r25,__zero_reg__
	brge .L8
	ldd r24,Y+2
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(96)
	andi r25,hi8(96)
	movw r18,r24
	asr r19
	ror r18
	asr r19
	ror r18
	asr r19
	ror r18
	asr r19
	ror r18
	asr r19
	ror r18
	lds r24,enc28j60_current_bank
	mov r24,r24
	ldi r25,lo8(0)
	cp r18,r24
	cpc r19,r25
	breq .L8
	ldd r24,Y+2
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(96)
	andi r25,hi8(96)
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	call switch_bank
.L8:
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ld r24,Z
	std Y+1,r24
/* #APP */
 ;  111 "hardware/ethernet/enc28j60.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	andi r24,lo8(-17)
	st X,r24
	ldd r24,Y+2
	andi r24,lo8(31)
	ori r24,lo8(64)
	call spi_send
	ldd r24,Y+3
	call spi_send
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	ori r24,lo8(16)
	st X,r24
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ldd r24,Y+1
	st Z,r24
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	write_control_register, .-write_control_register
.global	write_buffer_memory
	.type	write_buffer_memory, @function
write_buffer_memory:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	std Y+2,r24
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ld r24,Z
	std Y+1,r24
/* #APP */
 ;  128 "hardware/ethernet/enc28j60.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	andi r24,lo8(-17)
	st X,r24
	ldi r24,lo8(122)
	call spi_send
	ldd r24,Y+2
	call spi_send
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	ori r24,lo8(16)
	st X,r24
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ldd r24,Y+1
	st Z,r24
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	write_buffer_memory, .-write_buffer_memory
.global	bit_field_modify
	.type	bit_field_modify, @function
bit_field_modify:
	push r29
	push r28
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
	std Y+2,r24
	std Y+3,r22
	std Y+4,r20
	ldd r24,Y+2
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(31)
	andi r25,hi8(31)
	cpi r24,27
	cpc r25,__zero_reg__
	brge .L13
	ldd r24,Y+2
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(96)
	andi r25,hi8(96)
	movw r18,r24
	asr r19
	ror r18
	asr r19
	ror r18
	asr r19
	ror r18
	asr r19
	ror r18
	asr r19
	ror r18
	lds r24,enc28j60_current_bank
	mov r24,r24
	ldi r25,lo8(0)
	cp r18,r24
	cpc r19,r25
	breq .L13
	ldd r24,Y+2
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(96)
	andi r25,hi8(96)
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	asr r25
	ror r24
	call switch_bank
.L13:
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ld r24,Z
	std Y+1,r24
/* #APP */
 ;  150 "hardware/ethernet/enc28j60.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	andi r24,lo8(-17)
	st X,r24
	ldd r24,Y+2
	mov r25,r24
	andi r25,lo8(31)
	ldd r24,Y+4
	or r24,r25
	call spi_send
	ldd r24,Y+3
	call spi_send
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	ori r24,lo8(16)
	st X,r24
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ldd r24,Y+1
	st Z,r24
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	bit_field_modify, .-bit_field_modify
.global	set_read_buffer_pointer
	.type	set_read_buffer_pointer, @function
set_read_buffer_pointer:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	std Y+2,r25
	std Y+1,r24
	ldd r25,Y+1
	ldi r24,lo8(0)
	mov r22,r25
	call write_control_register
	ldd r24,Y+1
	ldd r25,Y+2
	mov r24,r25
	clr r25
	mov r25,r24
	ldi r24,lo8(1)
	mov r22,r25
	call write_control_register
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	set_read_buffer_pointer, .-set_read_buffer_pointer
.global	get_read_buffer_pointer
	.type	get_read_buffer_pointer, @function
get_read_buffer_pointer:
	push r16
	push r17
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r24,lo8(0)
	call read_control_register
	mov r16,r24
	ldi r17,lo8(0)
	ldi r24,lo8(1)
	call read_control_register
	mov r24,r24
	ldi r25,lo8(0)
	mov r25,r24
	clr r24
	or r24,r16
	or r25,r17
/* epilogue start */
	pop r28
	pop r29
	pop r17
	pop r16
	ret
	.size	get_read_buffer_pointer, .-get_read_buffer_pointer
.global	set_write_buffer_pointer
	.type	set_write_buffer_pointer, @function
set_write_buffer_pointer:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	std Y+2,r25
	std Y+1,r24
	ldd r25,Y+1
	ldi r24,lo8(2)
	mov r22,r25
	call write_control_register
	ldd r24,Y+1
	ldd r25,Y+2
	mov r24,r25
	clr r25
	mov r25,r24
	ldi r24,lo8(3)
	mov r22,r25
	call write_control_register
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	set_write_buffer_pointer, .-set_write_buffer_pointer
.global	get_write_buffer_pointer
	.type	get_write_buffer_pointer, @function
get_write_buffer_pointer:
	push r16
	push r17
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r24,lo8(2)
	call read_control_register
	mov r16,r24
	ldi r17,lo8(0)
	ldi r24,lo8(3)
	call read_control_register
	mov r24,r24
	ldi r25,lo8(0)
	mov r25,r24
	clr r24
	or r24,r16
	or r25,r17
/* epilogue start */
	pop r28
	pop r29
	pop r17
	pop r16
	ret
	.size	get_write_buffer_pointer, .-get_write_buffer_pointer
.global	read_phy
	.type	read_phy, @function
read_phy:
	push r16
	push r17
	push r29
	push r28
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 1 */
	std Y+1,r24
	ldi r24,lo8(-44)
	ldd r22,Y+1
	call write_control_register
	ldi r24,lo8(-46)
	ldi r22,lo8(1)
	ldi r20,lo8(-128)
	call bit_field_modify
.L24:
	ldi r24,lo8(-22)
	call read_control_register
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(1)
	andi r25,hi8(1)
	tst r24
	brne .L24
	ldi r24,lo8(-46)
	ldi r22,lo8(1)
	ldi r20,lo8(-96)
	call bit_field_modify
	ldi r24,lo8(-40)
	call read_control_register
	mov r16,r24
	ldi r17,lo8(0)
	ldi r24,lo8(-39)
	call read_control_register
	mov r24,r24
	ldi r25,lo8(0)
	mov r25,r24
	clr r24
	or r24,r16
	or r25,r17
/* epilogue start */
	pop __tmp_reg__
	pop r28
	pop r29
	pop r17
	pop r16
	ret
	.size	read_phy, .-read_phy
.global	write_phy
	.type	write_phy, @function
write_phy:
	push r29
	push r28
	rcall .
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 3 */
	std Y+1,r24
	std Y+3,r23
	std Y+2,r22
	ldi r24,lo8(-44)
	ldd r22,Y+1
	call write_control_register
	ldd r25,Y+2
	ldi r24,lo8(-42)
	mov r22,r25
	call write_control_register
	ldd r24,Y+2
	ldd r25,Y+3
	mov r24,r25
	clr r25
	mov r25,r24
	ldi r24,lo8(-41)
	mov r22,r25
	call write_control_register
.L27:
	ldi r24,lo8(-22)
	call read_control_register
	mov r24,r24
	ldi r25,lo8(0)
	andi r24,lo8(1)
	andi r25,hi8(1)
	tst r24
	brne .L27
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	write_phy, .-write_phy
.global	reset_controller
	.type	reset_controller, @function
reset_controller:
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
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ld r24,Z
	std Y+15,r24
/* #APP */
 ;  228 "hardware/ethernet/enc28j60.c" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	andi r24,lo8(-17)
	st X,r24
	ldi r24,lo8(-1)
	call spi_send
	ldi r24,lo8(0x40000000)
	ldi r25,hi8(0x40000000)
	ldi r26,hlo8(0x40000000)
	ldi r27,hhi8(0x40000000)
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
	brge .L41
.L39:
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Y+6,r25
	std Y+5,r24
	rjmp .L32
.L41:
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
	brge .L42
.L40:
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
	rjmp .L35
.L36:
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
.L35:
	ldd r24,Y+5
	ldd r25,Y+6
	sbiw r24,0
	brne .L36
	rjmp .L37
.L42:
	ldd r22,Y+7
	ldd r23,Y+8
	ldd r24,Y+9
	ldd r25,Y+10
	call __fixunssfsi
	movw r26,r24
	movw r24,r22
	std Y+6,r25
	std Y+5,r24
.L32:
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
.L37:
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	ori r24,lo8(16)
	st X,r24
	ldi r30,lo8(95)
	ldi r31,hi8(95)
	ldd r24,Y+15
	st Z,r24
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
	.size	reset_controller, .-reset_controller
.global	reset_rx
	.type	reset_rx, @function
reset_rx:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	ldi r24,lo8(31)
	ldi r22,lo8(64)
	ldi r20,lo8(-128)
	call bit_field_modify
	ldi r24,lo8(-25536)
	ldi r25,hi8(-25536)
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
	ldi r24,lo8(31)
	ldi r22,lo8(64)
	ldi r20,lo8(-96)
	call bit_field_modify
	ldi r24,lo8(31)
	ldi r22,lo8(4)
	ldi r20,lo8(-128)
	call bit_field_modify
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	reset_rx, .-reset_rx
.global	init_enc28j60
	.type	init_enc28j60, @function
init_enc28j60:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	call reset_controller
	ldi r24,lo8(8)
	ldi r22,lo8(0)
	call write_control_register
	ldi r24,lo8(9)
	ldi r22,lo8(0)
	call write_control_register
	ldi r24,lo8(10)
	ldi r22,lo8(-1)
	call write_control_register
	ldi r24,lo8(11)
	ldi r22,lo8(15)
	call write_control_register
	ldi r24,lo8(4)
	ldi r22,lo8(0)
	call write_control_register
	ldi r24,lo8(5)
	ldi r22,lo8(16)
	call write_control_register
	ldi r24,lo8(12)
	ldi r22,lo8(0)
	call write_control_register
	ldi r24,lo8(13)
	ldi r22,lo8(0)
	call write_control_register
	ldi r24,lo8(14)
	ldi r22,lo8(0)
	call write_control_register
	ldi r24,lo8(15)
	ldi r22,lo8(0)
	call write_control_register
	sts (enc28j60_next_packet_pointer)+1,__zero_reg__
	sts enc28j60_next_packet_pointer,__zero_reg__
	ldi r24,lo8(-63)
	ldi r22,lo8(-128)
	ldi r20,lo8(-96)
	call bit_field_modify
	ldi r24,lo8(-64)
	ldi r22,lo8(13)
	ldi r20,lo8(-128)
	call bit_field_modify
	ldi r24,lo8(-62)
	ldi r22,lo8(50)
	ldi r20,lo8(-128)
	call bit_field_modify
	ldi r24,lo8(0)
	ldi r22,lo8(0)
	ldi r23,hi8(0)
	call write_phy
	ldi r24,lo8(0)
	call read_phy
	andi r24,lo8(256)
	andi r25,hi8(256)
	sbiw r24,0
	breq .L46
	ldi r24,lo8(-62)
	ldi r22,lo8(1)
	ldi r20,lo8(-128)
	call bit_field_modify
	ldi r24,lo8(-60)
	ldi r22,lo8(18)
	call write_control_register
	ldi r24,lo8(-58)
	ldi r22,lo8(18)
	call write_control_register
	ldi r24,lo8(-57)
	ldi r22,lo8(12)
	call write_control_register
	rjmp .L47
.L46:
	ldi r24,lo8(-62)
	ldi r22,lo8(1)
	ldi r20,lo8(-96)
	call bit_field_modify
	ldi r24,lo8(-60)
	ldi r22,lo8(21)
	call write_control_register
	ldi r24,lo8(-58)
	ldi r22,lo8(18)
	call write_control_register
	ldi r24,lo8(-57)
	ldi r22,lo8(12)
	call write_control_register
.L47:
	ldi r24,lo8(-54)
	ldi r22,lo8(-32)
	call write_control_register
	ldi r24,lo8(-53)
	ldi r22,lo8(5)
	call write_control_register
	lds r25,uip_ethaddr
	ldi r24,lo8(-28)
	mov r22,r25
	call write_control_register
	lds r25,uip_ethaddr+1
	ldi r24,lo8(-27)
	mov r22,r25
	call write_control_register
	lds r25,uip_ethaddr+2
	ldi r24,lo8(-30)
	mov r22,r25
	call write_control_register
	lds r25,uip_ethaddr+3
	ldi r24,lo8(-29)
	mov r22,r25
	call write_control_register
	lds r25,uip_ethaddr+4
	ldi r24,lo8(-32)
	mov r22,r25
	call write_control_register
	lds r25,uip_ethaddr+5
	ldi r24,lo8(-31)
	mov r22,r25
	call write_control_register
	ldi r24,lo8(56)
	ldi r22,lo8(-125)
	call write_control_register
	ldi r24,lo8(20)
	ldi r22,lo8(3090)
	ldi r23,hi8(3090)
	call write_phy
	ldi r24,lo8(27)
	ldi r22,lo8(-37)
	call write_control_register
	ldi r24,lo8(18)
	ldi r22,lo8(18)
	ldi r23,hi8(18)
	call write_phy
	ldi r24,lo8(31)
	ldi r22,lo8(4)
	ldi r20,lo8(-128)
	call bit_field_modify
	ldi r24,lo8(30)
	ldi r22,lo8(-128)
	ldi r20,lo8(-128)
	call bit_field_modify
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	init_enc28j60, .-init_enc28j60
.global	switch_bank
	.type	switch_bank, @function
switch_bank:
	push r29
	push r28
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 1 */
	std Y+1,r24
	ldi r24,lo8(31)
	ldi r22,lo8(3)
	ldi r20,lo8(-96)
	call bit_field_modify
	ldd r24,Y+1
	mov r25,r24
	andi r25,lo8(3)
	ldi r24,lo8(31)
	mov r22,r25
	ldi r20,lo8(-128)
	call bit_field_modify
	ldd r24,Y+1
	sts enc28j60_current_bank,r24
/* epilogue start */
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	switch_bank, .-switch_bank
.global	enc28j60_periodic
	.type	enc28j60_periodic, @function
enc28j60_periodic:
	push r29
	push r28
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 1 */
	ldi r24,lo8(50)
	std Y+1,r24
	ldi r24,lo8(-62)
	call read_control_register
	mov r25,r24
	ldd r24,Y+1
	and r25,r24
	ldd r24,Y+1
	cp r25,r24
	breq .L53
	call init_enc28j60
.L53:
/* epilogue start */
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	enc28j60_periodic, .-enc28j60_periodic
	.comm enc28j60_next_packet_pointer,2,1
	.comm rfm12_status,2,1
.global __do_clear_bss
