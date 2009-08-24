/***********************************************************************

    	Copyright 1997 Willows Software, Inc. 

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 675 Mass Ave,
Cambridge, MA 02139, USA.


For more information about the Willows Twin Libraries.

	http://www.willows.com	

To send email to the maintainer of the Willows Twin Libraries.

	mailto:twin@willows.com 

***********************************************************************/
/*******************************************************************************************
**
**                                   PORTABLE CODE ROUTINES
**
********************************************************************************************/

/***********************************
**
**  System Includes
**
***********************************/


/***********************************
**
**  App. Includes
**
***********************************/
#include "portable.h"


/***********************************
**
**  Private Defines
**
***********************************/


/***********************************
**
**  Private functions
**
***********************************/

/******************************** BYTE STREAM READING ROUTINES ******************************/

/***************************************************
*
* Reads the next WORD from the byte stream.
*
****************************************************/
WORD __far __pascal ReadWORD( BYTE __far * fpDataStream )
{
  WORD         wCounter;
  WORD         wValue;
  BYTE __far * BytePtr = (BYTE __far * ) &wValue;

  for( wCounter = 0; wCounter < sizeof(WORD); wCounter++ )
  {
    /* Save byte's value. */
    *BytePtr++ = *fpDataStream;

    /* Goto next byte. */
    fpDataStream = fpDataStream + 1;
  }

  /* Return value of WORD. */
  return( wValue );
}  


/***************************************************
*
* Reads the next DWORD from the byte stream.
*
****************************************************/
DWORD __far __pascal ReadDWORD( BYTE __far * fpDataStream )
{
  WORD         wCounter;
  DWORD        dwValue;
  BYTE __far * BytePtr = (BYTE __far * ) &dwValue;

  for( wCounter = 0; wCounter < sizeof(DWORD); wCounter++ )
  {
    /* Save byte's value. */
    *BytePtr++ = *fpDataStream;

    /* Goto next byte. */
    fpDataStream = fpDataStream + 1;
  }

  /* Return value of DWORD. */
  return( dwValue );
}  


