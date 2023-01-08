;; Multi-Push/Pop
;; Both take the registers in the same order, "F"==Flags
;; Push pushes left to right; pop right to left

;;;; ported to wasm/masm by valerius

pushm macro args
  push bp                               ; Save old bp
  mov  bp, sp                           ; bp->old bp in stack
  irp  y, <args>                        ;
    ifidni y, f                         ; Save
      pushf                             ;
    else                                ; regs
      push y                            ;
    endif                               ; in specified order
  endm                                  ;   
  push bp                               ; save bp on stack top
  mov  bp, [bp]                         ; restore old bp
endm

popm macro args
  push bp                               ; Save old bp
  mov  bp, sp                           ; bp->stack top (which contain stack frame bottom address)
  mov  bp, [bp]                         ; now bp->stack bottom
  irp  y, <args>                        ;
    dec  bp                             ; next
    dec  bp                             ; variable
    push word ptr [bp]                  ;
    ifidni y, f                         ;
      popf                              ;
    else                                ; Restore registers
      pop y                             ; in reverse order
    endif                               ;
  endm                                  ;
  pop  bp                               ; restore initial bp
endm                                    ;

cglobal macro args
  irp y, <args>
    ;ifnidn __OUTPUT_FORMAT__,elf
    ;  define y _y
    ;endif
      public y
  endm
endm

cextern macro args
  irp y, <args>
    ;ifnidn __OUTPUT_FORMAT__,elf
    ;  define y _y
    ;endif
      extrn y
  endm
endm
