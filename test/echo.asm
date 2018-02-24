
putchar:equ	08000h
getchar:equ	08003h


loop:
	call	getchar
	jr	c,skip
	call	putchar
	jr	loop
skip:
	halt
