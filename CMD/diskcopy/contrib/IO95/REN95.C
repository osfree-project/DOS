/* $RCSfile: REN95.C,v $
   $Locker:  $	$Name: not supported by cvs2svn $	$State: Exp $

	Rename file

   $Log: not supported by cvs2svn $
   Revision 1.2  2000/01/11 09:34:39  ska
   add: support Turbo C v2.01

   Revision 1.1  2000/01/11 09:10:09  ska
   Auto Check-in

*/

#include <assert.h>
#include <dos.h>
#include "io95.h"
#include "io95_loc.h"

#ifndef lint
static char const rcsid[] = 
	"$Id: REN95.C,v 1.1 2006-07-04 19:07:58 perditionc Exp $";
#endif

int rename95(const char * const oldnam, const char * const newnam)
{	union REGPACK r;

	assert(oldnam);
	assert(newnam);
	r.w.ds = FP_SEG(oldnam);
	r.w.dx = FP_OFF(oldnam);
	r.w.es = FP_SEG(newnam);
	r.w.di = FP_OFF(newnam);
	r.w.si = 0;
	r.w.cx = 0;
	return callWin95(0x56, &r);
}
