/* ------------- applicat.c ------------- */

#include "dfpcomp.h"

int ScreenHeight;
WINDOW ApplicationWindow = NULL;
extern DBOX Display;

static void DoWindowColors(WINDOW);

#ifdef INCLUDE_WINDOWOPTIONS
static void SelectTexture(void);
static void SelectBorder(WINDOW);
static void SelectTitle(WINDOW);
static void SelectStatusBar(WINDOW);
#endif

WINDOW oldFocus;
#ifdef INCLUDE_MULTI_WINDOWS
int WindowSel;
#endif

static char Cwd[65];



/* --------------- CREATE_WINDOW Message -------------- */
static int CreateWindowMsg(WINDOW wnd)
{
    int rtn;
	ApplicationWindow = wnd;
    ScreenHeight = SCREENHEIGHT;
	getcwd(Cwd, 64);

		DoWindowColors (wnd);
	

    if (SCREENHEIGHT != SysConfig.VideoCurrentResolution.VRes)    {
        SetScreenHeight(SysConfig.VideoCurrentResolution.VRes);
        if (WindowHeight(wnd) == ScreenHeight ||
                SCREENHEIGHT-1 < GetBottom(wnd))    {
            WindowHeight(wnd) = SCREENHEIGHT;
            GetBottom(wnd) = GetTop(wnd)+WindowHeight(wnd)-1;
            wnd->RestoredRC = WindowRect(wnd);
        }
    }
#ifdef INCLUDE_WINDOWOPTIONS
    SelectBorder(wnd);
    SelectTitle(wnd);
    SelectStatusBar(wnd);
#endif

    rtn = BaseWndProc(APPLICATION, wnd, CREATE_WINDOW, 0, 0);
    if (wnd->extension != NULL)
        CreateMenu(wnd);
    CreateStatusBar(wnd);
    SendMessage(NULL, SHOW_MOUSE, 0, 0);
    return rtn;
}

/* --------- ADDSTATUS Message ---------- */
static void AddStatusMsg(WINDOW wnd, PARAM p1)
{
    if (wnd->StatusBar != NULL)    {
        if (p1 && *(char *)p1)
            SendMessage(wnd->StatusBar, SETTEXT, p1, 0);
        else 
            SendMessage(wnd->StatusBar, CLEARTEXT, 0, 0);
        SendMessage(wnd->StatusBar, PAINT, 0, 0);
    }
}

/* -------- SETFOCUS Message -------- */
static void SetFocusMsg(WINDOW wnd, BOOL p1)
{
    if (p1)
        SendMessage(inFocus, SETFOCUS, FALSE, 0);
    inFocus = p1 ? wnd : NULL;
	SendMessage(NULL, HIDE_CURSOR, 0, 0);
	if (isVisible(wnd))
	    SendMessage(wnd, BORDER, 0, 0);
	else 
	    SendMessage(wnd, SHOW_WINDOW, 0, 0);
}

/* ------- SIZE Message -------- */
static void SizeMsg(WINDOW wnd, PARAM p1, PARAM p2)
{
    BOOL WasVisible;
    WasVisible = isVisible(wnd);
    if (WasVisible)
        SendMessage(wnd, HIDE_WINDOW, 0, 0);
    if (p1-GetLeft(wnd) < 30)
        p1 = GetLeft(wnd) + 30;
    BaseWndProc(APPLICATION, wnd, SIZE, p1, p2);
    CreateMenu(wnd);
    CreateStatusBar(wnd);
    if (WasVisible)
        SendMessage(wnd, SHOW_WINDOW, 0, 0);
}

/* ----------- KEYBOARD Message ------------ */
static int KeyboardMsg(WINDOW wnd, PARAM p1, PARAM p2)
{
    if (WindowMoving || WindowSizing || (int) p1 == F1)
        return BaseWndProc(APPLICATION, wnd, KEYBOARD, p1, p2);
    switch ((int) p1)    {
        case ALT_F4:
			if (TestAttribute(wnd, CONTROLBOX))
	            PostMessage(wnd, CLOSE_WINDOW, 0, 0);
            return TRUE;
#ifdef INCLUDE_MULTI_WINDOWS
        case ALT_F6:	/* same effect as Alt-Tab in Win ;-) */
            SetNextFocus();
            return TRUE;
#endif
        case ALT_HYPHEN:
			if (TestAttribute(wnd, CONTROLBOX))
	            BuildSystemMenu(wnd);
            return TRUE;
        default:
            break;
    }
    PostMessage(wnd->MenuBarWnd, KEYBOARD, p1, p2);
    return TRUE;
}

