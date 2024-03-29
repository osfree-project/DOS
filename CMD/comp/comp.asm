;	COMP	Replacement for the messy-dos command of the same name.

;	Usage:	comp [/#] file1 [file2]
;		where file1 and file2 may be directories or may contain
;		wildcards (but not both).  The default for file2 is the current
;		directory on the current disk.  The switch gives the maximum
;		number of errors to report per file, no limit if #=0.  Default
;		is 0 if file1 refers to a single file, 10 otherwise.
;		Also "comp /?" prints a help message and quits.
;		The '/' in the switch refers to the switch character.
;
;	Author:  Paul Vojta
;	======================================================================
;
;	Copyright (c) 2003  Paul Vojta
;
;	Permission is hereby granted, free of charge, to any person obtaining a
;	copy of this software and associated documentation files (the
;	"Software"), to deal in the Software without restriction, including
;	without limitation the rights to use, copy, modify, merge, publish,
;	distribute, sublicense, and/or sell copies of the Software, and to
;	permit persons to whom the Software is furnished to do so, subject to
;	the following conditions:
;
;	The above copyright notice and this permission notice shall be included
;	in all copies or substantial portions of the Software.
;
;	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
;	OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
;	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
;	IN NO EVENT SHALL PAUL VOJTA OR CONTRIBUTORS BE LIABLE FOR ANY CLAIM,
;	DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
;	OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
;	THE USE OR OTHER DEALINGS IN THE SOFTWARE.
;

_TEXT   segment dword public 'CODE'  use16

;.8086
	org	100h

stdout	equ	1
stderr	equ	2

CR	equ	13
LF	equ	10
TAB	equ	9

fn1	equ	ds:[5ch]	;filename portion of string 1
str2	equ	ds:[5eh]	;string 2
fn2	equ	ds:[60h]
pat2	equ	62h		;pattern for filling in wild cards in filename 2
str1	equ	70h

attr	equ	21		;byte in area43 (see below)
flname	equ	30		;ditto

;	Begin.  Set disk transfer address and slash.

__start:
	mov	ah,1ah		;set DTA
	mov	dx,offset area43
	int	21h
	mov	ax,3700h	;get switch character
	int	21h
	mov	byte ptr switchar1,dl
	cmp	dl,'/'
	jne	f1
	mov	byte ptr slash,'\'
f1:	cld

;	Handle switches

	mov	di,81h
	mov	ch,0
	mov	cl,[di-1]

f2:	jcxz	f9		;if end of string
	mov	al,dl		;switch character
	repnz	scasb
	jne	f9		;if done searching
	cmp	al,'/'
	je	f3		;if slash, don't require preceding white space
	mov	al,[di-2]
	cmp	al,' '
	je	f3		;if space
	cmp	al,TAB
	jne	f2		;if not tab

;	Interpret switch (must be numeric argument or `/?')

f3:	cmp	byte ptr [di],'?'
	je	f8		;if `/?'
	xor	bx,bx		;value of the argument
	push	cx
	mov	cx,10
	mov	si,di
f4:	mov	byte ptr [si-1],' '	;erase the previous character
	lodsb
	sub	al,'0'
	cmp	al,9	
	ja	f5		;if not digit
	xchg	ax,bx
	mul	cx
	mov	bh,0
	add	bx,ax
	jmp	f4		;loop back for more

f5:	mov	maxerrs,bx	;save argument
	mov	byte ptr maxerrset,1;set flag indicating we've done this
	pop	cx
	cmp	al,' '-'0'
	je	f2		;if ended with space
	cmp	al,TAB-'0'
	je	f2		;if ended with tab
	cmp	al,CR-'0'
	je	f2		;if ended with CR
	mov	dx,offset msg1	;illegal switch
	jmp	short f7	;error quit
f6:	mov	dx,offset msg2	;insufficient parameters
f7:	jmp	errend

;	Print help message and quit.

f8:	mov	dx,offset helpmsg
	call	print
	int	20h		;quit

;	Compute buffer size.

f9:	mov	ax,sp
	sub	ax,offset buf+100h
	shr	ax,1
	mov	al,0
	mov	word ptr buflen,ax

;	Start scanning parameters.

	mov	si,81h
f10:	lodsb			;skip spaces
	cmp	al,' '
	je	f10		;if space
	cmp	al,TAB
	je	f10		;if tab
	dec	si		;get first parameter
	mov	di,str1
	call	getparm
	jz	f6		;if no parameter present
	pushf
	push	word ptr area43+attr
	mov	fn1,bx		;beginning of file name 1
	lea	di,[bx+14]
	mov	str2,di		;start of second string
	call	getparm
	mov	fn2,bx
	mov	si,bx		;set up pat2
	mov	di,pat2
	mov	cx,7
	rep	movsw
	pop	word ptr area43+attr
	popf
	jns	f11		;if wild cards
	call	doit
	jmp	short quit

;	Compare multiple files.

f11:	cmp	byte ptr maxerrset,0
	jnz	f12		;if maxerrs given
	mov	word ptr maxerrs,10	;default = 10
f12:	mov	dx,str1
	mov	cx,1
	mov	ah,4eh		;find first file
	int	21h
	jc	f14		;if not found
	mov	word ptr okmsg,offset crlf

f13:	mov	si,offset area43+flname
	mov	di,fn1
	mov	cx,7
	rep	movsw
	mov	dx,str1
	call	print
	call	doit
	mov	ah,4fh		;find next file
	int	21h
	jnc	f13

quit:	mov	ax,4c00h
	int	21h

f14:	mov	dx,offset msg3	;file not found
	jmp	errend

;	GETPARM	Get next parameter.  Upon entry, si points to the next character
;		in the command string and di points where to put it.  On exit,
;		si points to the next+1 character in the command line, di points
;		to the end of the parameter, and bx points to the beginning of
;		the filename part of the string.  AH=0 if no parameter, 1 if
;		wild cards are present, and 80h if it is a file.  Flags are set
;		according to AH.

getparm:mov	str2,di

gp0:	lodsb		;skip separators
	cmp	al,' '
	je	getparm
	cmp	al,TAB
	je	getparm
	cmp	al,CR
	mov	ah,0
	je	gp8		;if C/R

gp1:	stosb			;copy until separator
	lodsb
	cmp	al,' '		;check for separator
	je	gp2
	cmp	al,TAB
	je	gp2
	cmp	al,CR
	jne	gp1
	dec	si

;	Process the parameter.

gp2:	mov	byte ptr [di],0
	mov	bx,di
	mov	ah,81h		;scan for start of file name

gp3:	dec	bx
	cmp	bx,str2
	jl	gp5		;if past beginning
	mov	al,[bx]
	cmp	al,slash
	je	gp6		;if '\' or '/'
	cmp	al,'?'		;check for wild cards
	je	gp4
	cmp	al,'*'
	jne	gp3
gp4:	and	ah,7fh		;clear no-wild bit
	jmp	gp3

gp5:	cmp	byte ptr [bx+2],':'	;no dir. given; remove drive letter
	jne	gp6
	inc	bx
	inc	bx

gp6:	inc	bx
	or	ah,ah
	jns	gp9		;if wild cards
	cmp	bx,di
	mov	ah,1
	je	gp8		;if no file name
	mov	ax,4300h	;see if directory
	mov	dx,str2
	int	21h
	mov	ah,80h
	jc	gp9		;if not found
	test	cl,10h		;test attribute for directory
	jz	gp9		;if file

;	It's a directory.

	mov	al,slash
	stosb
	mov	ah,1

gp8:	push	ax
	mov	bx,di		;add "*.*"
	mov	ax,'.*'
	stosw
	stosb
	mov	byte ptr [di],0
	pop	ax

;	Return.

gp9:	or	ah,ah		;set flags
	ret

;	DOIT	Do it.  Str1, str2, and pat2 are assumed to be set up.

doit:	mov	si,pat2
	mov	bx,fn1
	mov	di,fn2
	mov	cx,8
	call	dopart		;translate wild cards for main part of file name
	dec	si
d1:	lodsb			;skip to file extension
	or	al,al
	jz	d3		;if end of file
	cmp	al,'.'
	jne	d1
	stosb			;store '.'
d2:	mov	al,byte ptr [bx]	;skip to extension in first file name
	cmp	al,0
	jz	d2a
	inc	bx
	cmp	al,'.'
	jne	d2
d2a:	mov	cl,3		;translate wild cards for file extension
	call	dopart

;	Set up files.

d3:	mov	byte ptr [di],0	;store terminating zero
	mov	dx,str1		;open file
	mov	ax,3d00h
	int	21h
	;if c	jmp	err	;if error
	jc	err	;if error
	mov	si,ax
	mov	ax,3d00h	;open file
	mov	dx,str2
	int	21h
	jnc	d3a		;if no error
	cmp	ax,2
	;if ne	jmp	err1	;if not file-not-found
	jne	err1	;if not file-not-found
	call	hyphens
	mov	dx,offset fil
	call	print
	mov	dx,str2
	call	print
	mov	dx,offset msg3+4;' not found.'
	call	print
	mov	ah,3eh		;close other file
	mov	bx,si
	int	21h
	;if c	jmp	err
	jc	err
	ret

d3a:	mov	bx,ax
	mov	word ptr bufno,0
	mov	word ptr errcnt,0
	mov	byte ptr atlflag,0

;	Loop for comparing.  si, bx = file handles.

d4:	mov	cx,buflen	;read from file 1
	mov	dx,offset buf
	xchg	bx,si
	mov	ah,3fh
	int	21h
	;if c	jmp	err	;if error
	jc	err	;if error
	mov	word ptr len1,ax
	push	bx
	mov	bx,si
	mov	si,dx
	add	dx,cx		;read from file 2
	mov	ah,3fh
	int	21h
	;if c	jmp	err
	jc	err
	mov	word ptr len2,ax
	push	bx
	mov	di,dx
	cmp	ax,len1
	jle	d4z		;find minimum length
	mov	ax,len1
d4z:	cmp	ax,buflen	;whether this is the last
	pushf

;	Begin loop over mini-buffers

d5:	mov	cx,256
	cmp	ax,cx
	jae	d5a
	mov	cx,ax
d5a:	sub	ax,cx
	push	ax

;	Do comparison.

d6:	repz	cmpsb
	je	d11		;if buffers equal

;	Print error message.

	push	cx
	push	di
	cmp	word ptr errcnt,0
	jne	d7		;if not the first error
	mov	dx,offset hdr	;print header
	call	print
d7:	call	inccount	;increment error count
	mov	di,offset lyne
	mov	dx,di
	mov	ax,bufno
	cmp	ah,0
	je	d8		;if not a huge file
	push	ax
	mov	al,ah
	call	hex
	stosw
	pop	ax
d8:	call	hex
	stosw
	mov	ax,si
	sub	ax,offset buf+1
	call	hex
	stosw
	pop	bx		;old di
	mov	al,[si-1]	;convert data bytes to hex
	mov	di,offset lyne+6
	call	dumpbyte
	mov	al,[bx-1]
	call	dumpbyte

;	Trim spaces from input line.

d9:	dec	di
	cmp	byte ptr [di],' '
	je	d9		;if space
	inc	di
	mov	ax,CR+256*LF
	stosw
	mov	al,0
	stosb
	mov	di,bx
	call	print		;print the line
	pop	cx
	mov	ax,errcnt
	cmp	ax,maxerrs
	jne	d10		;if within limits
	mov	byte ptr atlflag,1	;set flag to print "At least"
	pop	ax
	popf
	pop	bx
	pop	si
	jmp	short d14

d10:	or	cx,cx
	jnz	d6		;if more comparisons to do

d11:	inc	word ptr bufno	;end mini-buffer
	pop	ax
	or	ax,ax
	;if nz	jmp	d5		;if more in this buffer
	jnz	d5		;if more in this buffer
	popf
	pop	bx		;get file handles
	pop	si
	;if e	jmp	d4		;if not eof yet
	jz	d4		;if not eof yet
	mov	ax,len2
	sub	ax,len1
	mov	cl,'2'
	jg	d12		;if excess bytes on file 2
	je	d14		;if exact match
	dec	cx
	xchg	bx,si
	neg	ax

;	Excess bytes on some file.

d12:	mov	byte ptr xs+26,cl
	mov	len1,ax
	mov	cx,buflen
	mov	dx,offset buf

d13:	mov	ah,3fh		;read excess bytes
	int	21h
	jc	err
	add	len1,ax
	cmp	ax,cx
	je	d13		;if more to go

	mov	al,byte ptr len1+1	;form and print excess-bytes message
	call	hex
	mov	word ptr xs,ax
	mov	al,byte ptr len1
	call	hex
	mov	word ptr xs+2,ax
	push	bx
	mov	dx,offset xs
	call	print
	pop	bx
	call	inccount	;increment error count
	
;	Close files and print error count.

d14:	mov	ah,3eh		;close file
	int	21h
	jc	err
	mov	ah,3eh
	xchg	bx,si
	int	21h
	jc	err

	mov	dx,okmsg	;get OK-message address
	mov	ax,errcnt
	or	ax,ax
	jz	d17		;if no errors
	cmp	byte ptr atlflag,0
	jz	d14a		;if we don't need to print "at least"
	push	ax
	mov	dx,offset atleast	;print "at least"
	call	print
	pop	ax
d14a:	mov	bx,10
	xor	cx,cx

d15:	xor	dx,dx		;convert to decimal
	div	bx
	add	dl,'0'
	push	dx
	inc	cx
	or	ax,ax
	jnz	d15		;if more digits
	mov	ah,2

d16:	pop	dx		;print the number
	int	21h
	loop	d16
	mov	dx,offset nerrs

;	Common ending routine.

d17:	jmp	short print	;call print and return

;	Process errors.

err1:	cmp	ax,5
	jne	err		;if not invalid path
	call	hyphens
	mov	dx,offset msg4
	jmp	short errend

err:	mov	dx,offset msg3	;file not found
	cmp	ax,2
	je	errend		;if file not found
	call	hyphens
	mov	dx,offset msg5	;I/O error
;	jmp	short errend	;(control falls through)

;	Ending stuff.

errend:	mov	bx,stderr
	call	print0
	mov	ax,4c01h
	int	21h

;	HYPHENS	Print hyphens (but only if this is a multiple comp).
;	PRINT	Print the line at (DX).  Destroys AX,CX.
;	PRINT0	Same as above, but also requires BX = output handle.

hyphens:mov	dx,offset hyph
print:	mov	bx,stdout
print0:	push	di
	mov	di,dx
	mov	cx,-1
	mov	al,0		;find length
	repnz	scasb
	not	cx
	dec	cx
	mov	ah,40h
	int	21h
	pop	di
	ret

;	DOPART	Copy string from [si] to [di], changing wild cards to those
;		present in [bx].  This copies up to CX characters.

dopart:	lodsb
	cmp	al,'.'
	je	dp5		;if end of this part
	cmp	al,0
	je	dp5		;if end
	cmp	al,'*'
	jne	dp1
	dec	si
	mov	al,'?'
dp1:	cmp	al,'?'
	jne	dp2		;if not wild card
	mov	al,[bx]
	cmp	al,'.'
	je	dp3
	cmp	al,0
	je	dp3
dp2:	stosb
dp3:	cmp	byte ptr [bx],'.'	;advance [bx], but not past '.' or end of string
	je	dp4
	cmp	byte ptr [bx],0
	je	dp4
	inc	bx
dp4:	loop	dopart
	inc	si
dp5:	ret

;	DUMPBYTE Print a byte in hexadecimal and then as a character.

dumpbyte:push	ax
	mov	ax,'  '
	stosw
	pop	ax
	push	ax
	call	hex
	stosw
	mov	al,' '
	stosb
	pop	ax
	cmp	al,0
	je	db2		;if null character
	cmp	al,' '
	jb	db1		;if control character
	cmp	al,127
	ja	db2		;if not a character
	mov	ah,al
	mov	al,''''		;save normal character
	stosw
	stosb
	ret

db1:	add	al,'A'-1	;control character
	mov	ah,al
	mov	al,'^'
	jmp	short db3

db2:	mov	ax,'  '		;just put spaces
db3:	stosw
	mov	al,' '
	stosb
	ret

;	HEX	Convert a byte to hexadecimal.  Destroys (CL).

hex:	mov	ah,0
	mov	cl,4
	shl	ax,cl
	shr	al,cl
	add	al,90h		;these four instructions change to ascii hex
	daa
	adc	al,40h
	daa
	xchg	al,ah
	add	al,90h
	daa
	adc	al,40h
	daa
	ret

;	INCCOUNT - Increment the variable "errcnt" (unless it equals 65535).

inccount: inc	word ptr errcnt
	jnz	ic1		;if we're OK
	dec	word ptr errcnt
	mov	byte ptr atlflag,1	;set flag to print "At least"
ic1:	ret

slash	db	'/'
msg1	db	'Illegal switch.',CR,LF,0
msg2	db	'Invalid number of parameters.',CR,LF,0
msg3	db	'File not found.',CR,LF,0
msg4	db	'Access denied.',CR,LF,0
msg5	db	'I/O error.',CR,LF,0
fil	db	'File ',0
hyph	db	'--',0
hdr	db	CR,LF,'Byte    File 1  File 2',CR,LF,0
lyne	db	'xxxx    aa      bb "x"',CR,LF,0
xs	db	'nnnn excess bytes on file x.',CR,LF,0
nerrs	db	' error(s).',CR,LF,0
ok	db	'Files compare OK.'	;(continues...)
crlf	db	CR,LF,0
atleast	db	'At least ',0

okmsg	dw	ok
maxerrs	dw	0
maxerrset db	0

end1:

helpmsg	db	'Compare files.',CR,LF,CR,LF
	db	'Syntax:  COMP ['
switchar1 db	'/options] <file1> [file2]',CR,LF,CR,LF
	db	TAB,'where <file1> and [file2] are file names (possibly with '
	db	'wild cards)',CR,LF
	db	TAB,'or directory names.  If [file2] is omitted, the current '
	db	'directory',CR,LF
	db	TAB,'is assumed.',CR,LF,CR,LF
	db	'Options:  ?',TAB,'Display this message and quit.',CR,LF
	db	TAB,'  <#>',TAB,'Do not print more than # errors per file.  '
	db	'If #=0, do not limit',CR,LF
	db	TAB,TAB,'the number of errors.  Default is 0 if <file1> refers '
	db	'to a',CR,LF
	db	TAB,TAB,'single file; 10 if more than one file.',CR,LF,0

area43	equ	end1
errcnt	equ	word ptr end1+43
bufno	equ	word ptr end1+45
len1	equ	word ptr end1+47
len2	equ	word ptr end1+49
buflen	equ	word ptr end1+51
atlflag	equ	byte ptr end1+53
buf	equ	end1+54

_TEXT   ends

	end __start
