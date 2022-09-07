/* ---------------- commands.h ----------------- */

/*
 * Command values sent as the first parameter
 * in the COMMAND message
 *
 * Add application-specific commands to this enum
 */

#ifndef COMMANDS_H
#define COMMANDS_H


enum commands {
    /* --------------- System menu -------------- */
#ifdef INCLUDE_RESTORE
    ID_SYSRESTORE,
#endif
    ID_SYSMOVE,
    ID_SYSSIZE,
#ifdef INCLUDE_MINIMIZE
    ID_SYSMINIMIZE,
#endif
#ifdef INCLUDE_MAXIMIZE
    ID_SYSMAXIMIZE,
#endif
    ID_SYSCLOSE,
    /* --------------- Edit box  ---------------- */
    ID_UNDO,
    ID_CUT,
    ID_COPY,
    ID_PASTE,
    ID_PARAGRAPH,
    ID_CLEAR,
    ID_DELETETEXT,
    ID_UPCASE,
    ID_DOWNCASE,
    ID_WORDCOUNT,
    ID_SEARCH,
    ID_REPLACE,
    ID_SEARCHNEXT,
    /* ---- FileOpen and SaveAs dialog boxes ---- */
    ID_FILENAME,
    ID_FILES,
    ID_DIRECTORY,
    ID_DRIVE,
    ID_PATH,
    /* ----- Search and Replace dialog boxes ---- */
    ID_SEARCHFOR,
    ID_REPLACEWITH,
    ID_MATCHCASE,
    ID_REPLACEALL,
    /* ----------- Windows dialog box ----------- */
    ID_WINDOWLIST,
    /* --------- generic command buttons -------- */
    ID_OK,
    ID_CANCEL,
    ID_HELP,
    /* ------------ Display dialog box ---------- */
    ID_BORDER,
    ID_TITLE,
    ID_STATUSBAR,
    ID_TEXTURE,
	ID_SNOWY,
    ID_COLOR,
    ID_MONO,
    ID_REVERSE,
    ID_25LINES,
    ID_43LINES,
    ID_50LINES,
	/* ---------- Print Select dialog box --------- */
	ID_PRINTERPORT,
	ID_LEFTMARGIN,
	ID_RIGHTMARGIN,
	ID_TOPMARGIN,
	ID_BOTTOMMARGIN,
	/* ----------- InputBox dialog box ------------ */
	ID_INPUTTEXT
};

#endif
