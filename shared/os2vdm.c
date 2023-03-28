#include <os2vdm.h>

#include <dos.h>
#include <string.h>

/*
INT 21 U - OS/2 v1.x FAPI - OS/2 FILE SYSTEM JOIN/SUBST
        AH = 61h
        BP = 6467h ("dg")
        AL = function
            00h list (i.e. get)
            01h add
            02h delete
        BX = drive number
        CX = size of buffer
        SI = type (0002h JOIN, 0003h SUBST)
        ES:DI -> buffer
Return: CF clear if successful
            AX = 0000h
            ES:DI buffer filled, if appropriate
        CF set on error
            AX = error code
Notes:  used by JOIN and SUBST to communicate with the OS/2 file system
        for function 00h (list), the ES:DI buffer is filled with the ASCIZ
          JOIN/SUBST path or an empty string if the drive is not JOINed/SUBSTed
        also supported by OS/2 v2.0+ Virtual DOS Machines

For error codes refer to OS/2 <bseerr.h>
*/

APIRET APIENTRY VdmSubstSet(CHAR cDrive, PSZ pszPath)
{
  union REGPACK rp;

  rp.h.ah=0x61;
  rp.w.bp=0x6467;// ("dg")
  rp.h.al=0x01;        // add
  rp.w.bx=cDrive - 'A';
  rp.w.cx=_fstrlen(pszPath)+1;
  rp.w.si=0x0003;
  rp.w.es=FP_SEG(pszPath);
  rp.w.di=FP_OFF(pszPath);

  intr(0x21, &rp);

  return rp.x.ax; // error
}


APIRET APIENTRY VdmSubstQuery(CHAR cDrive, USHORT usBufferSize, PVOID Buffer)
{
  union REGPACK rp;

  rp.h.ah=0x61;
  rp.w.bp=0x6467;// ("dg")
  rp.h.al=0x00; // list
  rp.w.bx=cDrive - 'A';
  rp.w.cx=usBufferSize;
  rp.w.si=0x0003;
  rp.w.es=FP_SEG(Buffer);
  rp.w.di=FP_OFF(Buffer);

  intr(0x21, &rp);

  return rp.x.ax; // error

}

APIRET APIENTRY VdmSubstDelete(CHAR cDrive)
{
  union REGPACK rp;

  rp.h.ah=0x61;
  rp.w.bp=0x6467;// ("dg")
  rp.h.al=0x02;     //delete
  rp.w.bx=cDrive - 'A';
  rp.w.cx=0x00;
  rp.w.si=0x0003;
  rp.w.es=FP_SEG(NULL);
  rp.w.di=FP_OFF(NULL);

  intr(0x21, &rp);

  return rp.x.ax; // error
}

APIRET APIENTRY VdmJoinSet(CHAR cDrive, PSZ pszPath)
{
  union REGPACK rp;

  rp.h.ah=0x61;
  rp.w.bp=0x6467;// ("dg")
  rp.h.al=0x01;        // add
  rp.w.bx=cDrive - 'A';
  rp.w.cx=_fstrlen(pszPath)+1;
  rp.w.si=0x0002;
  rp.w.es=FP_SEG(pszPath);
  rp.w.di=FP_OFF(pszPath);

  intr(0x21, &rp);

  return rp.x.ax; // error
}


APIRET APIENTRY VdmJoinQuery(CHAR cDrive, USHORT usBufferSize, PVOID Buffer)
{
  union REGPACK rp;

  rp.h.ah=0x61;
  rp.w.bp=0x6467;// ("dg")
  rp.h.al=0x00; // list
  rp.w.bx=cDrive - 'A';
  rp.w.cx=usBufferSize;
  rp.w.si=0x0002;
  rp.w.es=FP_SEG(Buffer);
  rp.w.di=FP_OFF(Buffer);

  intr(0x21, &rp);

  return rp.x.ax; // error

}

APIRET APIENTRY VdmJoinDelete(CHAR cDrive)
{
  union REGPACK rp;

  rp.h.ah=0x61;
  rp.w.bp=0x6467;// ("dg")
  rp.h.al=0x02;     //delete
  rp.w.bx=cDrive - 'A';
  rp.w.cx=0x00;
  rp.w.si=0x0002;
  rp.w.es=FP_SEG(NULL);
  rp.w.di=FP_OFF(NULL);

  intr(0x21, &rp);

  return rp.x.ax; // error
}

