/*  
		FreeDOS DFlat+ Hello World!

*/

/* I N C L U D E S /////////////////////////////////////////////////////// */


#include "dflatp.h"
#include "dfptools.h"

// This line is just used to compile the MODULE bit
#include "resource.h"

/* D E F I N E S ///////////////////////////////////////////////////////// */


/* G L O B A L S ///////////////////////////////////////////////////////// */

DEFPROGRAM
  MOD_DESCRIPTION("FreeDOS Hello World! 1.0")
  MOD_VERSION(1,0,0,0)
  MOD_COPYRIGHT("   Aitor Santamar¡a")
  MOD_LICENSE("GNU GPL 2.0")
  MOD_ABOUT("Simple Hello World based on DFlat+")
END_DEFMODULE


/* P R O T O T Y P E S /////////////////////////////////////////////////// */

static int MainAppProc(WINDOW, MESSAGE, PARAM, PARAM);

/* F U N C T I O N S ///////////////////////////////////////////////////// */


int DfpMain(int argc, char *argv[])
{
    WINDOW wnd;

    wnd = CreateWindow(APPLICATION, "", 0, 0, -1, -1, NULL, NULL, MainAppProc, 0 );

		ProcessMessages();

		return 0;
}


/* ------- window processing module for the Edit application window ----- */
static int MainAppProc(WINDOW wnd,MESSAGE msg,PARAM p1,PARAM p2)
{
    int rtn = DefaultWndProc(wnd, msg, p1, p2);

		if ( msg == CREATE_WINDOW )
    {
        MessageBox ("Message", "Hello world!");
        PostMessage (wnd, CLOSE_WINDOW, 0, 0);
    }

    return rtn;
}



