/* ------------ log .c ------------ */

#include "dflatp.h"
#include "dfptools.h"
#include "helpbox.h"

enum dfplog_messages {
    /* ------------- Legacy Log dialog box ------------- */
    ID_LOGLIST = 5010,
  	ID_LOGGING};

static char *message[] = {
    #undef DFlatMsg
    #define DFlatMsg(m) " " #m,
    #include "dflatmsg.h"
    NULL
};

static FILE *log = NULL;

/* ------------ Message Log dialog box -------------- */
DIALOGBOX(dbLog)
    DB_TITLE("Edit Message Log", -1, -1, 18, 41)
    CONTROL(TEXT,  "~Messages",   10,   1,  1,  8, ID_LOGLIST)
    CONTROL(LISTBOX,    NULL,     1,    2, 14, 26, ID_LOGLIST)
    CONTROL(TEXT,    "~Logging:", 29,   4,  1, 10, ID_LOGGING)
    CONTROL(CHECKBOX,    NULL,    31,   5,  1,  3, ID_LOGGING)
    CONTROL(BUTTON,  "   ~OK   ", 29,   7,  1,  8, ID_OK)
    CONTROL(BUTTON,  " ~Cancel ", 29,  10,  1,  8, ID_CANCEL)
    CONTROL(BUTTON,  "  ~Help  ", 29,  13, 1,   8, ID_HELP)
ENDDB

BOOL LogMessageStart (WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2)
{
    if (log != NULL && message[msg][0] != ' ')
        fprintf(log,
            "%-20.20s %-12.12s %-20.20s, %5.5ld, %5.5ld\n",
            wnd ? (GetTitle(wnd) ? GetTitle(wnd) : "") : "",
            wnd ? ClassNames[GetClass(wnd)] : "",
            message[msg]+1, p1, p2);
    return TRUE;
}


BOOL LogMessageEnd ( WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2 )
{
	return TRUE;
}

static int LogProc(WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2)
{
    WINDOW cwnd = ControlWindow(&dbLog, ID_LOGLIST);
    char **mn = message;
    switch (msg)    {
        case INITIATE_DIALOG:
            AddAttribute(cwnd, MULTILINE | VSCROLLBAR);
            while (*mn)    {
                SendMessage(cwnd, ADDTEXT, (PARAM) (*mn), 0);
                mn++;
            }
            SendMessage(cwnd, SHOW_WINDOW, 0, 0);
            break;
        case COMMAND:
            if ((int) p1 == ID_OK)    {
                int item;
                int tl = GetTextLines(cwnd);
                for (item = 0; item < tl; item++)
                    if (ItemSelected(cwnd, item))
                        mn[item][0] = LISTSELECTOR;
            }
            break;
        default:
            break;
    }
    return DefaultWndProc(wnd, msg, p1, p2);
}

void MessageLog(WINDOW wnd)
{
    if (DialogBox(wnd, &dbLog, TRUE, LogProc))    {
        if (CheckBoxSetting(&dbLog, ID_LOGGING))    {
            log = fopen("DFLAT.LOG", "wt");
//            SetCommandToggle(&MainMenu, ID_LOG);
        }
        else if (log != NULL)    {
            fclose(log);
            log = NULL;
//            ClearCommandToggle(&MainMenu, ID_LOG);
        }
    }
}

//#endif

