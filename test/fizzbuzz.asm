
putchar:equ	08000h
CR:	equ	00ah

	ld	a,1
loop:
	push	af
	call	fizzbuzz
	pop	af
	inc	a
	cp	101
	jr	nz,loop
	halt

fizzbuzz:
	ld	l,a
	ld	b,15
	call	divmod
	jr	z,put_fizzbuzz
	ld	a,l
	ld	b,3
	call	divmod
	jr	z,put_fizz
	ld	a,l
	ld	b,5
	call	divmod
	jr	z,put_buzz
	ld	a,l
	call	putdeci
	ld	a,CR
	jp	putchar

put_fizzbuzz:
	call	prints
	db	'FizzBuzz',CR,0
	ret

put_fizz:
	call	prints
	db	'Fizz',CR,0
	ret

put_buzz:
	call	prints
	db	'Buzz',CR,0
	ret

putdeci:
	cp	10
	jr	c,_putdeci1
	push	af
	ld	b,10
	call	divmod
	ld	a,c
	call	putdeci
	pop	af
_putdeci1:
	ld	b,10
	call	divmod
	add	a,'0'
	jp	putchar


; •¶Žš—ño—Í
prints:
	ex	(sp),hl
	jr	_prints_2
_prints_1:
	call	putchar
_prints_2:
	ld	a,(hl)
	inc	hl
	or	a
	jr	nz,_prints_1
	ex	(sp),hl
	ret

; Š„‚èŽZ‚Æ—]‚è
; c = a / b
; a = a % b
; zero => a = 0
divmod:
	ld	c,-1
_divmod1:
	inc	c
	sub	b
	jr	nc,_divmod1
	add	a,b
	ret

