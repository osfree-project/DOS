/* ---------------- video.h ----------------- */

#ifndef VIDEO_H
#define VIDEO_H

#include "dfpcomp.h"

void getvideo(RECT, void far *);
void storevideo(RECT, void far *);


void wputch(WINDOW, int, int, int);
void wputs(WINDOW, void *, int, int);
void scroll_window(WINDOW, RECT, int);



#endif
