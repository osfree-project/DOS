.model small
.8086
.code

	include msg.inc
	include dos.inc
	
	public	printmsg
printmsg	proc    near
	lodsw
	mov     dx,si
	@Write	, ax, 2		; stderr
	ret
printmsg	endp

	end
