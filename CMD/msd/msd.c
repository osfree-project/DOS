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
  MOD_DESCRIPTION("osFree MSD 1.0")
  MOD_VERSION(1,0,0,0)
  MOD_COPYRIGHT(" Yuri Prokushev")
  MOD_LICENSE("GNU GPL 2.0")
  MOD_ABOUT("MSD replacement based on DFlat+")
END_DEFMODULE

BEGIN_USER_COMMANDS
    /* --------------- File menu ---------------- */
    ID_FIND,
    ID_PRINT,
    ID_AUTOEXEC,
    ID_CONFIG,
    ID_SYSTEM,
    ID_WIN,
    ID_EXIT,
    /* --------------- Utilities Menu ------------- */
    ID_MEMBLOCK,
    ID_MEMBROWSER,
    ID_INSCOMMAND,
    ID_TESTPRINT,
    ID_BW,
    /* --------------- Help menu ---------------- */
    ID_ABOUT
END_USER_COMMANDS

DEFMENU(MainMenu)
    /* --------------- the File popdown menu ----------------*/
    POPDOWN( "~File",  NULL, "Finds files, prints reports, exits." )
        SELECTION( "~Find File...",        ID_FIND,     0, 0)
        SELECTION( "~Print Report ...",    ID_PRINT,    0, 0)
        SEPARATOR
        SELECTION( "1 AUTOEXEC.BAT",       ID_AUTOEXEC,    0, 0)
        SELECTION( "2 CONFIG.SYS", ID_CONFIG,       0, 0)
        SELECTION( "3 SYSTEM.INI",      ID_SYSTEM,        0, 0)
        SELECTION( "4 WIN.INI",      ID_WIN,        0, 0)
        SEPARATOR
        SELECTION( "E~xit",       ID_EXIT,     F3, 0)
    ENDPOPDOWN

    /* --------------- the Utilities popdown menu ----------------*/
    POPDOWN( "~Utilities", NULL, "Memory views, insert commands, test printer, color toggle." )
        SELECTION( "~Memory Block Display ...",       ID_MEMBLOCK,   0, 0)
        SELECTION( "Memory ~Browser ...",      ID_MEMBROWSER,  0,  0)
        SELECTION( "~Insert Command ...",     ID_INSCOMMAND, 0, 0)
        SELECTION( "~Test Printer",     ID_TESTPRINT, 0,         0)
        SEPARATOR
        SELECTION( "Black & ~White",     ID_BW,  F5,       0)
    ENDPOPDOWN

    /* --------------- the Help popdown menu ----------------*/
    POPDOWN( "~Help", NULL, "Information about MSD." )
        SELECTION(  "~About ...",          ID_ABOUT,     0, 0 )
    ENDPOPDOWN
ENDMENU

/* P R O T O T Y P E S /////////////////////////////////////////////////// */

static int MainAppProc(WINDOW, MESSAGE, PARAM, PARAM);

/* F U N C T I O N S ///////////////////////////////////////////////////// */


int DfpMain(int argc, char *argv[])
{
    WINDOW wnd;

    wnd = CreateWindow(APPLICATION, "", 0, 0, -1, -1, &MainMenu, NULL, MainAppProc,  HASBORDER | MINMAXBOX | HASSTATUSBAR);

    ProcessMessages();

    return 0;
}


/* ------- window processing module for the Edit application window ----- */
static int MainAppProc(WINDOW wnd,MESSAGE msg,PARAM p1,PARAM p2)
{
    int rtn;

    switch (msg)
        {
   	case CLOSE_WINDOW:
    				UnLoadHelpFile();
    				break;
        case COMMAND:
	    switch ((int)p1)
                {
                case ID_EXIT: 
  		    PostMessage(wnd, CLOSE_WINDOW, 0, 0);
                    return TRUE;
		case ID_ABOUT:
		    ProgramAboutBox ();
		    return TRUE;
		default:
		    break;

                }
	    break;
	default:
	    break;
        }

    return DefaultWndProc(wnd, msg, p1, p2);

}



