; $Id$
;	Criter and ^Break handler for external programs for XMS Swap
;	variant

include model.inc
include stuff.inc

TEXT  segment word public 'CODE' use16

	cglobal lowlevel_cbreak_handler
lowlevel_cbreak_handler:
include "../criter/dmy_cbrk.asm"

TEXT  ends

      end
