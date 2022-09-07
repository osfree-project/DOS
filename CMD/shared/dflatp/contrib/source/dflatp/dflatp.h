/* ------------------------------------------------------ */
/* ----- DFlat+ API include ----------------------------- */
/* ------------------------------------------------------ */

#ifndef DFLATP_H
#define DFLATP_H


/* /////// DESCRIPTION /////////////////////////////////// */


/* DFlat+ application developer API
 * Use freely the definitions given here to design your
 * own application
 */

/* /////// INCLUDES ///////////////////////////////////// */

#include "system.h"    /* OS routines and definitions */


/* /////// DATA TYPES /////////////////////////////////// */


typedef unsigned int MESSAGE;
typedef long PARAM;
typedef PARAM UCOMMAND;


#include "dfpcore.h"
/* Above there goes the definition of:
   MODULE            A programming unit (Program or Library)
   HWND              Handle to a window
   CLASS             Class (number)
   ColorScheme       A color combination for the UI
   VideoResolution   A screen mode resolution   
 */   

/* ---- types of vectors that can be in a picture box ------- */
enum VectTypes {VECTOR, SOLIDBAR, HEAVYBAR, CROSSBAR, LIGHTBAR};

/* /////// CONSTANTS /////////////////////////////////// */

/*
   Class list:       see classes.h
   System Messages:  see dflatmsg.h
*/   

extern char *ClassNames[];

#include "keys.h"					/* Keyboard constants */
#include "commands.h"			/* UCommand constants */

	/* Modules */
extern MODULE ProgramModule;  /* Must be created by developer */
extern MODULE DFlatpModule;

	/* Module version strings (fmt x.y.z.t) */
#define ProgramVersion    (ModuleVersion(ProgramModule))
#define DFlatpVersion     (ModuleVersion(DFlatpModule))

	/* System color schemes */
extern ColorScheme color;
extern ColorScheme bw;
extern ColorScheme reverse;

	/* System screen resolutions */
extern  VideoResolution  TXT25;
extern  VideoResolution  TXT43;
extern  VideoResolution  TXT50;

	/* Window attributes */
#define SHADOW       0x0001
#define MOVEABLE     0x0002
#define SIZEABLE     0x0004
#define HASMENUBAR   0x0008
#define VSCROLLBAR   0x0010
#define HSCROLLBAR   0x0020
#define VISIBLE      0x0040
#define SAVESELF     0x0080
#define HASTITLEBAR  0x0100
#define CONTROLBOX   0x0200
#define MINMAXBOX    0x0400
#define NOCLIP       0x0800
#define READONLY     0x1000
#define MULTILINE    0x2000
#define HASBORDER    0x4000
#define HASSTATUSBAR 0x8000


/* /////// UI System Enhancements ////////////////////// */


	/* Memory allocation */
void *DFcalloc(size_t, size_t);
void *DFmalloc(size_t);
void *DFrealloc(void *, size_t);

	/* Critical error detection */
int TestCriticalError(void);

	/* Manipulate the snowy flag (CGA screens) */
BOOL GetSnowyFlag ( void );
void SetSnowyFlag ( BOOL );

	/* Select resolution and color schemes */
void SelectLines(VideoResolution);
BOOL SelectColorScheme (ColorScheme);



/* /////// APPLICATION ENTRY POINT (to be implemented)// */

int DfpMain(int argc, char *argv[]);		


/* /////// SYSTEM CONFIGURATION //////////////////////// */

typedef struct sysconfigtype {
		ColorScheme      VideoCurrentColorScheme;	  /* Read-only */
		VideoResolution	 VideoCurrentResolution;    /* Read-only */
		BOOL						 VideoSnowyFlag;            /* Read-only */
		unsigned char    CountryTimeSeparator;      /* Read-write */
		unsigned char    EditorTabSize;             /* Read-write */
		BOOL             EditorGlobalReadOnly;      /* Read-write */
} SysConfigType;
	

