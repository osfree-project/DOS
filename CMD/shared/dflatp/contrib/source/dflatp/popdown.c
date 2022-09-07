/* ------------- popdown.c ----------- */

#include "dfpcomp.h"

static int SelectionWidth(struct PopDown *);
static int py = -1;
int CurrentMenuSelection;

static long int PopDownDelay = 0;
#define MaxPopDownDelay 8000        /* approx. half a second = 8000 */ 

extern int mctr;

/* ------------ CREATE_WINDOW Message ------------- */
static int CreateWindowMsg(WINDOW wnd)
{
    int rtn, adj;
    ClearAttribute(wnd, HASTITLEBAR     |
                        VSCROLLBAR     |
                        MOVEABLE     |
                        SIZEABLE     |
                        HSCROLLBAR);
	/* ------ adjust to keep popdown on screen ----- */
	adj = SCREENHEIGHT-1-wnd->rc.bt;
	if (adj < 0)	{
		wnd->rc.tp += adj;
		wnd->rc.bt += adj;
	}
	adj = SCREENWIDTH-1-wnd->rc.rt;
	if (adj < 0)	{
		wnd->rc.lf += adj;
		wnd->rc.rt += adj;
	}
    rtn = BaseWndProc(POPDOWNMENU, wnd, CREATE_WINDOW, 0, 0);
    SendMessage(wnd, CAPTURE_MOUSE, 0, 0);
    SendMessage(wnd, CAPTURE_KEYBOARD, 0, 0);
    SendMessage(wnd, CAPTURE_CLOCK, 0, 0);            
    SendMessage(NULL, SAVE_CURSOR, 0, 0);
    SendMessage(NULL, HIDE_CURSOR, 0, 0);

	wnd->oldFocus = inFocus;
	inFocus = wnd;
	
    return rtn;
}


/* -------- BUTTON_RELEASED Message -------- */
static BOOL ButtonReleasedMsg(WINDOW wnd, PARAM p1, PARAM p2)
{
    py = -1;
    if (InsideRect((int)p1, (int)p2, ClientRect(wnd)))    {
        int sel = (int)p2 - GetClientTop(wnd);
        if (*TextLine(wnd, sel) != LINE)     {
						if (FocusedWindow(wnd) != NULL) 
								SendMessage (FocusedWindow(wnd), CLOSE_WINDOW, 0, 0);
            SendMessage(wnd, LB_SELECTION, sel, 0);
            SendMessage(wnd, LB_CHOOSE, wnd->selection, 0);
        }
    } else	{
    		WINDOW pwnd = GetParent (wnd);
				PostMessage (pwnd, BUTTON_RELEASED, p1, p2);
				if ( (GetClass(pwnd) !=MENUBAR) && (GetClass(pwnd)!=POPDOWNMENU) )
                 SendMessage(wnd, CLOSE_POPDOWN, TRUE, 0);
		}				
    return FALSE;
}

/* --------- PAINT Message -------- */
static void PaintMsg(WINDOW wnd)
{
    int wd;
    unsigned char sep[80],*cp=sep,sel[80];
    struct PopDown *ActivePopDown,*pd1;

    ActivePopDown = pd1 = wnd->mnu->Selections;
    wd = MenuWidth(ActivePopDown)-2;
    while (wd--)
        *cp++ = LINE;

    *cp = '\0';
    SendMessage(wnd, CLEARTEXT, 0, 0);
    wnd->selection = wnd->mnu->Selection;
    while (pd1->SelectionTitle != NULL)
        {
        if (*pd1->SelectionTitle == LINE)
            SendMessage(wnd, ADDTEXT, (PARAM) sep, 0);
        else
            {
            int len;

            memset(sel, '\0', sizeof sel);
            if (pd1->Attrib & INACTIVE)
                /* ------ inactive menu selection ----- */
                sprintf(sel, "%c%c%c", CHANGECOLOR, wnd->WindowColors [HILITE_COLOR] [FG]|0x80, wnd->WindowColors [STD_COLOR] [BG]|0x80);

            strcat(sel, " ");
            if (pd1->Attrib & CHECKED)
                /* ---- paint the toggle checkmark ---- */
                sel[strlen(sel)-1] = CHECKMARK;

            len=CopyCommand(sel+strlen(sel), pd1->SelectionTitle, pd1->Attrib & INACTIVE, wnd->WindowColors [STD_COLOR] [BG]);
            if (pd1->Accelerator)
                {
                /* ---- paint accelerator key ---- */
                int i;
                int wd1=2+SelectionWidth(ActivePopDown)-strlen(pd1->SelectionTitle);
                int key=pd1->Accelerator;

                if (key > 0 && key < 27)
                    {
                    /* --- CTRL+ key --- */
                    while (wd1--)
                        strcat(sel, " ");

                    sprintf(sel+strlen(sel), "Ctrl+%c", key-1+'A');
                    }
                else	/* accelerator keys with names defined in keys.c */
                    {
                    for (i = 0; keys[i].keylabel; i++)
                        {
                    	if (keys[i].keycode == key)
                            {
                            while (wd1--)
                                strcat(sel, " ");

                            sprintf(sel+strlen(sel), "%s",
                            keys[i].keylabel);
                            break;
                            }

                        }

                    }

                }

            if (pd1->Attrib & CASCADED)
                {
                /* ---- paint cascaded menu token ---- */
                if (!pd1->Accelerator)
                    {
                    wd = MenuWidth(ActivePopDown)-len+1;
                    while (wd--)
                        strcat(sel, " ");

                    }

                sel[strlen(sel)-1] = CASCADEPOINTER;
                }
            else
                strcat(sel, " ");

            strcat(sel, " ");
            sel[strlen(sel)-1] = RESETCOLOR;
            SendMessage(wnd, ADDTEXT, (PARAM) sel, 0);
            }

        pd1++;
        }

}

