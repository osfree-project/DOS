/* $Id: PORTABLE.H 1.2 1998/08/19 07:27:05 ska Exp ska $
   $Locker: ska $	$Name:  $	$State: Exp $


   $Log: PORTABLE.H $
   Revision 1.2  1998/08/19 07:27:05  ska
   fix: incompatiblies Watcom to other compilers

   Revision 1.1  1998/08/19 06:33:33  ska
   Initial revision

*/

#ifndef __PORTABLE_H
#define __PORTABLE_H

#include <regproto.h>
#define NUL '\0'

#ifdef FARDATA
#undef FARDATA
#endif
#ifdef FARCODE
#undef FARCODE
#endif

#if defined(__HUGE__) || defined(__LARGE__) || defined(__COMPACT__)
#define FARDATA
#endif
#if defined(__HUGE__) || defined(__LARGE__) || defined(__MEDIUM__)
#define FARCODE
#endif


/* far pointer variable handling */
#define TO_FP(var) ((void far*) (var))	/* cast variable to far pointer */
#define FARARG(var,type) type far* var
#define COPYFARARG(var) var

/* DWORD variables handling */
#define setDW(var,seg,ofs) ((var) = (dword)MK_FP(seg,ofs))
#define setDWP(varP,seg,ofs) (*(varP) = (dword)MK_FP(seg,ofs))
#define DW_LO(var) ((word)(var))
#define DW_HI(var) ((word)((var) >> 16))
#define DWP_LO(var) ((word)(var))
#define DWP_HI(var) ((word)((var) >> 16))
#define DWARG dword

/* Simulate long constants and long arguments */
#define TO_LONG(num) (unsigned long)(num)
#define MK_LONG(hi,lo) (((unsigned long)(hi) << 16) | (unsigned)(lo))


#ifndef NULL
#define NULL ((void*)0)
#endif

/* Source In compiler specific settings */

#ifdef __WATCOMC__
#include "p-watcom.h"
#endif


#endif