/*
INT 21 U - OS/2 v2.0+ Virtual DOS Machine - ENABLE AUTOMATIC TITLE SWITCH
        AH = 64h
        DX = 0000h (function number)
        CX = 636Ch (magic value, "cl")
        BX = 0000h (indicates special request)
Note:   if CX is not 636Ch on entry, INT 21/AH=6Ch is invoked, because a bug
          in OS/2 1.x FAPI erroneously called AH=64h instead of AH=6Ch
SeeAlso: AH=64h/DX=0001h,INT 21/AH=4Bh
*/

APIRET APIENTRY VdmEnableAutoTitle(VOID)
{
  union REGPACK rp;

  rp.h.ah=0x64;
  rp.w.cx=0x636c;// ("cl")
  rp.w.bx=0x0000;

  rp.w.dx=0x0000;

  intr(0x21, &rp);

  return 0;
}

/*
--------O-2164--DX0001-----------------------
INT 21 U - OS/2 v2.0+ Virtual DOS Machine - SET SESSION TITLE
        AH = 64h
        DX = 0001h (function number)
        CX = 636Ch (magic value, "cl")
        BX = 0000h (indicates special request)
        ES:DI -> new ASCIZ title (max 12 char) or "" to restore default title
Note:   if CX is not 636Ch on entry, INT 21/AH=6Ch is invoked, because a bug
          in OS/2 1.x FAPI erroneously called AH=64h instead of AH=6Ch
SeeAlso: AH=64h/DX=0000h,AH=64h/DX=0002h,INT 15/AH=12h/BH=05h
*/

APIRET APIENTRY VdmSetTitle(PSZ pszTitle)
{
  union REGPACK rp;

  rp.h.ah=0x64;
  rp.w.cx=0x636c;// ("cl")
  rp.w.bx=0x0000;

  rp.w.dx=0x0001;

  rp.w.es=FP_SEG(pszTitle);
  rp.w.di=FP_OFF(pszTitle);

  intr(0x21, &rp);

  return 0;
}

/*
--------O-2164--DX0002-----------------------
INT 21 U - OS/2 v2.0+ Virtual DOS Machine - GET SESSION TITLE
        AH = 64h
        DX = 0002h (function number)
        CX = 636Ch (magic value, "cl")
        BX = 0000h (indicates special request)
        ES:DI -> 13-byte buffer for current title
Return: buffer filled (single 00h if title never changed)
Note:   if CX is not 636Ch on entry, INT 21/AH=6Ch is invoked, because a bug
          in OS/2 1.x FAPI erroneously called AH=64h instead of AH=6Ch
SeeAlso: AH=64h/DX=0000h,AH=64h/DX=0001h,INT 15/AH=12h/BH=05h
*/

APIRET APIENTRY VdmQueryTitle(PSZ pszTitle)
{
  union REGPACK rp;

  rp.h.ah=0x64;
  rp.w.cx=0x636c;// ("cl")
  rp.w.bx=0x0000;

  rp.w.dx=0x0002;

  rp.w.es=FP_SEG(pszTitle);
  rp.w.di=FP_OFF(pszTitle);

  intr(0x21, &rp);

  return 0;
}

/*
--------O-2164--DX0003-----------------------
INT 21 U - OS/2 v2.1 Virtual DOS Machine - GET LASTDRIVE
        AH = 64h
        DX = 0003h (function number)
        CX = 636Ch (magic value, "cl")
        BX = 0000h (indicates special request)
Return: AL = highest drive supported
Notes:  if CX is not 636Ch on entry, INT 21/AH=6Ch is invoked, because a bug
          in OS/2 1.x FAPI erroneously called AH=64h instead of AH=6Ch
        used by WinOS2
        not supported by OS/2 Warp 3.0, check list of lists instead (see #01627)
SeeAlso: AH=52h
*/

APIRET APIENTRY VdmQueryLastDrive(PSZ cDrive)
{
  union REGPACK rp;

  rp.h.ah=0x64;
  rp.w.cx=0x636c;// ("cl")
  rp.w.bx=0x0000;

  rp.w.dx=0x0003;

  intr(0x21, &rp);

  *cDrive=rp.h.al;

  return 0; // error
}