/* ---------- BORDER Message ----------- */
static int BorderMsg(WINDOW wnd)
{
    int i, rtn = TRUE;
    WINDOW currFocus;
    if (wnd->mnu != NULL)    {
        currFocus = inFocus;
        inFocus = NULL;
        rtn = BaseWndProc(POPDOWNMENU, wnd, BORDER, 0, 0);
        inFocus = currFocus;
        for (i = 0; i < ClientHeight(wnd); i++)    {
            if (*TextLine(wnd, i) == LINE)    {
                wputch(wnd, LEDGE, 0, i+1);
                wputch(wnd, REDGE, WindowWidth(wnd)-1, i+1);
            }
        }
    }
    return rtn;
}

/* -------------- LB_CHOOSE Message -------------- */
/* did the user left-click one of the items in the current popdown? */
static void LBChooseMsg(WINDOW wnd, PARAM p1)
{
    struct PopDown *ActivePopDown = wnd->mnu->Selections;

    if (ActivePopDown != NULL)    {
        int *attr = &(ActivePopDown+(int)p1)->Attrib;

        wnd->mnu->Selection = (int)p1;
        if (!(*attr & INACTIVE))    {
            if (*attr & TOGGLE)
                *attr ^= CHECKED;
			      if (GetParent (wnd) != NULL)	{
				        CurrentMenuSelection = (int)p1;

  							if (isCascadedCommand2(wnd->mnu, (ActivePopDown+(int)p1)->ActionId))  {
						        /* find the cascaded menu based on command id in p1 */
        						MENU *mnu = ActiveMenuBar->PullDown + mctr;

						        while (mnu->Title != (void *)-1)    {
            						if (mnu->CascadeId == (int) (ActivePopDown+(int)p1)->ActionId )    {
  							
               						    /* Create a new pop-up child window */
                  						WINDOW mwnd;
                  						
                              if (mnu->PrepMenu != NULL)
                                  (*(mnu->PrepMenu))(GetDocFocus(), mnu);
              
                              mwnd = CreateWindow(POPDOWNMENU, NULL,
                                          GetLeft(wnd) + WindowWidth(wnd) - 1, 
                                          GetTop(wnd) + wnd->selection,
                                          MenuHeight(mnu->Selections),
                                          MenuWidth(mnu->Selections),
                                          NULL,
                                          wnd,
                                          NULL,
                                          SHADOW);
              
                              wnd->childfocus = mwnd;		/* Register it as current menu's child */
              
                              SendMessage(mwnd, BUILD_SELECTIONS, (PARAM) mnu, 0);
                      			  SendMessage(mwnd, SETFOCUS, TRUE, 0);
                      				SendMessage(mwnd, SHOW_WINDOW, 0, 0);
                          
                              break;
                        }
                        mnu++;
        						}
  							} else
      						PostMessage(wnd, COMMAND,(ActivePopDown+(int)p1)->ActionId, 0);

			      }
        } else
						  PostMessage(wnd, CLOSE_POPDOWN, TRUE, 0);
     }
}

