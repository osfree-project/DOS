/*
    ASSIGN: Replace drive letters
    Copyright (C) 1995-97 Steffen Kaiser

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 1, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
/* $RCSfile: ASSIGN.C $
   $Locker: ska $	$Name:  $	$State: Rel $

	ASSIGN TSR loader.

	The target DOS versions are: MS-DOS 3.0 .. MS-DOS 6.22. DR-DOS need
	not the TSR, because ASSIGN is handled via the CDS there. Other
	DOS's are unknown to me. Nonetheless, no check is perfomed, if it's
	MS-DOS, or not. If the DOS version is less than 3 a fatal error
	occurs; greater than 6.22 a warning is displayed.

	The usage is similar to the DOS's one, except the SHADOW option:
	ASSIGN [/SHADOW] [x[:]=y[:] [...]]
		installs ASSIGN if neccassary & no command line errors
		no spaces allowed left or right the equal sign '='
		if ASSIGN is already installed & command line errors occur,
			the valid assignments before the incorrect one are made
		the /SHADOW option can be abbreviated down to /SH & is case insensitive
			this forces ASSIGN to reply "not installed, but not OK to install"
			on the multiplex installation question, instead of "installed"
	ASSIGN /STATUS
		any assignments are displayed in the form:
			X: => Y:
		where X is the logical drive letter and Y the one, to which X points
		the /STATUS option can be abbreviated down to /S & is case insensitive
		if ASSIGN is not installed, neither a warning is displayed nor
		it's installed
	ASSIGN [/SHADOW]
		installs ASSIGN if neccassary & no command line errors
		clears the drive map table, so all drive letters point to itselfs

	Target compiler:
		Borland C++ v3.1, Micro-C v3.13

*/

#include <stdio.h>
#include <dos.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <direct.h>                                                                                     
#include <stdlib.h>
#include <portable.h>
#include <getopt.h>

#define nargs() _AX
typedef void __interrupt
#ifdef __cplusplus
	(*fintr)(...);
#else
	(*fintr)();
#endif
#define copy_seg(s1,o1,s2,o2,len) _fmemcpy(MK_FP(s1,o1),MK_FP(s2,o2),len)

#define CMD_NONE 0
#define CMD_STATUS 1
#define CMD_UNINSTALL 2

//!! include asgn_tsr here!!!
#include "asgn_asc.c"

extern char TXT_MSG_INCORRECT_DOSVERSION[];
extern char TXT_MSG_ASSIGN_ASSIGNMENT[];
extern char TXT_MSG_QMARK_ASSIGN[];
extern char TXT_MSG_ASSIGN_NOTINSTALLED[];

#define E_recursion "Cannot unload the module, because it is a recursion loop"
#define E_releaseBlock "The chunk of memory could not be relased"
#define E_internalFailure "Internal failure #%u"
#define E_loadedModule "The module %s is not loaded with this module version"
#define E_notOnTop "Some interrupt vectors are hooked by other programs."
#define E_mcbChain "MCB Chain corrupt"
#define E_assignData "Cannot locate ASSIGN data segment"
#define M_installByte "The installation check byte is 0%02x"
#define M_inRecurs "The recursion rejection flag is 0%02x"
#define E_noMem "Memory full"



#define message(f, ...) {fprintf(f, __VA_ARGS__); }
#define warning(...) printf(__VA_ARGS__);
#define informative(...) printf(__VA_ARGS__)
#define error(...) printf(__VA_ARGS__)
#define fatal(...) {printf(__VA_ARGS__); exit(1); }

/*
 *     Issue an internal failure error message
 *     They have only a number to differ among themselves
 */
#define iFailure(nr) fatal(E_internalFailure, nr)

#define msgErrorNumber(nr) 0

//msgExitCode

/*
 * The application's name
 */
#ifdef MAXFILE
       static char XappName[MAXFILE] = "";
#define maxName MAXFILE
#else /*#      !(defined(MAXFILE)) */
       static char XappName[9] = "";
#define maxName 9
#endif /*#     defined(MAXFILE) */


/*
 *     Return the application's name   
 */
char *appName(void)
{      return XappName;        }


