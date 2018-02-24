
putchar:equ	08000h

	ld	l,helloworld
	ld	a,'H'
_prints_1:
	call	putchar
_prints_2:
	ld	a,(hl)
	inc	hl
	or	a
	jr	nz,_prints_1
	;
	halt

helloworld:
	db	'ello, world!'
;	db	0		; omit terminator because after ram is cleared by 0
