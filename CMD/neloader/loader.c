#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dos.h>
#include <os2\newexe.h>

extern char _far *_LpPgmName;
extern char _far *_LpCmdLine;

int main( void )
{
  union REGS aRegs;
  char filename[_MAX_PATH];
  FILE *f;
  struct exe_hdr MZHeader;
  struct new_exe NEHeader;
  int result;

  _fstrcpy(filename, _LpPgmName);

  if (_osmajor < 2) 
  {
    aRegs.h.ah = 0x09;
    aRegs.w.dx = (unsigned int)"This program requires DOS 2.0 or higher.\r\n$";
    intdos( &aRegs, &aRegs );
    return 2;
  }

  if( (f  = fopen( filename, "rb" )) == NULL )
  {
    printf( "The file '%s' was not opened\n", _LpPgmName );
    return 1;
  }

  result = fread(&MZHeader, 1, sizeof(MZHeader), f);

  result = fseek(f, E_LFANEW(MZHeader), SEEK_SET);

  result = fread(&NEHeader, 1, sizeof(NEHeader), f);

  result = fseek(f, E_LFANEW(MZHeader)+NE_SEGTAB(NEHeader), SEEK_SET);

//NE_CSEG(x)

  if(f)
  {
    if (fclose(f))
    {
      printf("The file '%s' was not closed\n", _LpPgmName );
      return 1;
    }
  }

  return 0;
}

