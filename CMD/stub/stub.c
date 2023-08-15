// VDM2OS2 - Stub to start 4OS2 & TCMD/OS2 from DOS VDM
// Copyright (c) 1996 Rex C. Conn

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <os2vdm.h>

extern char _far *_LpPgmName;
extern char _far *_LpCmdLine;

int main( void )
{
        STARTDATA StartData;
        union REGS aRegs;

        if ( _osmajor < 20 ) {
                aRegs.h.ah = 0x09;
                aRegs.w.dx = (unsigned int)"This is an OS/2 executable.\r\n$";
                intdos( &aRegs, &aRegs );
                return 2;
        }

        StartData.uLength = sizeof( STARTDATA );

        StartData.uRelated = 0;
        StartData.uForeground = 0;
        StartData.uTrace = 0;

        // set title, name, & args
        StartData.lpTitle = 0L;
        StartData.lpPgmName = _LpPgmName;
        StartData.lpArgs = _LpCmdLine;

        StartData.ulTermQ = 0L;
        StartData.lpEnvironment = 0L;
        StartData.uInherit = 0;
        StartData.uSession = 0;
        StartData.lpIcon = 0;
        StartData.ulPgmHandle = 0L;
        StartData.uPgmControl = 0;
        StartData.uColumn = StartData.uRow = 0;
        StartData.uWidth = StartData.uHeight = StartData.uReserved = 0;
        StartData.ulObjectBuffer = 0L;
        StartData.ulObjectBufferLen = 0L;

        VdmStartSession(&StartData);

        return 0;
}

