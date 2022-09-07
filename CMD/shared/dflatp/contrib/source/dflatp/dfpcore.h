/* ------------------------------------------------------ */
/* ----- DFlat+ CORE include ---------------------------- */
/* ------------------------------------------------------ */

/* Contains core definitions necessary for the API
 * but that should NOT be used or modified by the
 * developer
 */

#ifndef DFP_CORE
#define DFP_CORE

#include <stdlib.h>
#include "portab.h"
#include "menu.h"

/* /////// INCLUDE //////////////////////////////////////// */

/* KEEP THESE ALWAYS ALIGNED WITH DFPCOMP!! */

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


/* /////// MODULE ///////////////////////////////////////// */


typedef struct ModuleDesc {
		char *Description;
		int   Ver_maj;
		int   Ver_min;
		int   Ver_rel;
		int   Ver_patch;
		char *Copyright;
		char *License;
		char *AboutComment;
} MODULE;


extern  char  VerStr [64];

#define MK_VER(a,b,c,d)   ((sprintf(VerStr,"%i.%i.%i.%i",a,b,c,d),VerStr))
#define ModuleVersion(m)  (MK_VER(m.Ver_maj,m.Ver_min,m.Ver_rel,m.Ver_patch))


/* /////// CLASS ////////////////////////////////////////// */

typedef enum window_class    {
	#define ClassDef(c,b,p,a) c,
	#include "classes.h"
	CLASSCOUNT
} CLASS;


typedef struct classdefs {
    CLASS base;                         /* base window class */
    int (*wndproc)(struct window *,MESSAGE,PARAM,PARAM);
    int attrib;
} CLASSDEFS;

extern CLASSDEFS classdefs[];


#include "dialbox.h"


/* /////// WINDOW ///////////////////////////////////////// */

enum Condition     {
    ISRESTORED, ISMINIMIZED, ISMAXIMIZED, ISCLOSING
};


typedef struct window {
    CLASS Class;           /* window class                  */
    char *title;           /* window title                  */
    int (*wndproc)
        (struct window *, MESSAGE, PARAM, PARAM);
    /* ---------------- window dimensions ----------------- */
    RECT rc;               /* window coordinates
                                            (0/0 to 79/24)  */
    int ht, wd;            /* window height and width       */
    RECT RestoredRC;       /* restored condition rect       */
    /* ----------------- window colors -------------------- */
    char WindowColors[4][2];
    /* -------------- linked list pointers ---------------- */
    struct window *parent; /* parent window                 */
    struct window *firstchild;  /* first child this parent  */
    struct window *lastchild;   /* last child this parent   */
    struct window *nextsibling; /* next sibling             */
    struct window *prevsibling; /* previous sibling         */
#if CLASSIC_WINDOW_NUMBERING	/* if enabled, select 0.7c style window list */
	/* no extra work */
#else			/* 0.7c: window list does not depend on stacking */
    struct window *numberonechild;      /* first child for list  */
    struct window *nextnumberedsibling;	/* next sibling for list */
#endif

    struct window *childfocus;	/* child that ha(s/d) focus */
    int attrib;                 /* Window attributes        */
    char *videosave;            /* video save buffer        */
    enum Condition condition;   /* Restored, Maximized,
                                   Minimized, Closing       */
    enum Condition oldcondition;/* previous condition       */
    BOOL wasCleared;
    int restored_attrib;        /* attributes when restored */
    void *extension;            /* menus, dialogs, documents, etc */
    void *wrapper;              /* used by C++ wrapper class */
    struct window *PrevMouse;   /* previous mouse capture   */
    struct window *PrevKeyboard;/* previous keyboard capture*/
    struct window *PrevClock;   /* previous clock capture   */
    struct window *MenuBarWnd;  /* menu bar                 */
    struct window *StatusBar;   /* status bar               */
    int isHelping;	        /* > 0 when help is being displayed */
    /* ----------------- text box fields ------------------ */
    int wlines;     /* number of lines of text              */
    int wtop;       /* text line that is on the top display */
    unsigned char *text; /* window text                     */
    unsigned int textlen;  /* text length                   */
    int wleft;      /* left position in window viewport     */
    int textwidth;  /* width of longest line in textbox     */
    int BlkBegLine; /* beginning line of marked block       */
    int BlkBegCol;  /* beginning column of marked block     */
    int BlkEndLine; /* ending line of marked block          */
    int BlkEndCol;  /* ending column of marked block        */
    int HScrollBox; /* position of horizontal scroll box    */
    int VScrollBox; /* position of vertical scroll box      */
    unsigned int *TextPointers; /* -> list of line offsets  */
    /* ----------------- list box fields ------------------ */
    int selection;  /* current selection                    */
    BOOL AddMode;   /* adding extended selections mode      */
    int AnchorPoint;/* anchor point for extended selections */
    int SelectCount;/* count of selected items              */
    /* ----------------- edit box fields ------------------ */
    int CurrCol;      /* Current column                     */
    int CurrLine;     /* Current line                       */
    int WndRow;       /* Current window row                 */
    BOOL TextChanged; /* TRUE if text has changed           */
    BOOL protect;     /* TRUE to display '*'                */
    unsigned char *DeletedText; /* for undo                 */
    unsigned DeletedLength; /* Length of deleted field      */
    BOOL InsertMode;   /* TRUE or FALSE for text insert     */
    BOOL WordWrapMode; /* TRUE or FALSE for word wrap       */
    unsigned int MaxTextLength; /* maximum text length      */
    /* ---------------- dialog box fields ----------------- */
    int ReturnCode;        /* return code from a dialog box */
    BOOL Modal;		   /* True if a modeless dialog box */
    CTLWINDOW *ct;	   /* control structure             */
    struct window *dfocus; /* control window that has focus */
    /* -------------- popdownmenu fields ------------------ */
    MENU *mnu;		/* points to menu structure         */
    MBAR *holdmenu; /* previous active menu                 */
    struct window *oldFocus;
    /* -------------- status bar fields ------------------- */
    BOOL TimePosted; /* True if time has been posted        */
#ifdef INCLUDE_PICTUREBOX
    /* ------------- picture box fields ------------------- */
    int VectorCount;  /* number of vectors in vector list   */
    void *VectorList; /* list of picture box vectors        */
#endif
} * WINDOW;

typedef WINDOW HWND;


/* /////// MESSAGE //////////////////////////////////////// */


typedef enum messages {
	#undef DFlatMsg
	#define DFlatMsg(m) m,
	#include "dflatmsg.h"
	MESSAGECOUNT
};


/* /////// VIDEO RESOLUTION /////////////////////////////// */

typedef struct videoresolution {
	  unsigned int HRes;
	  unsigned int VRes;
	  BOOL		 		 isGraphicMode;
	  char         Description[31];
} VideoResolution;

/* /////// COLOR SCHEME /////////////////////////////////// */

typedef struct colorscheme 
{		
		BOOL	isMonoScheme;
		unsigned char index;
		unsigned char clrArray [CLASSCOUNT] [4] [2];
} ColorScheme;

enum colortypes {
	STD_COLOR,
	SELECT_COLOR,
	FRAME_COLOR,
	HILITE_COLOR
};

enum grounds { FG, BG };

#define ColorSchemeArraySize (CLASSCOUNT*4*2)


/* /////// MISCELLANEOUS ////////////////////////////////// */

int ErrorBoxProc(WINDOW, MESSAGE, PARAM, PARAM);
int YesNoBoxProc(WINDOW, MESSAGE, PARAM, PARAM);
int MessageBoxProc(WINDOW, MESSAGE, PARAM, PARAM);


#endif
