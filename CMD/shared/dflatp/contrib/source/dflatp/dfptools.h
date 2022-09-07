/* ------------- DFlat+ Tools include ----------- */
#ifndef DFPTOOLS_H
#define DFPTOOLS_H

#include "dflatp.h"


enum dftools_messages { 
    /* ------------ Legacy HelpBox dialog box ---------- */
    ID_HELPTEXT = 5000,
    ID_BACK,
    ID_PREV,
    ID_NEXT };


/* ---- Tool: INTEGRATED HELP ------------------ */



void BuildFileName(char *path, const char *fn, const char *ext);

BOOL DisplayHelp(WINDOW, char *);
void UnLoadHelpFile(void);
void LoadHelpFile(char *);

/* To use it: include in your code:
    InstallHelpProcedure (DisplayHelp);
    LoadHelpFile( "file name containing the HELP");

    The needed HUFFC.EXE and FIXHELP.EXE are also built.
    
    See the FreeDOS EDIT sources to see how to create a basic help
    file and include it within your application.
*/


/* ---- Tool: GENERIC LOGGING ------------------ */

/* Within DFlat+ you can have logging routines within your code.
   You choose the routines you want linking to different libraries.
   
   Link to:
   
   DDNLOG*.LIB     - To create a non-logging, minimum size version.
   DDLOG*.LIB			 - To use the legacy logging system
   DDLOGR*.LIB     - To create a DFlat+ Logger version
*/

/* Definitions specific to the legacy logging: */

void MessageLog(HWND);   
/* Open a dialog on window referred by HWND, which lets you start
   logging and choose the messages you want to log */
   
/* Definitions specific to the DFlat+ logger */

/* Log levels for the DFLat+ new Logger tool */
typedef enum  {
	LL_CRITICAL, LL_ERROR, LL_WARN, LL_NOTIFY
}  log_levels;

extern log_levels CurrentLogLevel;	/* Current Logging level */
extern char logstr[];

int  StartLogger ( char *LogFileName, log_levels);
		 /* start logging to this file (append)*/
int  StopLogger  ( void );
		/* Stop logging */

/* Different logging routines, depending on the number of parameters you need */
void Log ( log_levels, char *ModuleName, char *message );

#define Log1(level, module, message, p1) {  if ( sprintf(logstr,message,p1)>=0 ) \
                                              Log (level, module, logstr );}
#define Log2(level, module, message, p1, p2)  { if ( sprintf(logstr,message,p1, p2)>=0 ) \
                                              Log (level, module, logstr );}
#define Log3(level, module, message, p1, p2, p3)  { if ( sprintf(logstr,message,p1, p2, p3)>=0 ) \
                                              Log (level, module, logstr );}
#define Log4(level, module, message, p1, p2, p3, p4) {  if ( sprintf(logstr,message,p1, p2, p3, p4)>=0 ) \
                                              Log (level, module, logstr );}
#define Log5(level, module, message, p1, p2, p3, p4, p5) {  if ( sprintf(logstr,message,p1, p2, p3, p4, p5)>=0 ) \
                                              Log (level, module, logstr );}
/* Text strings for classes and messages */
char  *MessageText ( MESSAGE msg );
char  *ClassText ( CLASS cls );


extern BOOL Debug_LogMessages;					/* Log messages automatically? */
extern BOOL Debug_LogClockMessages; 		/* Log clock messages too? */




#endif
