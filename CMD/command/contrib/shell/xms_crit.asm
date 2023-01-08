; $Id$
;	Criter and ^Break handler for external programs for XMS Swap
;	variant

include model.inc

;; If the include is in here, NASM locks up, suck all CPU
;	global _lowlevel_cbreak_handler
;_lowlevel_cbreak_handler:
;%include "../criter/dmy_cbrk.asm"

XMS_SWAP_CRITER equ 1
NO_RESOURCE_BLOCK equ 1

include "../criter/criter.asm"
