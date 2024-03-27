.8086
_TEXT segment para public 'CODE' use16

	include msg.inc
	include dos.inc
	
	public	printmsg
printmsg	proc    near
	lodsw
	push	dx
	mov     dx,si
	@Write	, ax, 2		; stderr
	pop	dx
	ret
printmsg	endp

_TEXT ends

	end
