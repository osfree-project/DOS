/* ------------- syshelp.c ------------- */

#include "dfpcomp.h"



static BOOL (* UserHelp)(WINDOW, char *);



BOOL InstallHelpProcedure ( BOOL (* f) () )
{
		if (f != NULL)
		{
			UserHelp = f;
			return TRUE;
		}
		else
			return FALSE;
}


BOOL SystemHelp(WINDOW w, char *topic)
{
			return  (*UserHelp) (w, topic);
}

