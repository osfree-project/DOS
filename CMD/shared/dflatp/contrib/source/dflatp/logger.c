/* ------------ logger .c ------------ */


//#ifdef DFLATP_LOG

#include <dos.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dflatp.h"
#include "dfptools.h"
#include "time.h"



BOOL LogMessageStart ( WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2 );
BOOL LogMessageEnd ( WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2 );


char logstr[512];
log_levels CurrentLogLevel = LL_CRITICAL;
BOOL Debug_LogMessages = FALSE;
BOOL Debug_LogClockMessages = FALSE;

FILE *LogFile;


#ifdef __WATCOMC__
void Log ( log_levels L, char *ModuleName, char *message )
{
  time_t rawtime;
  char times[27];
  struct dostime_t t;
  struct dosdate_t d;

	if ( (LogFile != NULL) && (L<=CurrentLogLevel) )
	{

			_dos_gettime (&t);
			_dos_getdate (&d);

			strcpy ( times, ctime (&rawtime)); times [24]= 0;
      fprintf (LogFile, "%4d%02d%02d %02d:%02d:%02d.%02d [%s] %s\n", 
      			d.year, d.month, d.day, 
      			t.hour, t.minute, t.second, t.hsecond, ModuleName, message);
      fflush ( LogFile );
	}
}
#else
void Log ( log_levels L, char *ModuleName, char *message )
{
  time_t rawtime;
  char times[27];
  struct time t;
  struct date d;

	if ( (LogFile != NULL) && (L<=CurrentLogLevel) )
	{

			gettime (&t);
			getdate (&d);

			strcpy ( times, ctime (&rawtime)); times [24]= 0;
      fprintf (LogFile, "%4d%02d%02d %02d:%02d:%02d.%02d [%s] %s\n", 
      			d.da_year, d.da_mon, d.da_day, 
      			t.ti_hour, t.ti_min, t.ti_sec, t.ti_hund, ModuleName, message);
      fflush ( LogFile );
	}
}
#endif



int  StartLogger ( char *LogFileName, log_levels Initial)
{
	LogFile = fopen (LogFileName, "awt");
  CurrentLogLevel = Initial;
	Log (LL_CRITICAL, "Logger", "--- Logging started ---");

	return ( LogFile != NULL);
//	if ( LogFile != NULL )
//			return SetSystemMessageLoggerStart ( LogMessageStart ) &&  SetSystemMessageLoggerEnd ( LogMessageEnd );
//	else
//			return FALSE;
}

int  StopLogger  ( void )
{
	Log (LL_CRITICAL, "Logger", "--- Logging finished ---");
//	SetSystemMessageLoggerStart ( DefaultMessageLog );
//	SetSystemMessageLoggerEnd ( DefaultMessageLog );
	return  fclose (LogFile);
}

