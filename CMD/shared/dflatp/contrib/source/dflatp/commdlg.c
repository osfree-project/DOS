/*  Common Dialogs

    Part of FreeDOS DFlat+

*/

/* I N C L U D E S /////////////////////////////////////////////////////// */

#include "dfpcomp.h"

/* G L O B A L S ///////////////////////////////////////////////////////// */

void *mypointer;
static char FileSpec[15], SrchSpec[15], FileName[15];
extern DBOX FileOpen, SaveAs;
extern DBOX Display;
#ifdef INCLUDE_MULTI_WINDOWS
extern DBOX Windows;
#endif
//static WINDOW oldFocus;
extern int WindowSel;

char  VerStr [64];



/* P R O T O T Y P E S /////////////////////////////////////////////////// */

static BOOL DlgFileOpen(char *, char *, char *, DBOX *);
static int DlgFnOpen(WINDOW, MESSAGE, PARAM, PARAM);
static void InitFnOpenDlgBox(WINDOW);
#ifdef STRIPPATH
static void StripPath(char *);
#endif
static BOOL IncompleteFilename(char *);
BOOL BuildFileList(WINDOW, char *);
void BuildDirectoryList(WINDOW);
void BuildDriveList(WINDOW);
void BuildPathDisplay(WINDOW);
void SelectColors( void );

/* F U N C T I O N S ///////////////////////////////////////////////////// */

BOOL OpenFileDialogBox(char *Fspec, char *Fname)
{
    return DlgFileOpen(Fspec, Fspec, Fname, &FileOpen);
}

/* Save as Dialog Box */
BOOL SaveAsDialogBox(char *Fspec, char *Sspec, char *Fname)
{
    return DlgFileOpen(Fspec, Sspec ? Sspec : Fspec, Fname, &SaveAs);
}

/* Generic File Open */
static BOOL DlgFileOpen(char *Fspec, char *Sspec, char *Fname, DBOX *db)
{
    BOOL rtn;

    strncpy(FileSpec, Fspec, 15);
    strncpy(SrchSpec, Sspec, 15);
    if ((rtn = DialogBox(NULL, db, TRUE, DlgFnOpen)) != FALSE)
        strcpy(Fname, FileName);

    return rtn;

}

/* Process dialog box messages */
static int DlgFnOpen(WINDOW wnd,MESSAGE msg,PARAM p1,PARAM p2)
{
    switch (msg)
        {
        case CREATE_WINDOW:
            {
            int rtn = DefaultWndProc(wnd, msg, p1, p2);
            DBOX *db = wnd->extension;
            WINDOW cwnd = ControlWindow(db, ID_FILENAME);
            SendMessage(cwnd, SETTEXTLENGTH, 64, 0);
            return rtn;
            }
        case INITIATE_DIALOG:
            InitFnOpenDlgBox(wnd);
            break;
        case COMMAND:
            switch ((int) p1)
                {
                case ID_OK:
                    {
                    if ((int)p2 == 0)
                        {
                        char fn[MAXPATH+1], nm[MAXFILE], ext[MAXEXT];

                    	GetItemText(wnd, ID_FILENAME, fn, MAXPATH);
                        fnsplit(fn, NULL, NULL, nm, ext);
                        strcpy(FileName, nm);
                        strcat(FileName, ext);
                        CreatePath(NULL, fn, FALSE, TRUE);
                    	if (IncompleteFilename(FileName))
                            {
                            /* --- no file name yet --- */
                            DBOX *db = wnd->extension;
                            WINDOW cwnd = ControlWindow(db, ID_FILENAME);

                            strcpy(FileSpec, FileName);
                            strcpy(SrchSpec, FileName);
                            InitFnOpenDlgBox(wnd);
                            SendMessage(cwnd, SETFOCUS, TRUE, 0);
                            return TRUE;
                            }

                        }

                    break;
                    }
                case ID_FILES:
                    switch ((int) p2)
                        {
                        case ENTERFOCUS:
                        case LB_CHILDSELECTION:
                            /* Selected a different filename */
                            GetDlgListText(wnd, FileName, ID_FILES);
                            PutItemText(wnd, ID_FILENAME, FileName);
                            break;
                        case LB_CHOOSE:
                            /* Choose a file name */
                            GetDlgListText(wnd, FileName, ID_FILES);
                            SendMessage(wnd, COMMAND, ID_OK, 0);
                            break;
                        default:
                            break;

                        }
                    return TRUE;
                case ID_DIRECTORY:
                    switch ((int) p2)
                        {
                        case ENTERFOCUS:
                            PutItemText(wnd, ID_FILENAME, FileSpec);
                            break;
                    	case LB_CHOOSE:
                            {
                            /* Choose dir */
                            char dd[15];

                            GetDlgListText(wnd, dd, ID_DIRECTORY);
                            chdir(dd);
                            InitFnOpenDlgBox(wnd);
                            SendMessage(wnd, COMMAND, ID_OK, 0);
                            break;
	                    }

                        default:
                            break;

                        }
                    return TRUE;

                case ID_DRIVE:
                    switch ((int) p2)
                        {
                        case ENTERFOCUS:
                            PutItemText(wnd, ID_FILENAME, FileSpec);
                            break;
                    	case LB_CHOOSE:
                            {
                            /* Choose dir */
                            char dr[15];
                            GetDlgListText(wnd, dr, ID_DRIVE);
                            /* *** 0.6e: string has form "[-X-]" *** */
                            setdisk(dr[2] - 'A'); /* fixed 0.6e: must use [2] */
                            InitFnOpenDlgBox(wnd);
                            SendMessage(wnd, COMMAND, ID_OK, 0);
	                    }
                        default:
                            break;

                        }
                    return TRUE;

                default:
                    break;
                }
        default:
            break;

        }

    return DefaultWndProc(wnd, msg, p1, p2);

}