/* Please be careful and respect the read-only/write note above.
   If you wish to modify the read-only attributes, use the given
   functions to do so.  */
extern SysConfigType SysConfig;


/* /////// MESSAGING SYSTEM //////////////////////////// */

	/* Message sending */
void PostMessage(HWND, MESSAGE, PARAM, PARAM);
int SendMessage(HWND, MESSAGE, PARAM, PARAM);

	/* Multitasking */
void ProcessMessages (void);		/* once finished init, let messages flow */
void Cooperate(void);						/* momentarily process pending messages  */


/* /////// CLASSES ///////////////////////////////////// */


#define BaseWndProc(Class,wnd,msg,p1,p2)    \
    (*classdefs[(classdefs[Class].base)].wndproc)(wnd,msg,p1,p2)

#define DefaultWndProc(wnd,msg,p1,p2)         \
	(classdefs[wnd->Class].wndproc == NULL) ? \
	BaseWndProc(wnd->Class,wnd,msg,p1,p2) :	  \
    (*classdefs[wnd->Class].wndproc)(wnd,msg,p1,p2)


/* /////// WINDOW METHODS ////////////////////////////// */

/* ------- window manipulation ------ */

HWND CreateWindow(CLASS,const char *,int,int,int,int,void*,HWND,
       int (*)(struct window *,MESSAGE,PARAM,PARAM),int);

BOOL isDerivedFrom(HWND, CLASS);
#define GetClass(w)          ((w)->Class)


/* ------- color manipulation ------- */

	/* Get colors defined for a window */
#define WndForeground(wnd) 		\
	(wnd->WindowColors [STD_COLOR] [FG])
#define WndBackground(wnd) 		\
	(wnd->WindowColors [STD_COLOR] [BG])
#define FrameForeground(wnd) 	\
	(wnd->WindowColors [FRAME_COLOR] [FG])
#define FrameBackground(wnd) 	\
	(wnd->WindowColors [FRAME_COLOR] [BG])
#define SelectForeground(wnd) 	\
	(wnd->WindowColors [SELECT_COLOR] [FG])
#define SelectBackground(wnd) 	\
	(wnd->WindowColors [SELECT_COLOR] [BG])
#define HighlightForeground(wnd) 	\
	(wnd->WindowColors [HILITE_COLOR] [FG])
#define HighlightBackground(wnd) 	\
	(wnd->WindowColors [HILITE_COLOR] [BG])

	/* Set colors defined for a window */
#define WindowClientColor(wnd, fg, bg) 	\
		WndForeground(wnd) = fg, WndBackground(wnd) = bg
#define WindowReverseColor(wnd, fg, bg) \
		SelectForeground(wnd) = fg, SelectBackground(wnd) = bg
#define WindowFrameColor(wnd, fg, bg) \
		FrameForeground(wnd) = fg, FrameBackground(wnd) = bg
#define WindowHighlightColor(wnd, fg, bg) \
		HighlightForeground(wnd) = fg, HighlightBackground(wnd) = bg



/* ------- window and client coords - */
#define WindowHeight(w)      ((w)->ht)
#define WindowWidth(w)       ((w)->wd)
#define BorderAdj(w)         (TestAttribute(w,HASBORDER)?1:0)
#define BottomBorderAdj(w)   (TestAttribute(w,HASSTATUSBAR)?1:BorderAdj(w))
#define TopBorderAdj(w)      ((TestAttribute(w,HASTITLEBAR) &&   \
                              TestAttribute(w,HASMENUBAR)) ?  \
                              2 : (TestAttribute(w,HASTITLEBAR | \
                              HASMENUBAR | HASBORDER) ? 1 : 0))
#define ClientWidth(w)       (WindowWidth(w)-BorderAdj(w)*2)
#define ClientHeight(w)      (WindowHeight(w)-TopBorderAdj(w)-\
                              BottomBorderAdj(w))