void hlpScreen()
{
       message(stdout, TXT_MSG_QMARK_ASSIGN);
       exit(msgErrorNumber(E_hlpScreen));
}



#ifndef lint
static char const rcsid[] = 
	"$Id: ASSIGN.C 1.4 1997/01/27 08:09:37 ska Rel ska $";
#endif

char shadowStr[] = "SKAUS18A3";
FLAG8 status = CMD_NONE;
FLAG shadow = 0, usehi = 0;

#define cmp_seg(s1,o1,s2,o2,l) _fmemcmp(MK_FP(s1,o1),MK_FP(s2,o2),l)

unsigned Xalloc_seg(unsigned size)
/* reserves a chunk of memory through DOS-48 & last fit */
{	unsigned segment;
	FLAG8 UMBLink, allocation;
        USEREGS

	_AX = 0x5800;
	intr(0x21, &reg);
	allocation = _AL;

	if(usehi) {
		__asm {
			mov ax, 5802h	/* Get UMB Link Status */
			int 21h
			rcl al, 1		/* incorporate Carry */
			xor ah, ah
		}
		UMBLink = nargs();
		if(UMBLink == 0) {	/* UMBs not chained, but available */
			__asm {
				mov ax, 5803h	/* Chain UMBs */
				mov bx, 1
				int 21h
				rcl al, 1
				xor ah, ah
			}
			if(nargs() & 1)
				fatal(E_mcbChain);
		}
	}
	else UMBLink = 0;

	_AX=0x5801;
	_BX=2;
	intr(0x21, &reg);

	__asm {
		mov bx, asmName(size, 4)
		mov ah, 48h
		int 21h
		jnc allocOK
		xor ax, ax
        allocOK:
	}
	segment = nargs();

	if(allocation != 2) {
		_AX = 0x5801;
		_BX = allocation;
		geninterrupt(0x21);
	}
	if(UMBLink == 0) {
		_AX = 0x5803;
		_BX = 0;
		geninterrupt(0x21);
	}

	return segment;
}


int shadowed(unsigned segment)
/* check, if this data segment is a shadowed ASSIGN segment */
{    
	return cmp_seg(FP_SEG(shadowStr), FP_OFF(shadowStr),
                       segment, 0x101 - sizeof(shadowStr), sizeof(shadowStr) - 1) == 0;
}

/* This function returns current DS value */
extern  unsigned short          GetDS( void );
#pragma aux GetDS               = \
        "mov    ax,ds"          \
        value                   [ax];

unsigned getSeg(void)
/* returns the data segment of ASSIGN */
{	int segment;
        USEREGS

	_ES=0;
	_AX=0x0601;
	intr(0x2f,&reg);
	if(!(segment = _ES/*nargs()*/) || segment == GetDS())
		fatal(E_assignData);

	return segment;
}

int installed(void)
/* check, if ASSIGN is installed */
{	int cond;
    USEREGS

	_AX=0x600;
	intr(0x2f, &reg);
	cond=_AL;

	if(cond == 1 && !shadow && !shadowed(getSeg())) warning(TXT_MSG_ASSIGN_NOTINSTALLED);

	return cond;
}

void displayStatus(void)
{	unsigned segment, offset;
	byte dr;

	if(!(dr = installed()))
		informative(TXT_MSG_ASSIGN_NOTINSTALLED);
	else {
		segment = getSeg();
		assert(segment);
		if(shadow) {
			if(dr != 0xff) informative(M_installByte, dr);
			if(dr = peekb(segment, 0x102))
				informative(M_inRecurs, dr);
		}
		for(offset = 1; offset < 27; ++offset)
			if((dr = peekb(segment, offset + 0x102)) != offset)
				message(stdout, TXT_MSG_ASSIGN_ASSIGNMENT, offset + 'A' - 1, 'A' - 1 + dr); //@todo change %c to %1 and %2
	}
}

void clrAssignments(unsigned const segment)
{	unsigned offset;

	assert(segment);

	for(offset = 0; offset < 26; ++offset)
		pokeb(segment, offset + 0x103, offset + 1);
}

