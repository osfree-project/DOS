.model small
.8086
.code

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

	end