/* Initialize the dialog box */
static void InitFnOpenDlgBox(WINDOW wnd)
{
    if (*FileSpec)
        PutItemText(wnd, ID_FILENAME, FileSpec);

    BuildPathDisplay(wnd);
    if (BuildFileList(wnd, SrchSpec))
        BuildDirectoryList(wnd);

    BuildDriveList(wnd);
}

/* Strip the drive and path information from a file spec */
#ifdef STRIPPATH /* normally not used... */
static void StripPath(char *filespec)
{
    char *cp, *cp1;

    cp = strchr(filespec, ':');
    if (cp != NULL)
        cp++;
    else
        cp = filespec;

    while (TRUE)
        {
        cp1 = strchr(cp, '\\');
        if (cp1 == NULL)
            break;

        cp = cp1+1;
        }

    strcpy(filespec, cp);

}
#endif

static BOOL IncompleteFilename(char *s)
{
    int lc = strlen(s)-1;

    if (strchr(s, '?') || strchr(s, '*') || !*s)
        return TRUE;

    if (*(s+lc) == ':' || *(s+lc) == '\\')
        return TRUE;

    return FALSE;
}


void AboutBox ( MODULE m, BOOL BasedOnDFlat )
{
		char maxAbout[]=
						 "                                      ";
    char aboutMsg [] =
             "          @                        \n"
             "          Version @                \n"
             "          @                        \n"
             "@                                  \n"
             "                                   \n"
             "@                                  \n"
             "@                                  \n"
             "@                                   ";

			char AboutStr[255];
			char *About1, *About2;
			
			strncpy (AboutStr, m.AboutComment, 255);
			About1 = strtok (AboutStr, "|");
			About2 = strtok (NULL, "@");

      strncpy (maxAbout, m.Description, 22); maxAbout[23] = 0;
      strncpy(strchr(aboutMsg,'@'), maxAbout,  strlen(maxAbout));
      
      strncpy (maxAbout, ModuleVersion(m), 14); maxAbout[15] = 0;
      strncpy(strchr(aboutMsg,'@'), maxAbout,  strlen(maxAbout));
      
      strncpy (maxAbout, m.License, 22); maxAbout[23] = 0;
      strncpy(strchr(aboutMsg,'@'), maxAbout,  strlen(maxAbout));
      
      strncpy (maxAbout, m.Copyright, 34); maxAbout[35] = 0;
      strncpy(strchr(aboutMsg,'@'), maxAbout,  strlen(maxAbout));
      
      strncpy (maxAbout, About1, 34); maxAbout[35] = 0;
      strncpy(strchr(aboutMsg,'@'), maxAbout,  strlen(maxAbout));
      
      strncpy (maxAbout, About2, 34); maxAbout[35] = 0;
      strncpy(strchr(aboutMsg,'@'), maxAbout,  strlen(maxAbout));
      
//      strncpy (maxAbout, SysConfig.DFlatpVersion, 4); maxAbout[5] = 0;
//      strncpy(strchr(aboutMsg,'@'), maxAbout,  strlen(maxAbout));

			if (BasedOnDFlat)
				 sprintf (AboutStr, "Based on FreeDOS-DFlat+ %i.%i",DFlatpModule.Ver_maj,DFlatpModule.Ver_min);
			else
				 strcpy (AboutStr, " ");
				 
      strncpy (maxAbout, AboutStr, 33); maxAbout[34] = 0;
      strncpy(strchr(aboutMsg,'@'), maxAbout,  strlen(maxAbout));

			sprintf (AboutStr, "About %s", m.Description);

      MessageBox(AboutStr, aboutMsg);
}

