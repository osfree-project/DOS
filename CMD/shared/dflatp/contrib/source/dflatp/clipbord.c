/* ----------- clipbord.c ------------ */

#include "dfpcomp.h"

char *Clipboard;
unsigned ClipboardLength;

void CopyTextToClipboard(char *text)
{
    ClipboardLength = strlen(text);
    Clipboard = DFrealloc(Clipboard, ClipboardLength);
    memmove(Clipboard, text, ClipboardLength);
}

void CopyToClipboard(WINDOW wnd)
{
    if (TextBlockMarked(wnd))    {
        char *bb = TextBlockBegin(wnd);	/* near pointers */
        char *be = TextBlockEnd(wnd);	/* near pointers */
        if (bb >= be) { /* *** 0.6e extra check *** */
            bb = TextBlockEnd(wnd);	/* sic! */
            be = TextBlockBegin(wnd);	/* sic! */
        }
        ClipboardLength = (unsigned) (be - bb); /* *** unsigned *** */
        Clipboard = DFrealloc(Clipboard, ClipboardLength);
        memmove(Clipboard, bb, ClipboardLength);
    }
}

void ClearClipboard(void)
{
    if (Clipboard != NULL)  {
        free(Clipboard);
        Clipboard = NULL;
    }
}


BOOL PasteText(WINDOW wnd, char *SaveTo, unsigned len)
{
    if (SaveTo != NULL && len > 0)    {
        unsigned plen = strlen(wnd->text) + len;

		if (plen <= wnd->MaxTextLength)	{
        	if (plen+1 > wnd->textlen)    {
            	wnd->text = DFrealloc(wnd->text, plen+3);
            	wnd->textlen = plen+1;
        	}
          	memmove(CurrChar+len, CurrChar, strlen(CurrChar)+1);
           	memmove(CurrChar, SaveTo, len);
           	BuildTextPointers(wnd);
           	wnd->TextChanged = TRUE;
			return TRUE;
		}
    }
	return FALSE;
}

