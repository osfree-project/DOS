/* ------------- dflat.h ----------- */
#ifndef PORTABC
#define PORTABC

#include <dos.h>
#include "portab.h"

#ifdef __WATCOMC__

static void (interrupt far *oldbreak)(void);
static  int     (*Hfunc)(void);

void setcbrk (char check)			/* 1 = all / 0 = only con calls check */
{
		union REGS r;
		
	  r.x.ax = 0x3301;
	  r.h.dl = check;
    int86(0x21, &r, &r);	
}

static  void interrupt far hentry()
{
        if      (!(*Hfunc)())
                _exit(0);
}

void  RestoreControlBreakHandler ()
{
    setvect(0x23, oldbreak);
}

void  SetControlBreakHandler(int (*fptr)())
{
        Hfunc = fptr;

        oldbreak = _dos_getvect (0x23);
        _dos_setvect(0x23, hentry);
}

#endif

#endif
