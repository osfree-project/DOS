/* ------------------------------------------------------ */
/* ----- DFlat+ Compilation include --------------------- */
/* ------------------------------------------------------ */

#ifndef DFP_COMPILE
#define DFP_COMPILE


/* /////// DESCRIPTION /////////////////////////////////// */


/* DFlat+ library compilation include
 * All the internal cross-references between modules.
 */

/* /////// GLOBAL DEFINES /////////////////////////////// */


/* NOTE: Future versions will include these by default.
         Do not alter/rely on them                        */

#define INCLUDE_MULTI_WINDOWS   /* MDI */
#define INCLUDE_SHELLDOS        /* Hability to run DOS apps */
#define INCLUDE_MINIMIZE
#define INCLUDE_MAXIMIZE
#define INCLUDE_RESTORE
#define INCLUDE_EXTENDEDSELECTIONS  /* Multiline text boxes */
#define USECBRKHNLDR 1 /* removing this line disables ctrl-break processing */
#define CLASSIC_WINDOW_NUMBERING 0  /* 0= stack-independent ordering */

	/* Components */
#define INCLUDE_PICTUREBOX


/* /////// INCLUDES  //////////////////////////////////// */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <process.h>
#include <conio.h>
#include <bios.h>
#include <ctype.h>
#include <io.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <time.h>
#include <setjmp.h>
#include "dflatp.h"
#include "sysint.h"
#include "video.h"


/* /////// CONSTANTS //////////////////////////////////// */


#define MAXMESSAGES 100
#define DELAYTICKS 1
#define FIRSTDELAY 7
#define DOUBLETICKS 5

#define MAXTEXTLEN 65000U /* maximum text buffer            */
#define EDITLEN     1024  /* starting length for multiliner */
#define ENTRYLEN     256  /* starting length for one-liner  */
#define GROWLENGTH    64  /* buffers grow by this much      */


#define ICONHEIGHT 3			/* Minimized window size */
#define ICONWIDTH  10


/* --------- space between menubar labels --------- */
#define MSPACE 2
/* --------------- border characters ------------- */
#define FOCUS_NW      (unsigned char) '\xda'     /* \xc9 */
#define FOCUS_NE      (unsigned char) '\xbf'     /* \xbb */
#define FOCUS_SE      (unsigned char) '\xd9'     /* \xbc */
#define FOCUS_SW      (unsigned char) '\xc0'     /* \xc8 */
#define FOCUS_SIDE    (unsigned char) '\xb3'     /* \xba */
#define FOCUS_LINE    (unsigned char) '\xc4'     /* \xcd */
#define NW            (unsigned char) '\xda'
#define NE            (unsigned char) '\xbf'
#define SE            (unsigned char) '\xd9'
#define SW            (unsigned char) '\xc0'
#define SIDE          (unsigned char) '\xb3'
#define LINE          (unsigned char) '\xc4'
#define LEDGE         (unsigned char) '\xc3'
#define REDGE         (unsigned char) '\xb4'
#define SIZETOKEN     (unsigned char) '\x04'
/* ------------- scroll bar characters ------------ */
#define UPSCROLLBOX    (unsigned char) '\x1e'
#define DOWNSCROLLBOX  (unsigned char) '\x1f'
#define LEFTSCROLLBOX  (unsigned char) '\x11'
#define RIGHTSCROLLBOX (unsigned char) '\x10'
#define SCROLLBARCHAR  (unsigned char) 176 
#define SCROLLBOXCHAR  (unsigned char) 178
/* ------------------ menu characters --------------------- */
#define CHECKMARK      (unsigned char) (SCREENHEIGHT==25?251:4)
#define CASCADEPOINTER (unsigned char) '\x10'
/* ----------------- title bar characters ----------------- */
#define CONTROLBOXCHAR (unsigned char) '\xf0'
#define MAXPOINTER     24      /* maximize token            */
#define MINPOINTER     25      /* minimize token            */
#define RESTOREPOINTER 18      /* restore token             */
/* --------------- text control characters ---------------- */
#define APPLCHAR     (unsigned char) 176 /* fills application window */
#define SHORTCUTCHAR '~'    /* prefix: shortcut key display */
#define LISTSELECTOR   4    /* selected list box entry      */

