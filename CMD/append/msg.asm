.model small
.8086
.code

	include msg.inc
	include dos.inc
	
	public	printmsg
printmsg	proc    near
	lodsw
	mov     cx,ax
	mov     ah,40h
	mov     bx,2		; stderr
	mov     dx,si
	int     21h
	ret
printmsg	endp

	end