#define WindowRect(w)        ((w)->rc)
#define GetTop(w)            (RectTop(WindowRect(w)))
#define GetBottom(w)         (RectBottom(WindowRect(w)))
#define GetLeft(w)           (RectLeft(WindowRect(w)))
#define GetRight(w)          (RectRight(WindowRect(w)))
#define GetClientTop(w)      (GetTop(w)+TopBorderAdj(w))
#define GetClientBottom(w)   (GetBottom(w)-BottomBorderAdj(w))
#define GetClientLeft(w)     (GetLeft(w)+BorderAdj(w))
#define GetClientRight(w)    (GetRight(w)-BorderAdj(w))

RECT ClientRect(HWND);
RECT RelativeWindowRect(HWND, RECT);

RECT ClipRectangle(HWND, RECT);
RECT AdjustRectangle(HWND, RECT);


/* ------- window attributes and title - */

void AddTitle(HWND, const char *);
void DisplayTitle(HWND, RECT *);
#define GetTitle(w)          ((w)->title)

#define GetAttribute(w)      ((w)->attrib)
#define AddAttribute(w,a)    (GetAttribute(w) |= a)
#define ClearAttribute(w,a)  (GetAttribute(w) &= ~(a))
#define TestAttribute(w,a)   (GetAttribute(w) & (a))
#define isHidden(w)          (!(GetAttribute(w) & VISIBLE))
#define SetVisible(w)        (GetAttribute(w) |= VISIBLE)
#define ClearVisible(w)      (GetAttribute(w) &= ~VISIBLE)

BOOL isVisible(HWND);

extern BOOL WindowMoving;
extern BOOL WindowSizing;
extern BOOL VSliding;
extern BOOL HSliding;


/* ------- painting and content ----- */

extern int foreground, background;

void SetStandardColor(HWND);
void SetReverseColor(HWND);

void RepaintBorder(HWND, RECT *);
void PaintShadow(HWND);
void ClearWindow(HWND, RECT *, int);
void writeline(HWND, char *, int, int, BOOL);
#define gotoxy(w,x,y) cursor(w->rc.lf+(x)+1,w->rc.tp+(y)+1)

extern BOOL ClipString;

BOOL CharInView(HWND, int, int);
void PutWindowChar(HWND,int,int,int);
void PutWindowLine(HWND, void *,int,int);


/* ------- object hierarchy/MDI ----- */

HWND GetAncestor(HWND);
BOOL isAncestor(HWND, HWND);

#define GetParent(w)         ((w)->parent)
#define FirstWindow(w)       ((w)->firstchild)

#define NumberOneChildWindow(w)	((w)->numberonechild)
#define NextNumberedWindow(w)	((w)->nextnumberedsibling)
#define LastWindow(w)        ((w)->lastchild)
#define NextWindow(w)        ((w)->nextsibling)
#define PrevWindow(w)        ((w)->prevsibling)

void RemoveWindow(HWND);
void AppendWindow(HWND);

void ChooseWindow(HWND, int);
void CloseAll(HWND, int);


/* ------- Window focus ------------- */

#define FocusedWindow(w)     ((w)->childfocus)
HWND GetDocFocus(void);

void SetNextFocus(void);
void SetPrevFocus(void);

void ReFocus(HWND);


/* /////// OTHER CLASSES' METHODS ////////////////////// */


/* --------- menu prototypes ---------- */
BOOL isActive(MBAR *, int);
char *GetCommandText(MBAR *, int);
void ActivateCommand(MBAR *,int);
void DeactivateCommand(MBAR *,int);
BOOL GetCommandToggle(MBAR *,int);
void SetCommandToggle(MBAR *,int);
void ClearCommandToggle(MBAR *,int);
void InvertCommandToggle(MBAR *,int);

extern int CurrentMenuSelection;


/* ------------- list box prototypes -------------- */
BOOL ItemSelected(HWND, int);

/* -------- text box prototypes ---------- */
#define TextLine(wnd, sel) \
      (wnd->text + *((wnd->TextPointers) + sel))