/* /////// VARIABLES //////////////////////////////////// */

extern WINDOW ApplicationWindow;

extern WINDOW inFocus;
extern WINDOW oldFocus;

extern WINDOW CaptureMouse;
extern WINDOW CaptureKeyboard;

extern MODULE ProgramModule;
extern MODULE DFlatpModule;

extern char *Clipboard;
extern unsigned ClipboardLength;

extern BOOL ClipString;


/* /////// METHODS  ///////////////////////////////////// */


/* --------- system enhancements ---------- */
void SetScreenHeight(int);

/* --------- modules  --------------------- */
extern  char  VerStr [64];
#define MK_VER(a,b,c,d)   ((sprintf(VerStr,"%i.%i.%i.%i",a,b,c,d),VerStr))
#define ModuleVersion(m)  (MK_VER(m.Ver_maj,m.Ver_min,m.Ver_rel,m.Ver_patch))


/* --------- windows  --------------------- */
void InsertTitle(WINDOW, const char *);
void InitWindowColors(WINDOW);
char *WindowName(WINDOW wnd);
void SkipApplicationControls(void);
void CreateStatusBar(WINDOW);


/* --------- window printing -------------- */
#define SwapVideoBuffer(wnd, ish, fh) swapvideo(wnd, wnd->videosave, ish, fh)
int LineLength(char *);
int MsgHeight(char *);
int MsgWidth(char *);


/* --------- messages  -------------------- */
BOOL init_messages(void);
BOOL dispatch_message(void);


/* --------- menus  ------------------- */
int CopyCommand(unsigned char *, unsigned char *, int, int);
void BuildSystemMenu(WINDOW);
BOOL isCascadedCommand(MBAR *,int);
BOOL isCascadedCommand2(MENU *, int);
void CreateMenu(WINDOW);


/* --------- other components ------------- */
void SetScrollBars(WINDOW);
#define HitControlBox(wnd, p1, p2)     \
     (TestAttribute(wnd, CONTROLBOX) && \
     p1 == 2 && p2 == 0)
void CustomizeDisplayPropBox ( void );


/* ---- standard window message processing prototypes ----- */
int ApplicationProc(WINDOW, MESSAGE, PARAM, PARAM);
int NormalProc(WINDOW, MESSAGE, PARAM, PARAM);
int TextBoxProc(WINDOW, MESSAGE, PARAM, PARAM);
int ListBoxProc(WINDOW, MESSAGE, PARAM, PARAM);
int EditBoxProc(WINDOW, MESSAGE, PARAM, PARAM);
int PictureProc(WINDOW, MESSAGE, PARAM, PARAM);
int MenuBarProc(WINDOW, MESSAGE, PARAM, PARAM);
int PopDownProc(WINDOW, MESSAGE, PARAM, PARAM);
int ButtonProc(WINDOW, MESSAGE, PARAM, PARAM);
int ComboProc(WINDOW, MESSAGE, PARAM, PARAM);
int TextProc(WINDOW, MESSAGE, PARAM, PARAM);
int RadioButtonProc(WINDOW, MESSAGE, PARAM, PARAM);
int CheckBoxProc(WINDOW, MESSAGE, PARAM, PARAM);
int SpinButtonProc(WINDOW, MESSAGE, PARAM, PARAM);
int BoxProc(WINDOW, MESSAGE, PARAM, PARAM);
int DialogProc(WINDOW, MESSAGE, PARAM, PARAM);
int SystemMenuProc(WINDOW, MESSAGE, PARAM, PARAM);
int HelpBoxProc(WINDOW, MESSAGE, PARAM, PARAM);
int MessageBoxProc(WINDOW, MESSAGE, PARAM, PARAM);
int CancelBoxProc(WINDOW, MESSAGE, PARAM, PARAM);
int ErrorBoxProc(WINDOW, MESSAGE, PARAM, PARAM);
int YesNoBoxProc(WINDOW, MESSAGE, PARAM, PARAM);
int StatusBarProc(WINDOW, MESSAGE, PARAM, PARAM);
int WatchIconProc(WINDOW, MESSAGE, PARAM, PARAM);

#endif

