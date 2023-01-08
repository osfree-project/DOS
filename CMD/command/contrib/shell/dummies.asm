; $Id$

; Dummy drivers to be included into FreeCOM itself

include model.inc
include stuff.inc

_TEXT segment word public 'CODE' use16

        public _dummy_criter_handler
        public _end_dummy_criter_handler
_dummy_criter_handler:
	mov al, 3			; always fail
	iret
_end_dummy_criter_handler:

_TEXT ends

      end