/* --------- SHIFT_CHANGED Message -------- */
static void ShiftChangedMsg(WINDOW wnd, PARAM p1)
{
	extern BOOL AltDown;
    if ((int)p1 & ALTKEY)
        AltDown = TRUE;
    else if (AltDown)    {
        AltDown = FALSE;
        if (wnd->MenuBarWnd != inFocus)
            SendMessage(NULL, HIDE_CURSOR, 0, 0);
        SendMessage(wnd->MenuBarWnd, KEYBOARD, F10, 0);
    }
}

/* -------- COMMAND Message ------- */
static void CommandMsg(WINDOW wnd, PARAM p1, PARAM p2)
{
    switch ((int)p1)    {
        case ID_SYSCLOSE:
            PostMessage(wnd, CLOSE_WINDOW, 0, 0);
            break;
#ifdef INCLUDE_RESTORE
        case ID_SYSRESTORE:
#endif
        case ID_SYSMOVE:
        case ID_SYSSIZE:
#ifdef INCLUDE_MINIMIZE
        case ID_SYSMINIMIZE:
#endif
#ifdef INCLUDE_MAXIMIZE
        case ID_SYSMAXIMIZE:
#endif
            BaseWndProc(APPLICATION, wnd, COMMAND, p1, p2);
            break;
        default:
            if (inFocus != wnd->MenuBarWnd && inFocus != wnd)
                PostMessage(inFocus, COMMAND, p1, p2);
            break;
    }
}

/* --------- CLOSE_WINDOW Message -------- */
static int CloseWindowMsg(WINDOW wnd)
{
    int rtn;
#ifdef INCLUDE_MULTI_WINDOWS
    CloseAll(wnd, TRUE);
	WindowSel = 0;
#endif
    PostMessage(NULL, STOP, 0, 0);
    rtn = BaseWndProc(APPLICATION, wnd, CLOSE_WINDOW, 0, 0);
    if (ScreenHeight != SCREENHEIGHT)
        SetScreenHeight(ScreenHeight);
	ApplicationWindow = NULL;
	setdisk(toupper(*Cwd) - 'A');
	chdir(Cwd+2);
    return rtn;
}

/* --- APPLICATION Window Class window processing module --- */
int ApplicationProc(WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2)
{
    switch (msg)    {
        case CREATE_WINDOW:
            return CreateWindowMsg(wnd);
        case HIDE_WINDOW:
            if (wnd == inFocus)
                inFocus = NULL;
            break;
        case ADDSTATUS:
            AddStatusMsg(wnd, p1);
            return TRUE;
        case SETFOCUS:
            if ((int)p1 == (inFocus != wnd))    {
                SetFocusMsg(wnd, (BOOL) p1);
                return TRUE;
            }
            break;
        case SIZE:
            SizeMsg(wnd, p1, p2);
            return TRUE;
#ifdef INCLUDE_MINIMIZE
        case MINIMIZE:
            return TRUE;
#endif
        case KEYBOARD:
            return KeyboardMsg(wnd, p1, p2);
        case SHIFT_CHANGED:
            ShiftChangedMsg(wnd, p1);
            return TRUE;
        case PAINT:
            if (isVisible(wnd))    {
                int cl = APPLCHAR;
                ClearWindow(wnd, (RECT *)p1, cl);
            }
            return TRUE;
        case COMMAND:
            CommandMsg(wnd, p1, p2);
            return TRUE;
        case CLOSE_WINDOW:
            return CloseWindowMsg(wnd);
        default:
            break;
    }
    return BaseWndProc(APPLICATION, wnd, msg, p1, p2);
}

static void SwitchCursor(void)
{
    SendMessage(NULL, SAVE_CURSOR, 0, 0);
    SwapCursorStack();
    SendMessage(NULL, RESTORE_CURSOR, 0, 0);
}

