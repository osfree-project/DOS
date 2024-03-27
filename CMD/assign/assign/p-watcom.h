/* Portable include file for Watcom C */

#ifdef __WATCOMC__

#ifndef  __LINUX__
#include <direct.h>
#endif

#include <stdlib.h>


/* byte/word/dword type */
typedef unsigned char byte;
typedef unsigned word;
typedef unsigned FLAG;
typedef unsigned FLAG8;
typedef unsigned long dword;

#ifndef _CLIB_
#define peekb(segm,ofs) (*(byte __far*)MK_FP((segm),(ofs)))
#define peekw(segm,ofs) (*(word __far*)MK_FP((segm),(ofs)))
#define pokeb(segm,ofs,value) (peekb((segm),(ofs)) = (byte)(value))
#define pokew(segm,ofs,value) (peekw((segm),(ofs)) = (word)(value))
#endif

/* get/set current working drive */
extern short getdisk(void);
#pragma aux getdisk = \
	"mov ah, 19h"	\
	"int 21h"	\
	"xor ah, ah"	\
	value [ax]

extern short setdisk(int newdrive);
#pragma aux setdisk = \
	"mov ah, 0eh"	\
	"int 21h"	\
	"xor ah, ah"	\
	parm [dx]	\
	modify [dx]	\
	value [ax]

#endif
