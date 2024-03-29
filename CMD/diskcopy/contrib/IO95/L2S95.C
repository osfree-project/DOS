/* $RCSfile: L2S95.C,v $
   $Locker:  $	$Name: not supported by cvs2svn $	$State: Exp $

	int lfn2sfn95(const char * const fnam, char * const buf);

	fully-qualify fnam and convert all long filename portions into
	their short form.

	Return:
		0: success
		2: invalid component in path or drive letter
		3: malformed path or buffer too short


   $Log: not supported by cvs2svn $
   Revision 1.1  2000/01/11 09:10:09  ska
   Auto Check-in

*/

#include <assert.h>
#include <dos.h>
#include <string.h>
#include "io95.h"

#ifndef lint
static char const rcsid[] = 
	"$Id: L2S95.C,v 1.1 2006-07-04 19:07:58 perditionc Exp $";
#endif

static int conv95(int fct, const char * const fnam, char * const buf)
{	union REGPACK r;

	assert(fnam);
	assert(buf);
	r.w.ax = 0x7160;
	r.w.cx = 0x8000 | fct;
	r.w.ds = FP_SEG(fnam);
	r.w.si = FP_OFF(fnam);
	r.w.es = FP_SEG(buf);
	r.w.di = FP_OFF(buf);
	r.w.flags = 0;
	*buf = '\0';
	intr(0x21, &r);
	if(r.w.flags & 1) {
		if(*buf && r.w.ax == 3 && strlen(buf) > 255)
			/* assume the bug */
			return 0;
		return r.w.ax;
	}
	return 0;
}

int truename95(const char * const fnam, char * const buf)
{	return conv95(2, fnam, buf);		}
int lfn2sfn95(const char * const fnam, char * const buf)
{	return conv95(1, fnam, buf);		}