void WriteTextLine(HWND, RECT *, int, BOOL);
#define TextBlockMarked(wnd) (  wnd->BlkBegLine ||    \
                                wnd->BlkEndLine ||    \
                                wnd->BlkBegCol  ||    \
                                wnd->BlkEndCol)
void MarkTextBlock(HWND, int, int, int, int);
#define ClearTextBlock(wnd) wnd->BlkBegLine = wnd->BlkEndLine =  \
                        wnd->BlkBegCol  = wnd->BlkEndCol = 0;
#define TextBlockBegin(wnd) (TextLine(wnd,wnd->BlkBegLine)+wnd->BlkBegCol)
#define TextBlockEnd(wnd)   (TextLine(wnd,wnd->BlkEndLine)+wnd->BlkEndCol)
#define GetText(w)        ((w)->text)
#define GetTextLines(w)   ((w)->wlines)
void ClearTextPointers(HWND);
void BuildTextPointers(HWND);
int TextLineNumber(HWND, char *);
void UpCaseMarked(HWND);		/* new 0.7d */
void DownCaseMarked(HWND);		/* new 0.7d */
void StatsForMarked(HWND, unsigned *, unsigned *, unsigned *); /* new 0.7d */

/* ------------- edit box prototypes ----------- */
#define CurrChar (TextLine(wnd, wnd->CurrLine)+wnd->CurrCol)
#define WndCol   (wnd->CurrCol-wnd->wleft)
#define isMultiLine(wnd) TestAttribute(wnd, MULTILINE)
#define SetProtected(wnd) (wnd)->protect=TRUE

void SearchText(HWND);
void ReplaceText(HWND);
void SearchNext(HWND);

/* ------------- picture box prototypes ------------- */
void DrawVector(HWND, int, int, int, int);
void DrawBox(HWND, int, int, int, int);
void DrawBar(HWND, enum VectTypes, int, int, int, int);
HWND WatchIcon(void);


/* /////// DIALOG BOXES  /////////////////////////////// */


BOOL DialogBox(HWND, DBOX *, BOOL,
       int (*)(struct window *, MESSAGE, PARAM, PARAM));
void ClearDialogBoxes(void);
void GetDlgListText(HWND, char *, UCOMMAND);
BOOL RadioButtonSetting(DBOX *, UCOMMAND);
void PushRadioButton(DBOX *, UCOMMAND);
void PutItemText(HWND, UCOMMAND, char *);
void PutComboListText(HWND, UCOMMAND, char *);
void GetItemText(HWND, UCOMMAND, char *, int);
char *GetDlgTextString(DBOX *, UCOMMAND, CLASS);
void SetDlgTextString(DBOX *, UCOMMAND, char *, CLASS);
BOOL CheckBoxSetting(DBOX *, UCOMMAND);
CTLWINDOW *FindCommand(DBOX *, UCOMMAND, int);
HWND ControlWindow(const DBOX *, UCOMMAND);
void SetRadioButton(DBOX *, CTLWINDOW *);
void ControlSetting(DBOX *, UCOMMAND, int, int);
BOOL isControlOn(DBOX *, UCOMMAND, int);
void SetFocusCursor(HWND);