/* ---------- KEYBOARD Message --------- */
/* did the user hit the highlighted key for an item in the current popdown? */
static BOOL KeyboardMsg(WINDOW wnd, PARAM p1, PARAM p2)
{

		
    WINDOW pwnd = GetParent(wnd);
    struct PopDown *ActivePopDown = wnd->mnu->Selections;

    if (wnd->mnu != NULL)    {
        if (ActivePopDown != NULL)    {
            int c = (int)p1;
            int sel = 0;
            int a;
            struct PopDown *pd = ActivePopDown;

#ifdef HOOKKEYB
            if ((c & OFFSET) == 0)
#else
            if ((c & FKEY) == 0)
#endif
            c = tolower(c);
            a = AltConvert(c);

            while (pd->SelectionTitle != NULL)    {
                char *cp = strchr(pd->SelectionTitle,
                                SHORTCUTCHAR);
                int sc = tolower(*(cp+1));
                if ((cp && sc == c) ||
                    (a && sc == a) ||
                    (pd->Accelerator == c))
                {
                    PostMessage(wnd, LB_SELECTION, sel, 0);
                    PostMessage(wnd, LB_CHOOSE, sel, TRUE);
                    return TRUE;
                }
                pd++, sel++;
            }
        }
    }


    switch ((int)p1)    {
        case F1: /* (possibly context sensitive) help */
            if (ActivePopDown == NULL)
                SendMessage(pwnd, KEYBOARD, p1, p2);
            else 
                SystemHelp(wnd,
                    (ActivePopDown+wnd->selection)->help);
            return TRUE;
        case ESC:
            PostMessage(wnd, CLOSE_POPDOWN, FALSE, 0);
            return TRUE;
#ifdef HOOKKEYB
        case FWD: /* old name of right arrow */
#else
	case LARROW: /* hope this makes sense */
						if (GetClass(pwnd)==MENUBAR)
								PostMessage (pwnd, KEYBOARD, p1, p2);
						else  if (GetClass (pwnd) == POPDOWNMENU )
            	  		PostMessage (wnd, CLOSE_WINDOW, 0, 0);
            break;
	case RARROW: /* formerly called FWD */
      if ( (FocusedWindow(wnd) == NULL) && (wnd->mnu != NULL) && (ActivePopDown != NULL) &&
      		 isCascadedCommand2(wnd->mnu, (ActivePopDown+wnd->selection)->ActionId))
      		    PostMessage(wnd,LB_CHOOSE,wnd->selection, 0);
			else  if (GetClass(pwnd)==MENUBAR)
         	 		PostMessage(pwnd, KEYBOARD, p1, p2);
      break;
#endif
        case UP:
            if (wnd->selection == 0)    {
                if (wnd->wlines == ClientHeight(wnd))    {
                    PostMessage(wnd, LB_SELECTION,
                                    wnd->wlines-1, FALSE);
                    return TRUE;
                }
            }
            break;
        case DN:
            if (wnd->selection == wnd->wlines-1)    {
                if (wnd->wlines == ClientHeight(wnd))    {
                    PostMessage(wnd, LB_SELECTION, 0, FALSE);
                    return TRUE;
                }
            }
            break;
        case HOME:
        case END:
        case '\r':
            break;
        default:
            return TRUE;
    }
    return FALSE;
}

/* ----------- CLOSE_WINDOW Message ---------- */
static int CloseWindowMsg(WINDOW wnd)
{
		if (FocusedWindow(wnd) != NULL) SendMessage (FocusedWindow(wnd), CLOSE_WINDOW, 0, 0);
        SendMessage (GetParent(wnd), DEADCHILD, 0, 0);

    SendMessage(wnd, RELEASE_CLOCK, 0, 0);
    SendMessage(wnd, RELEASE_MOUSE, 0, 0);
    SendMessage(wnd, RELEASE_KEYBOARD, 0, 0);
    SendMessage(NULL, RESTORE_CURSOR, 0, 0);
	
		inFocus = wnd->oldFocus;

    return  BaseWndProc(POPDOWNMENU, wnd, CLOSE_WINDOW, 0, 0);
}