void addAssignment(unsigned const segment, const char * const asgm)
{	char const *p;
	char dr1, dr2;

	p = asgm;
	assert(p && segment);
	if(islower(*p)) dr1 = toupper(*p);
	else if(!isupper(dr1 = *p)) hlpScreen();

	if(*++p == ':') ++p;
	if(!*p == '=') hlpScreen();

	if(islower(*++p)) dr2 = toupper(*p);
	else if(!isupper(dr2 = *p)) hlpScreen();

	if(*++p == ':') ++p;
	if(*p) hlpScreen();

	pokeb(segment, 0x103 + (int)dr1 - 'A', dr2 - 'A' + 1);
}

#include <algnbyte.h>

struct PATCHITEM {
	byte intNr;
	word oldIntOfs;
	word oldIntSeg;
	word newIntOfs;
};
struct COMinfo {
	byte intr;
	word addLen;
	word addOff;
	byte type;
};
#include <algndflt.h>

void loadModule(byte *mod, unsigned len, const char *const padd)
/* install module mod with length len */
{	unsigned segLen, segPad, segment, modLen;
	struct COMinfo *nfo;
	byte items;
	const char *pad;
	word vseg, voff;
	struct PATCHITEM const *h;
        USEREGS

	nfo = (struct COMinfo*)(mod + len - sizeof(struct COMinfo));

	if(nfo->type != 1)
		iFailure(1);
	items = nfo->intr;
	pad = padd && *padd? padd: NULL;

/* calculate amount of necessary paragraphs */
	segLen = ((modLen = len - nfo->addLen - (int)items * sizeof(struct PATCHITEM)
						- sizeof(struct COMinfo)) >> 4) + 1;
	segPad = pad? ((strlen(pad) + 2) >> 4) + 1: 0;

/* allocate that amount of paragraphs */
	if(!(segment = Xalloc_seg(segLen + segPad)))
		fatal(E_noMem);

#ifndef NDEBUG
	printf("Loading module at 0x%04x\n", segment);
#endif

/* modify the MCB, so it's left in memory */
	pokew(segment - 1, 1, shadow? 8: segment);	/* 8 indicate MCB's owner is the system */
	copy_seg(segment - 1, 8, _psp - 1, 8, 8);	/* copy Owner ID */
	pokew(segment + segPad - 1, 0x10 - 2, segment);	/* keep MCB paragraphe */

/* pad the block */
	if(pad)
		copy_seg(segment, (segPad << 4) - strlen(pad) - 2, FP_SEG(pad), FP_OFF(pad), strlen(pad));

/* copy the module */
	copy_seg(segment + segPad, 0, FP_SEG(mod), FP_OFF(mod), modLen);

/* adjust segment, that the first byte of the module lies on offset 0x100 */
	segment += segPad - 0x10;

/* patch the module */
	h = (struct PATCHITEM*)nfo;
	while(items--) {
		--h;
		_AL = h->intNr;
		_AH = 0x35;
		intr(0x21, &reg);
		vseg = _ES;
		voff = _BX;
		pokew(segment, h->oldIntOfs, voff);
		pokew(segment, h->oldIntSeg, vseg);
                _dos_setvect(h->intNr, (fintr)MK_FP(segment, h->newIntOfs));
	}
}