void ProgramAboutBox ( void )
{
		AboutBox ( ProgramModule, TRUE );
}

void DFlatpAboutBox ( void )
{
		AboutBox ( DFlatpModule, FALSE );
}


void CustomizeDisplayPropBox ( void )
{
       	int i;
       	CTLWINDOW *ct, *ct1;
       	ct = FindCommand(&Display, ID_SNOWY, CHECKBOX);
    	if (!isVGA())    {
        	/* ---- modify Display Dialog Box for EGA, CGA ---- */
        	if (isEGA())
            	ct1 = FindCommand(&Display,ID_50LINES,RADIOBUTTON);
        	else    {
            	CTLWINDOW *ct2;
            	ct2 = FindCommand(&Display,ID_COLOR,RADIOBUTTON)-1;
				if (ct2)	{
	            	ct2->dwnd.w++;
    	        	for (i = 0; i < 7; i++)
        	        	(ct2+i)->dwnd.x += 8;
				}
            	ct1 = FindCommand(&Display,ID_25LINES,RADIOBUTTON)-1;
        	}
			if (ct && ct1)
	        	for (i = 0; i < 6; i++)
    	        	*ct1++ = *ct++;
		}
    	if (isVGA() || isEGA())    {
			/* ------ eliminate the snowy check box ----- */
	       	ct = FindCommand(&Display, ID_SNOWY, CHECKBOX);
			if (ct != NULL)
				for (i = 0; i < 4; i++)
					*(ct+i) = *(ct+2+i);
		}
}


/* Display Properties Box */
void DisplayProperties ( WINDOW wnd )
{
	
	VideoResolution newVideoResolution;
	
	#ifdef INCLUDE_WINDOWOPTIONS
    if (cfg.Border)
        SetCheckBox(&Display, ID_BORDER);
    if (cfg.Title)
        SetCheckBox(&Display, ID_TITLE);
    if (cfg.StatusBar)
        SetCheckBox(&Display, ID_STATUSBAR);
    if (cfg.Texture)
        SetCheckBox(&Display, ID_TEXTURE);
#endif

		/* Prepare the dialog box items */

	  switch (SysConfig.VideoCurrentColorScheme.index)   {
	  	case 1: PushRadioButton(&Display, ID_MONO); break;
	  	case 2: PushRadioButton(&Display, ID_REVERSE); break;
	  	default: PushRadioButton(&Display, ID_COLOR);
	  }

    switch (SCREENHEIGHT)  {
    		case 43: PushRadioButton(&Display, ID_43LINES); break;
    		case 50: PushRadioButton(&Display, ID_50LINES); break;
    		default: PushRadioButton(&Display, ID_25LINES);
    }
    
		if ( GetSnowyFlag() )
        SetCheckBox(&Display, ID_SNOWY);

		/* Execute the dialog box */

    if (DialogBox(wnd, &Display, TRUE, NULL))     {

				if (inFocus == wnd->MenuBarWnd || inFocus == wnd->StatusBar)
					oldFocus = ApplicationWindow;
				else 
					oldFocus = inFocus;

        SendMessage(wnd, HIDE_WINDOW, 0, 0);

				newVideoResolution = TXT25;
        if (isEGA() || isVGA())    {
             if (RadioButtonSetting(&Display, ID_43LINES))
                 newVideoResolution = TXT43;
             else if (RadioButtonSetting(&Display, ID_50LINES))
                 newVideoResolution = TXT50;
        }

        SelectLines(newVideoResolution);
        SelectColors();

#ifdef INCLUDE_WINDOWOPTIONS
                SelectBorder(wnd);
                SelectTitle(wnd);
                SelectStatusBar(wnd);
                SelectTexture();
#endif

        CreateMenu(wnd);
        CreateStatusBar(wnd);
        SendMessage(wnd, SHOW_WINDOW, 0, 0);
		    SendMessage(oldFocus, SETFOCUS, TRUE, 0);
    }
}

