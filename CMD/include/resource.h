/* ------------- dflat.h ----------- */
#ifndef RESOURCE_H
#define RESOURCE_H

#include "dflatp.h"


/* ------- macros for commands and messages ------- */


#define BEGIN_USER_MESSAGES  enum user_messages { DEFAULT_USER_MESSAGE = 10000,
#define END_USER_MESSAGES    , LAST_USER_MESSAGE  };

#define BEGIN_DIALOG_MESSAGES  enum std_dialog_messages { DEFAULT_DIALOG_MESSAGE = 6000,
#define END_DIALOG_MESSAGES    , LAST_DIALOG_MESSAGE  };


#define BEGIN_USER_COMMANDS  enum user_commands { DEFAULT_USER_COMMAND = 10000,
#define END_USER_COMMANDS    , LAST_USER_COMMAND  };


/* --------- macros to define a menu bar with
                 popdowns and selections ------------- */
#define SEPCHAR "\xc4"
#define DEFMENU(m) MBAR m = {-1,{
#define POPDOWN(ttl,func,stat)     {ttl,func,stat,-1,0,{
#define CASCADED_POPDOWN(id,func)  {NULL,func,NULL,id,0,{
#define SELECTION(stxt,acc,id,attr)   {stxt,acc,id,attr,#acc},
#define SEPARATOR                     {SEPCHAR},
#define ENDPOPDOWN                    {NULL}}},
#define ENDMENU                {(char *)-1} }};
	

/* ------------ Macros to describe a Module      ---------- */

#define DEFPROGRAM  MODULE ProgramModule = {
#define DEFDFLATP   MODULE DFlatpModule = {
#define MOD_DESCRIPTION(s)   s,
#define MOD_VERSION(m1,m2,r,p)  m1,m2,r,p,
#define MOD_COPYRIGHT(s)     s
#define MOD_LICENSE(s)      ,s
#define MOD_ABOUT(s)        ,s
#define END_DEFMODULE        };



#endif