void unloadModule(byte *mod, unsigned len, const char *const padd, unsigned const segment)
{	byte *p;
	struct COMinfo *nfo;
	word items;
	const char *pad;
	word vseg, voff;
	struct PATCHITEM const *h;
        USEREGS

#ifndef NDEBUG
	printf("Unloading module from 0x%04x\n", segment);
#endif

	nfo = (struct COMinfo*)(mod + len - sizeof(struct COMinfo));

	if(nfo->type != 1)
		iFailure(1);
	pad = padd && *padd? padd: NULL;

	if(pad && cmp_seg(segment, 0x100 - strlen(pad) - 2
					, FP_SEG(pad), FP_OFF(pad), strlen(pad)))
		fatal(E_loadedModule, appName());

/* check, if all interrupts point into this MCB */

	for(h = (struct PATCHITEM*)nfo, items = nfo->intr; items--;) {
		--h;
		_AL = h->intNr;
		_AH = 0x35;
		intr(0x21, &reg);
		vseg=_ES;
		voff=_BX;
		if(h->newIntOfs != voff || segment != vseg)
		 	error(E_notOnTop);
	}
	for(h = (struct PATCHITEM*)nfo, items = nfo->intr; items--;) {
		--h;
                _dos_setvect(h->intNr, (fintr)MK_FP(peekw(segment, h->oldIntSeg)
					, peekw(segment, h->oldIntOfs)));
	}

#ifndef NDEBUG
	printf("Releasing block @%04x\n", peekw(segment, 0x100 - 2));
#endif

/* now release the memory block */
#ifdef _MICROC_
/* no way to stuff ES into int86() function */

	set_es(peekw(segment, 0x100 - 2));
	__asm {
		mov ah, 49h
		int 21h
		pushf
		pop ax
		mov __FLAGS, ax
	}
#else
	_ES = peekw(segment, 0x100 - 2);
	_AX = 0x4900;
	geninterrupt(0x21);
#endif
       if(_CFLAG)      /* Carry set ==> Error */
		fatal(E_releaseBlock);
}

void flush(void)
{	__asm {
		mov ah, 0dh
		int 21h
	}
}

void patchModule(byte *mod, word len)
{	struct COMinfo *nfo;
	byte *iotbl;
	word *p, version;
	FLAG8 a;
        USEREGS

	nfo = (struct COMinfo*)(mod + len - sizeof(struct COMinfo));
	p = (word*)(module - 0x100 + nfo->addOff);
	iotbl = module - 0x100 + *p;

/* Check DOS's version number */
	_AH=0x30;
	intr(0x21, &reg);

/* Patch module */

	if(((version = nargs()) & 0xff) < 5) {
		if((version & 0xff) < 3)
			fatal(TXT_MSG_INCORRECT_DOSVERSION);
		a = 0x10;	/* sub fct >= 0x10 new since DOS5 */
		if((version & 0xff) < 4) {
			if((version >> 8) < 2) {	
				a = 0xc;	/* sub fct >= 0xc new since DOS3.2 */
				if((version >> 8) == 0)
					a = 9;	/* sub fct >= 9 new since DOS3.1 */
			}
		}
		memset(iotbl + a, 0, 0x12 - a);	/* mark those sub fct as NOPs */
	}
}

int main(int argc, char **argv)
{	int c, len;
	char *p;

	while((c = getopt(argc, argv, "sShHmMuU?", "")) != EOF)
		switch(c) {
			case 'u': 
			case 'U': status = CMD_UNINSTALL; break;
			case 'm':
			case 'M': usehi = !NUL; break;
			case 's':
			case 'S':
                        #if 0
				if(len = strlen(p = &argv[optind][optchar])) {
					/* differ "/STATUS" and "/SHADOW" */

					++optind;		/* skip this option */
					optchar = 0;

					if(memicmp(p, "HADOW", len) == 0) {
						shadow = 1;
						continue;
					}
					if(memicmp(p, "TATUS", len))
						hlpScreen();
				}


                        #endif
				/* Status */
				status = CMD_STATUS;
				continue;
			
			default:
				hlpScreen();
		}

	switch(status) {
		case CMD_STATUS:
			if(argv[optind]) hlpScreen();
			displayStatus();
			break;
		case CMD_UNINSTALL:
			if(argv[optind]) hlpScreen();
			if(!installed()) {
				warning(TXT_MSG_ASSIGN_NOTINSTALLED);
				break;
			}
			if(peekb(getSeg(), 0x102))
				error(E_recursion);
			flush();
			unloadModule(module, sizeof(module), shadowStr, getSeg());
			break;
		case CMD_NONE:
			flush();
			if(!installed()) {
				patchModule(module, sizeof(module));
				if(shadow)
					*module = 1;	/* shadow ASSIGN */
				module[1] = getdisk();	/* patch in the current working drive */
				loadModule(module, sizeof(module), shadowStr);
			}

			if(argv[optind])
				do addAssignment(getSeg(), argv[optind]);
				while(argv[++optind]);
			else 
				clrAssignments(getSeg());
			break;
		default:
			iFailure(2);
	}

	return 0;
}