static char s[50];
char  *MessageText ( MESSAGE msg )
{
//	return "SSS";
	switch (msg) {
                  case START                  : return "START                  ";
                  case STOP                   : return "STOP                   ";
                  case COMMAND                : return "COMMAND                ";
                  case CREATE_WINDOW          : return "CREATE_WINDOW          ";
                  case OPEN_WINDOW            : return "OPEN_WINDOW            ";
                  case SHOW_WINDOW            : return "SHOW_WINDOW            ";
                  case HIDE_WINDOW            : return "HIDE_WINDOW            ";
                  case CLOSE_WINDOW           : return "CLOSE_WINDOW           ";
                  case SETFOCUS               : return "SETFOCUS               ";
                  case KILLFOCUS							: return "KILLFOCUS              ";
                  case PAINT                  : return "PAINT                  ";
                  case BORDER                 : return "BORDER                 ";
                  case TITLE                  : return "TITLE                  ";
                  case MOVE                   : return "MOVE                   ";
                  case SIZE                   : return "SIZE                   ";
                  case MAXIMIZE               : return "MAXIMIZE               ";
                  case MINIMIZE               : return "MINIMIZE               ";
                  case RESTORE                : return "RESTORE                ";
                  case INSIDE_WINDOW          : return "INSIDE_WINDOW          ";
                  case DEADCHILD              : return "DEADCHILD              ";
                  case CLOCKTICK              : return "CLOCKTICK              ";
                  case CAPTURE_CLOCK          : return "CAPTURE_CLOCK          ";
                  case RELEASE_CLOCK          : return "RELEASE_CLOCK          ";
                  case KEYBOARD               : return "KEYBOARD               ";
                  case CAPTURE_KEYBOARD       : return "CAPTURE_KEYBOARD       ";
                  case RELEASE_KEYBOARD       : return "RELEASE_KEYBOARD       ";
                  case KEYBOARD_CURSOR        : return "KEYBOARD_CURSOR        ";
                  case CURRENT_KEYBOARD_CURSOR: return "CURRENT_KEYBOARD_CURSOR";
                  case HIDE_CURSOR            : return "HIDE_CURSOR            ";
                  case SHOW_CURSOR            : return "SHOW_CURSOR            ";
                  case SAVE_CURSOR            : return "SAVE_CURSOR            ";
                  case RESTORE_CURSOR         : return "RESTORE_CURSOR         ";
                  case SHIFT_CHANGED          : return "SHIFT_CHANGED          ";
                  case WAITKEYBOARD           : return "WAITKEYBOARD           ";
                  case RESET_MOUSE            : return "RESET_MOUSE            ";
                  case MOUSE_TRAVEL           : return "MOUSE_TRAVEL           ";
                  case MOUSE_INSTALLED        : return "MOUSE_INSTALLED        ";
                  case RIGHT_BUTTON           : return "RIGHT_BUTTON           ";
                  case LEFT_BUTTON            : return "LEFT_BUTTON            ";
                  case DOUBLE_CLICK           : return "DOUBLE_CLICK           ";
                  case MOUSE_MOVED            : return "MOUSE_MOVED            ";
                  case BUTTON_RELEASED        : return "BUTTON_RELEASED        ";
                  case CURRENT_MOUSE_CURSOR   : return "CURRENT_MOUSE_CURSOR   ";
                  case MOUSE_CURSOR           : return "MOUSE_CURSOR           ";
                  case SHOW_MOUSE             : return "SHOW_MOUSE             ";
                  case HIDE_MOUSE             : return "HIDE_MOUSE             ";
                  case WAITMOUSE              : return "WAITMOUSE              ";
                  case TESTMOUSE              : return "TESTMOUSE              ";
                  case CAPTURE_MOUSE          : return "CAPTURE_MOUSE          ";
                  case RELEASE_MOUSE          : return "RELEASE_MOUSE          ";
                  case ADDTEXT                : return "ADDTEXT                ";
                  case INSERTTEXT             : return "INSERTTEXT             ";
                  case DELETETEXT             : return "DELETETEXT             ";
                  case CLEARTEXT              : return "CLEARTEXT              ";
                  case SETTEXT                : return "SETTEXT                ";
                  case SCROLL                 : return "SCROLL                 ";
                  case HORIZSCROLL            : return "HORIZSCROLL            ";
                  case SCROLLPAGE             : return "SCROLLPAGE             ";
                  case HORIZPAGE              : return "HORIZPAGE              ";
                  case SCROLLDOC              : return "SCROLLDOC              ";
                  case GETTEXT                : return "GETTEXT                ";
                  case SETTEXTLENGTH          : return "SETTEXTLENGTH          ";
                  case BUILDMENU              : return "BUILDMENU              ";
                  case MB_SELECTION           : return "MB_SELECTION           ";
                  case BUILD_SELECTIONS       : return "BUILD_SELECTIONS       ";
                  case CLOSE_POPDOWN          : return "CLOSE_POPDOWN          ";
                  case LB_SELECTION           : return "LB_SELECTION           ";
                  case LB_CHILDSELECTION      : return "LB_CHILDSELECTION      ";
                  case LB_CHOOSE              : return "LB_CHOOSE              ";
                  case LB_CURRENTSELECTION    : return "LB_CURRENTSELECTION    ";
                  case LB_GETTEXT             : return "LB_GETTEXT             ";
                  case LB_SETSELECTION        : return "LB_SETSELECTION        ";
                  case INITIATE_DIALOG        : return "INITIATE_DIALOG        ";
                  case ENTERFOCUS             : return "ENTERFOCUS             ";
                  case LEAVEFOCUS             : return "LEAVEFOCUS             ";
                  case ENDDIALOG              : return "ENDDIALOG              ";
                  case DISPLAY_HELP           : return "DISPLAY_HELP           ";
                  case ADDSTATUS              : return "ADDSTATUS              ";
                  case DRAWVECTOR             : return "DRAWVECTOR             ";
                  case DRAWBOX                : return "DRAWBOX                ";
                  case DRAWBAR                : return "DRAWBAR                ";
									default:  sprintf (s, "%i", msg); return s;
		}
}


static char s2[50];
char  *ClassText ( CLASS cls )
{
	switch (cls) {
                 case NORMAL     : return "NORMAL     ";
                 case APPLICATION: return "APPLICATION";
                 case TEXTBOX    : return "TEXTBOX    ";
                 case LISTBOX    : return "LISTBOX    ";
                 case EDITBOX    : return "EDITBOX    ";
                 case MENUBAR    : return "MENUBAR    ";
                 case POPDOWNMENU: return "POPDOWNMENU";
                 case PICTUREBOX : return "PICTUREBOX ";
                 case DIALOG     : return "DIALOG     ";
                 case BOX        : return "BOX        ";
                 case BUTTON     : return "BUTTON     ";
                 case COMBOBOX   : return "COMBOBOX   ";
                 case TEXT       : return "TEXT       ";
                 case RADIOBUTTON: return "RADIOBUTTON";
                 case CHECKBOX   : return "CHECKBOX   ";
                 case SPINBUTTON : return "SPINBUTTON ";
                 case ERRORBOX   : return "ERRORBOX   ";
                 case MESSAGEBOX : return "MESSAGEBOX ";
                 case HELPBOX    : return "HELPBOX    ";
                 case STATUSBAR  : return "STATUSBAR  ";
//                 case EDITOR     : return "EDITOR     ";
                 case TITLEBAR   : return "TITLEBAR   ";
                 case DUMMY      : return "DUMMY      ";
                 default: sprintf (s2, "%i", cls); return s2;
		}
}


static void LogMessage ( char * SectionName, WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2 )
{
			if ( wnd != NULL )
  				Log5 (LL_NOTIFY, SectionName, "Wnd[%ld] Class[%s] Msg[%s], P1[%ld], P2[%ld]", wnd, ClassText(GetClass(wnd)), MessageText(msg), p1, p2)
			else  				
  				Log3 (LL_NOTIFY, SectionName, "SysMsg Msg[%s], P1[%ld], P2[%ld]", MessageText(msg), p1, p2);
}


BOOL LogMessageStart ( WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2 )
{
    if (Debug_LogMessages)
    	if  ( Debug_LogClockMessages ||  (msg != CLOCKTICK) )
					LogMessage ( "MsgSysStart", wnd, msg, p1, p2);
		return TRUE;
}


BOOL LogMessageEnd ( WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2 )
{
    if (Debug_LogMessages)
    	if  ( Debug_LogClockMessages ||  (msg != CLOCKTICK) )
					LogMessage ( "MsgSysEnd", wnd, msg, p1, p2);
		return TRUE;
}





//#endif