/* ------- Shell out to DOS ---------- */
void ExecuteNonDFP (char *CmdLine)
{
	oldFocus = inFocus;
    SendMessage(ApplicationWindow, HIDE_WINDOW, 0, 0);
    SwitchCursor();
    if (ScreenHeight != SCREENHEIGHT)
        SetScreenHeight(ScreenHeight);
    SendMessage(NULL, HIDE_MOUSE, 0, 0);
    printf("Type EXIT to return to %s (%i.%i.%i.%i) (based on DFlat+ %i.%i).\n", 
           ProgramModule.Description,ProgramModule.Ver_maj,ProgramModule.Ver_min,ProgramModule.Ver_rel,ProgramModule.Ver_patch, 
           DFlatpModule.Ver_maj,DFlatpModule.Ver_min);
    fflush(stdout);
    spawnl(P_WAIT, CmdLine, NULL);
    if (SCREENHEIGHT != SysConfig.VideoCurrentResolution.VRes)
        SetScreenHeight(SysConfig.VideoCurrentResolution.VRes);
    SwitchCursor();
	SendMessage(ApplicationWindow, SHOW_WINDOW, 0, 0);
    SendMessage(oldFocus, SETFOCUS, TRUE, 0);
    SendMessage(NULL, SHOW_MOUSE, 0, 0);
}


/* -------- Create the menu bar -------- */
void CreateMenu(WINDOW wnd)
{
    AddAttribute(wnd, HASMENUBAR);
    if (wnd->MenuBarWnd != NULL)
        SendMessage(wnd->MenuBarWnd, CLOSE_WINDOW, 0, 0);
    wnd->MenuBarWnd = CreateWindow(MENUBAR,
                        NULL,
                        GetClientLeft(wnd),
                        GetClientTop(wnd)-1,
                        1,
                        ClientWidth(wnd),
                        NULL,
                        wnd,
                        NULL,
                        0);
    SendMessage(wnd->MenuBarWnd,BUILDMENU,
        (PARAM)wnd->extension,0);
    AddAttribute(wnd->MenuBarWnd, VISIBLE);
}

/* ----------- Create the status bar ------------- */
void CreateStatusBar(WINDOW wnd)
{
    if (wnd->StatusBar != NULL)    {
        SendMessage(wnd->StatusBar, CLOSE_WINDOW, 0, 0);
        wnd->StatusBar = NULL;
    }
    if (TestAttribute(wnd, HASSTATUSBAR))    {
        wnd->StatusBar = CreateWindow(STATUSBAR,
                            NULL,
                            GetClientLeft(wnd),
                            GetBottom(wnd),
                            1,
                            ClientWidth(wnd),
                            NULL,
                            wnd,
                            NULL,
                            0);
        AddAttribute(wnd->StatusBar, VISIBLE);
    }
}

#ifdef INCLUDE_MULTI_WINDOWS
/* -------- return the name of a document window ------- */
char *WindowName(WINDOW wnd)
{
    if (GetTitle(wnd) == NULL)    {
        if (GetClass(wnd) == DIALOG)
            return ((DBOX *)(wnd->extension))->HelpName;
        else 
            return "Untitled";
    }
    else
        return GetTitle(wnd);
}




/* ----- user chose a window from the Window menu
        OR the More Window dialog box ----- */
void ChooseWindow(WINDOW wnd, int WindowNo)
{
#if CLASSIC_WINDOW_NUMBERING
    WINDOW cwnd = FirstWindow(wnd);
#else
    WINDOW cwnd = NumberOneChildWindow(wnd);
#endif
    while (cwnd != NULL)	{
	/* printf("CHOOSEWINDOW...\n"); */
        if (isVisible(cwnd) &&
            GetClass(cwnd) != MENUBAR &&
            GetClass(cwnd) != STATUSBAR)
            if (WindowNo-- == 0)
                break;
#if CLASSIC_WINDOW_NUMBERING
	cwnd = NextWindow(cwnd);
#else
	cwnd = NextNumberedWindow(cwnd);
#endif
    }
    if (cwnd != NULL)    {
        SendMessage(cwnd, SETFOCUS, TRUE, 0);
        if (cwnd->condition == ISMINIMIZED)
            SendMessage(cwnd, RESTORE, 0, 0);
    }
}