#define GetControl(wnd)             (wnd->ct)
#define GetDlgText(db, cmd)         GetDlgTextString(db, cmd, TEXT)
#define GetDlgTextBox(db, cmd)      GetDlgTextString(db, cmd, TEXTBOX)
#define GetEditBoxText(db, cmd)     GetDlgTextString(db, cmd, EDITBOX)
#define GetComboBoxText(db, cmd)    GetDlgTextString(db, cmd, COMBOBOX)
#define SetDlgText(db, cmd, s)      SetDlgTextString(db, cmd, s, TEXT)
#define SetDlgTextBox(db, cmd, s)   SetDlgTextString(db, cmd, s, TEXTBOX)
#define SetEditBoxText(db, cmd, s)  SetDlgTextString(db, cmd, s, EDITBOX)
#define SetComboBoxText(db, cmd, s) SetDlgTextString(db, cmd, s, COMBOBOX)
#define SetDlgTitle(db, ttl)        ((db)->dwnd.title = ttl)
#define SetCheckBox(db, cmd)        ControlSetting(db, cmd, CHECKBOX, ON)
#define ClearCheckBox(db, cmd)      ControlSetting(db, cmd, CHECKBOX, OFF)
#define EnableButton(db, cmd)       ControlSetting(db, cmd, BUTTON, ON)
#define DisableButton(db, cmd)      ControlSetting(db, cmd, BUTTON, OFF)
#define ButtonEnabled(db, cmd)      isControlOn(db, cmd, BUTTON)
#define CheckBoxEnabled(db, cmd)    isControlOn(db, cmd, CHECKBOX)


/* /////// MESSAGE BOXES  ////////////////////////////// */

HWND SliderBox(int, char *, char *);
BOOL InputBox(HWND, char *, char *, char *, int, int);
BOOL GenericMessage(HWND, char *, char *, int,
	int (*)(struct window *, MESSAGE, PARAM, PARAM),
	char *, char *, int, int, int);
#define TestErrorMessage(msg)	\
	GenericMessage(NULL, "Error", msg, 2, ErrorBoxProc,	  \
		Ok, Cancel, ID_OK, ID_CANCEL, TRUE)
#define ErrorMessage(msg) \
	GenericMessage(NULL, "Error", msg, 1, ErrorBoxProc,   \
		Ok, NULL, ID_OK, 0, TRUE)
#define MessageBox(ttl, msg) \
	GenericMessage(NULL, ttl, msg, 1, MessageBoxProc, \
		Ok, NULL, ID_OK, 0, TRUE)
#define YesNoBox(msg)	\
	GenericMessage(NULL, NULL, msg, 2, YesNoBoxProc,   \
		Yes, No, ID_OK, ID_CANCEL, TRUE)
#define CancelBox(wnd, msg) \
	GenericMessage(wnd, "Wait...", msg, 1, CancelBoxProc, \
		Cancel, NULL, ID_CANCEL, 0, FALSE)
void CloseCancelBox(void);
HWND MomentaryMessage(char *);


/* /////// COMMON DIALOGS ////////////////////////////// */


void ProgramAboutBox ( void );
void DFlatpAboutBox ( void );

BOOL OpenFileDialogBox(char *, char *);
BOOL SaveAsDialogBox(char *, char *, char *);

void DisplayProperties ( HWND );

void ExecuteNonDFP (char *);

void MoreWindows(HWND);


/* /////// CLIPBOARD  ////////////////////////////////// */

void CopyTextToClipboard(char *);
void CopyToClipboard(HWND);
#define PasteFromClipboard(wnd) PasteText(wnd,Clipboard,ClipboardLength)
BOOL PasteText(HWND, char *, unsigned);
void ClearClipboard(void);


/* /////// DFLAT+ HOOKS  /////////////////////////////// */


/* ------------- help system --------------------- */
BOOL SystemHelp(HWND w, char *topic);
BOOL InstallHelpProcedure ( BOOL (* f) () );

/* -------------- message logging system -------- */
BOOL LogMessageStart ( WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2 );
BOOL LogMessageEnd ( WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2 );



/* /////// WILL BE DEPRECATED (DO NOT USE!!) /////////// */


char *WindowName(HWND wnd);
void SkipApplicationControls(void);
extern HWND inFocus;
extern HWND oldFocus;

#define CHANGECOLOR  (unsigned char) 19 /* prefix to change colors  (old: 174) */
#define RESETCOLOR   (unsigned char) 23 /* reset colors to default  (old: 175) */
#define LISTSELECTOR   4    /* selected list box entry      */

extern char *Clipboard;
extern unsigned ClipboardLength;


/* /////// END  //////////////////////////////////////// */

#endif

