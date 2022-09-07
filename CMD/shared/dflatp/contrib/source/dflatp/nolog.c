/* ------------ nolog .c ------------ */
/* Link to this to create non-logging DFlat+ app */


#include "dflatp.h"
#include "dfptools.h"


BOOL LogMessageStart ( WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2 )
{
		return TRUE;
}


BOOL LogMessageEnd ( WINDOW wnd, MESSAGE msg, PARAM p1, PARAM p2 )
{
		return TRUE;
}


