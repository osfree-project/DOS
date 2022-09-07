/* --------------- system.h -------------- */
#ifndef SYSINT_H
#define SYSINT_H


#include "system.h"

#define swap(a,b){int x=a;a=b;b=x;}
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

#ifdef HOOKKEYB
/* if irq 9 hooked, waitforkeyboard clears buffer until key released */
/* (used to wait for a key but also to zap special keys from buffer) */
#define waitforkeyboard() while ((keyportvalue & 0x80) == 0) \
						  clearBIOSbuffer()
#else
/* if irq 9 not hooked, waitforkeyboard only drains buffer */
/* (used for "press a key to continue" cases only) */
#define waitforkeyboard() while (Xbioskey(1)) (void)Xbioskey(0)
#endif

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
void clearscreen(void);
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
/* ------------ timer macros -------------- */
#ifdef HOOKTIMER /* if timer IRQ handler in use - classic style */
#define timed_out(timer)         (timer==0)
#define set_timer(timer, secs)     timer=(secs)*182/10+1
#define set_timer_ticks(timer, ticks)     timer=(ticks)
#define disable_timer(timer)     timer = -1
#define timer_running(timer)     (timer > 0)
#define countdown(timer)         --timer
#define timer_disabled(timer)     (timer == -1)
#else /* else use functions in message.c (by ea) */
	/* functions only use constants in timer variables  */
	/* to identify which timer is used! So take care:   */
	/* Never manipulate timer variables directly!   -ea */
int timed_out(int timer);
void set_timer(int timer, int secs);
void set_timer_ticks(int timer, int ticks);
void disable_timer(int timer);
int timer_running(int timer);
/* void countdown(int timer); -- only used in IRQ handler anyway -- */
int timer_disabled(int timer);
#endif

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


#endif