/* ----- set up colors for the application window ------ */
void SelectColors( void )
{
  	get_videomode();
    if (ismono() && !isEGA() && !isVGA())     /* -------- CGA --------- */
       SetSnowyFlag (CheckBoxSetting(&Display, ID_SNOWY));

    if (RadioButtonSetting(&Display, ID_MONO))
        SelectColorScheme (bw);
    else if (RadioButtonSetting(&Display, ID_REVERSE))
        SelectColorScheme (reverse);
    else if (ismono() || video_mode == 2)
        SelectColorScheme (bw);
		else
        SelectColorScheme (color);

}



/* window processing module for the More Windows dialog box */
/* used if you have more than 9 windows open, lists ALL windows */
static int WindowPrep(WINDOW wnd,MESSAGE msg,PARAM p1,PARAM p2)
{
    switch (msg)    {
        case INITIATE_DIALOG:    {
            WINDOW wnd1;
            WINDOW cwnd = ControlWindow(&Windows,ID_WINDOWLIST);
            int sel = 0;
            if ((cwnd == NULL) || (ApplicationWindow == NULL))
                return FALSE;
#if CLASSIC_WINDOW_NUMBERING
            wnd1 = FirstWindow(ApplicationWindow);
#else
            wnd1 = NumberOneChildWindow(ApplicationWindow);
#endif
            while (wnd1 != NULL)	{
		/* printf("WINDOWPREP...\n"); */
                if (isVisible(wnd1) && wnd1 != wnd &&
                    GetClass(wnd1) != MENUBAR &&
                    GetClass(wnd1) != STATUSBAR)    {
                    if (wnd1 == oldFocus)
                        WindowSel = sel;
                    SendMessage(cwnd, ADDTEXT,
                        (PARAM) WindowName(wnd1), 0);
                    sel++;
                }
#if CLASSIC_WINDOW_NUMBERING
                wnd1 = NextWindow(wnd1);
#else
                wnd1 = NextNumberedWindow(wnd1);
#endif
            }
            SendMessage(cwnd, LB_SETSELECTION, WindowSel, 0);
            AddAttribute(cwnd, VSCROLLBAR);
            PostMessage(cwnd, SHOW_WINDOW, 0, 0);
            break;
        }
        case COMMAND:
            switch ((int) p1)    {
                case ID_OK:
                    if ((int)p2 == 0)
                        WindowSel = SendMessage(
                                    ControlWindow(&Windows,
                                    ID_WINDOWLIST),
                                    LB_CURRENTSELECTION, 0, 0);
                    break;
                case ID_WINDOWLIST:
                    if ((int) p2 == LB_CHOOSE)
                        SendMessage(wnd, COMMAND, ID_OK, 0);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return DefaultWndProc(wnd, msg, p1, p2);
}

/* ---- the More Windows command on the Window menu ---- */
void MoreWindows(WINDOW wnd)
{
    if (DialogBox(wnd, &Windows, TRUE, WindowPrep))
        ChooseWindow(wnd, WindowSel);
}

