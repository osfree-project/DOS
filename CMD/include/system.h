/* --------------- system.h -------------- */
#ifndef SYSTEM_H
#define SYSTEM_H

/* ----- programming basics ---- */

#include "portab.h"

typedef enum {FALSE, TRUE} BOOL;
#define swap(a,b){int x=a;a=b;b=x;}


typedef struct    {
    int lf,tp,rt,bt;
} RECT;



#define within(p,v1,v2)   ((p)>=(v1)&&(p)<=(v2))
#define RectTop(r)        (r.tp)
#define RectBottom(r)     (r.bt)
#define RectLeft(r)       (r.lf)
#define RectRight(r)      (r.rt)
#define InsideRect(x,y,r) (within((x),RectLeft(r),RectRight(r))\
                               &&                              \
                          within((y),RectTop(r),RectBottom(r)))
#define ValidRect(r)      (RectRight(r) || RectLeft(r) || \
                           RectTop(r) || RectBottom(r))
#define RectWidth(r)      (RectRight(r)-RectLeft(r)+1)
#define RectHeight(r)     (RectBottom(r)-RectTop(r)+1)

RECT subRectangle(RECT, RECT);


/* ----- interrupt vectors ----- */
#define TIMER  8
#define VIDEO  0x10
#define KEYBRD 0x16
#define DOS    0x21
#define CTRLBREAK 0x23
#define CRIT   0x24
#define MOUSE  0x33
#define KEYBOARDVECT 9
/* ------- platform-dependent values ------ */
#define KEYBOARDPORT 0x60
#define FREQUENCY 100
#define COUNT (1193280L / FREQUENCY)
#define ZEROFLAG 0x40
#define MAXSAVES 50
#define SCREENWIDTH  (peekb(0x40,0x4a) & 255)
#define SCREENHEIGHT (isVGA() || isEGA() ? peekb(0x40,0x84)+1 : 25)
#define clearBIOSbuffer() *(int far *)(MK_FP(0x40,0x1a)) = \
		        	      *(int far *)(MK_FP(0x40,0x1c));


/* ----- keyboard BIOS (0x16) functions -------- */
#define READKB 0
#define KBSTAT 1
/* ------- video BIOS (0x10) functions --------- */
#define SETCURSORTYPE 1
#define SETCURSOR     2
#define READCURSOR    3
#define READATTRCHAR  8
#define WRITEATTRCHAR 9
#define HIDECURSOR 0x20

/* ------- the interrupt function registers -------- */
typedef struct {
    int bp,di,si,ds,es,dx,cx,bx,ax,ip,cs,fl;
} IREGS;

/* ---------- keyboard prototypes -------- */
int AltConvert(int);
int Xbioskey(int); /* enhanced for 102 key keyboard support */
int getkey(void);
int getshift(void);
BOOL keyhit(void);
void beep(void);

/* ---------- cursor prototypes -------- */
void curr_cursor(int *x, int *y);
void cursor(int x, int y);
void hidecursor(void);
void unhidecursor(void);
void savecursor(void);
void restorecursor(void);
void normalcursor(void);
void set_cursor_type(unsigned t);
void videomode(void);
void SwapCursorStack(void);

/* --------- screen prototpyes -------- */
/* Call get_videomode before using these two: */
extern unsigned video_mode;
extern unsigned video_page;

void clearscreen(void);
void get_videomode(void);
unsigned int GetVideoChar(int, int);
void PutVideoChar(int, int, int);

#define videochar(x,y) (GetVideoChar(x,y) & 255)
#define vad(x,y) ((y)*(SCREENWIDTH*2)+(x)*2)
#define ismono() (video_mode == 7)
#define istext() (video_mode < 4)
#define clr(fg,bg) ((fg)|((bg)<<4))


/* ---------- mouse prototypes ---------- */
BOOL mouse_installed(void);
int mousebuttons(void);
void get_mouseposition(int *x, int *y);
void set_mouseposition(int x, int y);
void show_mousecursor(void);
void hide_mousecursor(void);
int button_releases(void);
void resetmouse(void);
void set_mousetravel(int, int, int, int);
#define leftbutton()     (mousebuttons()&1)
#define rightbutton()     (mousebuttons()&2)
#define waitformouse()     while(mousebuttons());


/* ----------- video adaptor prototypes ----------- */
BOOL isEGA(void);
BOOL isVGA(void);
void Set25(void);
void Set43(void);
void Set50(void);

#ifndef BLACK
/* ============= Color Macros ============ */
#define BLACK         0
#define BLUE          1
#define GREEN         2
#define CYAN          3
#define RED           4
#define MAGENTA       5
#define BROWN         6
#define LIGHTGRAY     7
#define DARKGRAY      8
#define LIGHTBLUE     9
#define LIGHTGREEN   10
#define LIGHTCYAN    11
#define LIGHTRED     12
#define LIGHTMAGENTA 13
#define YELLOW       14
#define WHITE        15
#endif


/* ---------- file system ---------- */

/* ----- Create unambiguous path from file spec, filling in the
     drive and directory if incomplete. Optionally change to
     the new drive and subdirectory ------ */
void CreatePath(char *spath,char *fspec,int InclName,int Change);


#endif
