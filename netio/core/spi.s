	.file	"spi.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	spi_init
	.type	spi_init, @function
spi_init:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	ldi r26,lo8(37)
	ldi r27,hi8(37)
	ldi r30,lo8(37)
	ldi r31,hi8(37)
	ld r24,Z
	ori r24,lo8(16)
	st X,r24
	ldi r26,lo8(40)
	ldi r27,hi8(40)
	ldi r30,lo8(40)
	ldi r31,hi8(40)
	ld r24,Z
	ori r24,lo8(4)
	st X,r24
	ldi r30,lo8(76)
	ldi r31,hi8(76)
	ldi r24,lo8(80)
	st Z,r24
	ldi r30,lo8(77)
	ldi r31,hi8(77)
	ldi r24,lo8(1)
	st Z,r24
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	spi_init, .-spi_init
	.type	spi_wait_busy, @function
spi_wait_busy:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
.L4:
	ldi r30,lo8(77)
	ldi r31,hi8(77)
	ld r24,Z
	tst r24
	brge .L4
/* epilogue start */
	pop r28
	pop r29
	ret
	.size	spi_wait_busy, .-spi_wait_busy
.global	spi_send
	.type	spi_send, @function
spi_send:
	push r29
	push r28
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 1 */
	std Y+1,r24
	ldi r30,lo8(78)
	ldi r31,hi8(78)
	ldd r24,Y+1
	st Z,r24
	call spi_wait_busy
	ldi r30,lo8(78)
	ldi r31,hi8(78)
	ld r24,Z
/* epilogue start */
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	spi_send, .-spi_send