/* - Window processing module for POPDOWNMENU window class - */
int PopDownProc(WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2)
{
    int     rtn;
    WINDOW	pwnd = GetParent (wnd);


    if (msg != CLOCKTICK)
        PopDownDelay = 0;

    switch (msg)    {
        case CREATE_WINDOW:
            rtn = CreateWindowMsg(wnd);
            return rtn;

        case CLOCKTICK:
            PopDownDelay++;
            if (PopDownDelay >= MaxPopDownDelay ) {
            		PopDownDelay = 0;
							  if ((wnd->mnu != NULL) && (wnd->mnu->Selections != NULL))
           		       if (isCascadedCommand2(wnd->mnu, (wnd->mnu->Selections+wnd->selection)->ActionId))
            				    SendMessage(wnd, LB_CHOOSE, wnd->selection, 0);
    				}  
    				break;  
					/* With SmoothMenus, no longer need to do anything special with LEFT_BUTTON */
/*        case LEFT_BUTTON:
            LeftButtonMsg(wnd, p1, p2);
            return FALSE;
*/
        case DOUBLE_CLICK:
            return TRUE;
        case LB_SELECTION:
            if (*TextLine(wnd, (int)p1) == LINE)
                return TRUE;
            wnd->mnu->Selection = (int)p1;
            break;
        case BUTTON_RELEASED:
            if (ButtonReleasedMsg(wnd, p1, p2))
                return TRUE;
            break;
				case MOUSE_MOVED:
				    if (InsideRect((int)p1, (int)p2, ClientRect(wnd)))  {
								if ((p2 - WindowRect(wnd).tp -1) != wnd->selection) {
									 if (FocusedWindow(wnd) != NULL)  
											SendMessage (FocusedWindow(wnd), CLOSE_WINDOW, 0, 0);
  						     PostMessage(wnd, LB_SELECTION, p2 - WindowRect(wnd).tp -1, FALSE);
  						  }
						}
  					else
            		PostMessage(pwnd, MOUSE_MOVED, p1, p2);
						break;
        case BUILD_SELECTIONS:
            wnd->mnu = (void *) p1;
            wnd->selection = wnd->mnu->Selection;
            break;
        case PAINT:
            if (wnd->mnu == NULL)
                return TRUE;
            PaintMsg(wnd);
            break;
        case BORDER:
            return BorderMsg(wnd);
        case LB_CHOOSE:
            LBChooseMsg(wnd, p1);
            return TRUE;
        case DEADCHILD:
              (wnd->childfocus) = NULL;
              break;
        case SETFOCUS:
        			if (FocusedWindow(wnd) != NULL)
        					return SendMessage (FocusedWindow(wnd), SETFOCUS, 0, 0);
        			wnd->oldFocus = inFocus;
        			inFocus = wnd;
        			break;
        case KEYBOARD:
            if (KeyboardMsg(wnd, p1, p2))
                return TRUE;
            break;
        case CLOSE_WINDOW:
            rtn = CloseWindowMsg(wnd);
            return rtn;
            
				case CLOSE_POPDOWN:
						if ( (GetClass(pwnd)==MENUBAR) || (GetClass(pwnd)==POPDOWNMENU) )
                 PostMessage(pwnd, msg, p1, p2);
            else
            		 PostMessage (wnd, CLOSE_WINDOW, 0, 0);
            return TRUE;
        case COMMAND:
                 PostMessage(pwnd, msg, p1, p2);
                 return TRUE;
        default:
            break;
    }

    return BaseWndProc(POPDOWNMENU, wnd, msg, p1, p2);
}

/* --------- compute menu height -------- */
int MenuHeight(struct PopDown *pd)
{
    int ht = 0;
    while (pd[ht].SelectionTitle != NULL)
        ht++;
    return ht+2;
}

/* --------- compute menu width -------- */
int MenuWidth(struct PopDown *pd)
{
    int wd = 0, i;
    int len = 0;

    wd = SelectionWidth(pd);
    while (pd->SelectionTitle != NULL)    {
        if (pd->Accelerator)    {
            for (i = 0; keys[i].keylabel; i++)
                if (keys[i].keycode == pd->Accelerator)    {
                    len = max(len, 2+strlen(keys[i].keylabel));
                    break;
                }
        }
        if (pd->Attrib & CASCADED)
            len = max(len, 2);
        pd++;
    }
    return wd+5+len;
}

/* ---- compute the maximum selection width in a menu ---- */
static int SelectionWidth(struct PopDown *pd)
{
    int wd = 0;
    while (pd->SelectionTitle != NULL)    {
        int len = strlen(pd->SelectionTitle)-1;
        wd = max(wd, len);
        pd++;
    }
    return wd;
}

/* ----- copy a menu command to a display buffer ---- */
int CopyCommand(unsigned char *dest, unsigned char *src,
                                        int skipcolor, int bg)
{
    unsigned char *d = dest;
    while (*src && *src != '\n')    {
        if (*src == SHORTCUTCHAR)    {
            src++;
            if (!skipcolor)    {
                *dest++ = CHANGECOLOR;
                *dest++ = SysConfig.VideoCurrentColorScheme.clrArray[POPDOWNMENU]
                            [HILITE_COLOR] [BG] | 0x80;
                *dest++ = bg | 0x80;
                *dest++ = *src++;
                *dest++ = RESETCOLOR;
            }
        }
        else
            *dest++ = *src++;
    }
    return (int) (dest - d);
}

