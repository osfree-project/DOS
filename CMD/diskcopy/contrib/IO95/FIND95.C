/* $RCSfile: FIND95.C,v $
   $Locker:  $ $Name: not supported by cvs2svn $   $State: Exp $

   findfirst/findnext loop

   == For instance:
   struct ffblk95 ff;

   if(findfirst95("some_path\\wildcard_pattern", &ff, file_attribs) == 0) do {
         printf("SFN = %s\n", ff.ff_95.ff_shortname);
         printf("LFN = %s\n", ff.ff_95.ff_longname);
      } while(findnext95(&ff));
      ==

    == Example #2:
    int access95(const char fnam[], int mode)
    { struct ffblk95 ff;
      // Design flaw: Wildcards are accepted :-(

      if(findfirst95(fnam, &ff, FA95_HIDDEN | FA95_SYSTEM))
         return -1;     // error

      findstop95(&ff);  // MUST BE CALLED for Win95 LFN!

      switch(mode) {
      case 0: // file exists
      case 1: // Execute permission -- ignored
      case 4: // Read permission
         break;
      case 2:  // write permission
      case 6: // r&w permission
         if((ff.ff_attr & FA95_RDONLY) == 0)
            break;
      default:
         return -1;     // error
      }

      return 0;
   }
   ==

   $Log: not supported by cvs2svn $
   Revision 1.2  2000/01/11 09:34:27  ska
   add: support Turbo C v2.01

   Revision 1.1  2000/01/11 09:10:08  ska
   Auto Check-in

*/

#include <assert.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>

#include <tcc2wat.h>

#include "io95.h"
#include "find95.h"

#ifdef findfirst
#undef findfirst
#undef findnext
#endif

#define FIND_FIRST 0x4e00
#define FIND_NEXT 0x4f00

#ifndef lint
static char const rcsid[] = 
   "$Id: FIND95.C,v 1.1 2006-07-04 19:07:58 perditionc Exp $";
#endif

#ifndef HAVE_GETSETDTA
void setdta(char far *dta)
{  union REGPACK rp;

   assert(dta);
   rp.w.ds = FP_SEG(dta);
   rp.w.dx = FP_OFF(dta);
   rp.w.ax = 0x1a00;
   intr(0x21, &rp);
}
char far *getdta(void)
{  union REGPACK rp;

   rp.w.ax = 0x2f00;
   intr(0x21, &rp);

   return MK_FP(rp.w.es, rp.w.bx);
}
#endif


static int findfile();

/* Start a search and fill the FF block
   Return:
      == 0: OK
      != 0: failure; OS error code
*/
int findfirst(char *name, FF_Block95 *ff, int attr)
/**Warning: Call to function 'findfile' with no prototype */
{  return findfile(ff, FIND_FIRST, name, attr);
}

/* Continue a previously startet search.
   Return:
      s. findfirst
*/
int findnext(FF_Block95 *ff)
/**Warning: Call to function 'findfile' with no prototype */
{  return findfile(ff, FIND_NEXT, NULL, 0);
}


/* Convert DOS style FF_Block95 into Win95 style */
static void convDOS(FF_Block95 *ff)
{  
   memcpy(ff->ff_95.ff_shortname, ff->ff_name, sizeof(ff->ff_name));
   memcpy(ff->ff_95.ff_longname, ff->ff_name, sizeof(ff->ff_name));
   ff->ff_95.ff_attr95 = ff->ff_attr;
   ff->ff_95.ff_losize = ff->ff_size;
   ff->ff_95.ff_hisize = 0;
}


/*
 * Find first/next file
 * Return: OS error code
 */
static int findfile(FF_Block95 *ff, int mode, char *name, int attr)
{  union REGPACK rp;
   char far *curDTA;

   /* first swap the DTA */
   curDTA = getdta();
   assert(curDTA);
   setdta((char far*)ff);

   /* second peform the desired command */
   if((rp.w.ax = mode) == FIND_FIRST) {
      rp.w.ds = FP_SEG(name);
      rp.w.dx = FP_OFF(name);
      rp.w.cx = attr;
   }
   intr(0x21, &rp);

   /* third re-set previous DTA */
   setdta(curDTA);

   convDOS(ff);

   /* forth check for an error */
   return (rp.w.flags & 1)? errno = rp.w.ax: 0;
}

/* Convert win95 style FF_Block95 into DOS style */
static void conv95(FF_Block95 *ff)
{  if(!*ff->ff_95.ff_shortname)
      memcpy(ff->ff_95.ff_shortname, ff->ff_95.ff_longname
       , sizeof(ff->ff_95.ff_shortname));
   memcpy(ff->ff_name, ff->ff_95.ff_shortname, sizeof(ff->ff_name));
   ff->ff_attr = (unsigned char)ff->ff_95.ff_attr95;
   ff->ff_size = ff->ff_95.ff_losize;
}


static int find95(char *name, FF_Block95 *ff, int attr)
{  union REGPACK r;

   r.w.ax = 0x714e;
   r.w.cx = attr;
   r.w.si = 1;       /* MS-DOS style time */
   r.w.ds = FP_SEG(name);
   r.w.dx = FP_OFF(name);
   r.w.es = FP_SEG(&ff->ff_95);
   r.w.di = FP_OFF(&ff->ff_95);
   r.w.flags = 0;
   intr(0x21, &r);
   if(r.w.flags & 1) {     /* Failure */
      ff->ff_95.ff_status = NOFIND95;
      return r.w.ax;
   }
   ff->ff_95.ff_status = r.w.ax;
   conv95(ff);
   return 0;            /* OK */
}

static int next95(FF_Block95 *ff)
{  union REGPACK r;

   r.w.ax = 0x714f;
   r.w.bx = ff->ff_95.ff_status;
   r.w.si = 1;          /* MS-DOS style time/date */
   r.w.es = FP_SEG(&ff->ff_95);
   r.w.di = FP_OFF(&ff->ff_95);
   r.w.flags = 0;
   intr(0x21, &r);
   if(r.w.flags & 1)
      return r.w.ax;
   conv95(ff);
   return 0;
}

int findfirst95(char *name, FF_Block95 *ff, int attr)
{  int err;

   assert(name);
   assert(ff);
   if(find95(name, ff, attr & 0x7f) == 0)
      return 0;         /* OK */
   return findfirst(name, ff, attr);
}
int findnext95(FF_Block95 *ff)
{  assert(ff);
   return ff->ff_95.ff_status == NOFIND95? findnext(ff): next95(ff);
}
void findstop95(FF_Block95 *ff)
{  assert(ff);
   if(ff->ff_95.ff_status != NOFIND95) {
      union REGPACK r;

      r.w.ax = 0x71a1;
      r.w.bx = ff->ff_95.ff_status;
      intr(0x21, &r);
   }
}
