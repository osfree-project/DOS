; $Id$
;	Criter and ^Break handler for external programs for XMS Swap
;	variant

include model.inc
include stuff.inc

_TEXT  segment word public 'CODE' use16

	public _lowlevel_cbreak_handler
_lowlevel_cbreak_handler:
include "../criter/dmy_cbrk.asm"

_TEXT  ends

      end