/* ----- Close all document windows ----- */
void CloseAll(WINDOW wnd, int closing)
{
    WINDOW wnd1, wnd2;
    SendMessage(wnd, SETFOCUS, TRUE, 0);
	wnd1 = LastWindow(wnd);
	while (wnd1 != NULL)	{
		wnd2 = PrevWindow(wnd1);
        if (isVisible(wnd1) &&
				GetClass(wnd1) != MENUBAR &&
					GetClass(wnd1) != STATUSBAR)    {
	        ClearVisible(wnd1);
    	    SendMessage(wnd1, CLOSE_WINDOW, 0, 0);
		}
		wnd1 = wnd2;
    }
    if (!closing)
        SendMessage(wnd, PAINT, 0, 0);
}

#endif    /* #ifdef INCLUDE_MULTI_WINDOWS */

static void DoWindowColors(WINDOW wnd)
{
    WINDOW cwnd;
    InitWindowColors(wnd);
    cwnd = FirstWindow(wnd);
    while (cwnd != NULL) {
        DoWindowColors(cwnd);
        if (GetClass(cwnd) == TEXT && GetText(cwnd) != NULL)
            SendMessage(cwnd, CLEARTEXT, 0, 0);
        cwnd = NextWindow(cwnd);
    }
}

/* ---- select screen lines ---- */
void SelectLines(VideoResolution  reqVR)
{
	
	  SysConfig.VideoCurrentResolution = reqVR;

    if (SCREENHEIGHT != reqVR.VRes)    {

        SetScreenHeight(reqVR.VRes);

    		/* ---- re-maximize ---- */
        if (ApplicationWindow->condition == ISMAXIMIZED)	{
           SendMessage(ApplicationWindow, SIZE, (PARAM) GetRight(ApplicationWindow),
                    SCREENHEIGHT-1);
    		   return;
    		}
    		/* --- adjust if current size does not fit --- */
    		if (WindowHeight(ApplicationWindow) > SCREENHEIGHT)
                SendMessage(ApplicationWindow, SIZE, (PARAM) GetRight(ApplicationWindow),
                    (PARAM) GetTop(ApplicationWindow)+SCREENHEIGHT-1);
    		/* --- if window is off-screen, move it on-screen --- */
    		if (GetTop(ApplicationWindow) >= SCREENHEIGHT-1)
     			 SendMessage(ApplicationWindow, MOVE, (PARAM) GetLeft(ApplicationWindow),
    				  (PARAM) SCREENHEIGHT-WindowHeight(ApplicationWindow));
      }
}

/* ---- set the screen height in the video hardware ---- */
void SetScreenHeight(int height)
{
    if (isEGA() || isVGA())    {
        SendMessage(NULL, SAVE_CURSOR, 0, 0);
        switch (height)    {
            case 25:
                Set25();
                break;
            case 43:
                Set43();
                break;
            case 50:
                Set50();
                break;
            default:
                break;
        }
        SendMessage(NULL, RESTORE_CURSOR, 0, 0);
        SendMessage(NULL, RESET_MOUSE, 0, 0);
        SendMessage(NULL, SHOW_MOUSE, 0, 0);
    }
}


BOOL SelectColorScheme (ColorScheme cs)
{
	
    memcpy(&SysConfig.VideoCurrentColorScheme, &cs, sizeof (ColorScheme));

		if (ApplicationWindow != NULL)
   			DoWindowColors(ApplicationWindow);

    return TRUE;
}


#ifdef INCLUDE_WINDOWOPTIONS

/* ----- select the screen texture ----- */
static void SelectTexture(void)
{
    cfg.Texture = CheckBoxSetting(&Display, ID_TEXTURE);
}

/* -- select whether the application screen has a border -- */
static void SelectBorder(WINDOW wnd)
{
    cfg.Border = CheckBoxSetting(&Display, ID_BORDER);
    if (cfg.Border)
        AddAttribute(wnd, HASBORDER);
    else
        ClearAttribute(wnd, HASBORDER);
}

/* select whether the application screen has a status bar */
static void SelectStatusBar(WINDOW wnd)
{
    cfg.StatusBar = CheckBoxSetting(&Display, ID_STATUSBAR);
    if (cfg.StatusBar)
        AddAttribute(wnd, HASSTATUSBAR);
    else
        ClearAttribute(wnd, HASSTATUSBAR);
}

/* select whether the application screen has a title bar */
static void SelectTitle(WINDOW wnd)
{
    cfg.Title = CheckBoxSetting(&Display, ID_TITLE);
    if (cfg.Title)
        AddAttribute(wnd, HASTITLEBAR);
    else
        ClearAttribute(wnd, HASTITLEBAR);
}


#endif

