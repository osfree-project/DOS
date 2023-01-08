include "resource.id"
resIdBlock macro x, y
	dd	???ende - ???start		;; Length of this resource
	dw x						;; major resource ID
	dw y						;; minor resource ID
	db 'FREECOM '				;; cookie
endm
