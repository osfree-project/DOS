#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

32_BITS = 0
PROJ      = lib
TRGT      = $(PROJ).lib
DESC      = DOS command interpreter
#defines object file names in format objname.$(O)
srcfiles = $(p)myperror$(e) $(p)absfile$(e) $(p)almemblk$(e) $(p)alprmblk$(e) $(p)alsysblk$(e) $(p)app_get$(e) &
        $(p)app_set$(e) $(p)beep_l$(e) $(p)beep_n$(e) $(p)brk_get$(e) $(p)brk_set$(e) $(p)cbreak$(e) &
        $(p)cbs$(e) $(p)cd_dir$(e) $(p)cgetch$(e) $(p)cgettime$(e) $(p)chgctxt$(e) $(p)chgdrv$(e) &
        $(p)chgenv$(e) $(p)chgenvc$(e) $(p)chgenvr$(e) $(p)clrline$(e) $(p)cmdinput$(e) $(p)comfile$(e) &
        $(p)compfile$(e) $(p)critend$(e) $(p)critrchk$(e) $(p)ctxt$(e) $(p)ctxt_adr$(e) $(p)ctxt_as$(e) &
        $(p)ctxt_chg$(e) $(p)ctxt_clr$(e) $(p)ctxt_get$(e) $(p)ctxt_inf$(e) $(p)ctxt_mk$(e) &
        $(p)ctxt_mkb$(e) $(p)ctxt_mkn$(e) $(p)ctxt_pop$(e) $(p)ctxt_psh$(e) $(p)ctxt_rnu$(e) &
        $(p)ctxt_set$(e) $(p)ctxt_ss$(e) $(p)ctxt_vw$(e) $(p)curdatel$(e) $(p)curtime$(e) $(p)cwd$(e) &
        $(p)dateget$(e) $(p)dateset$(e) $(p)dbg_c$(e) $(p)dbg_mem$(e) $(p)dbg_prnt$(e) $(p)dbg_s$(e) &
        $(p)dbg_sn$(e) $(p)devopen$(e) $(p)dfn_err$(e) $(p)dispcnt$(e) $(p)dispexit$(e) $(p)drvnum$(e) &
        $(p)efct_001$(e) $(p)exec$(e) $(p)exec1$(e) $(p)farread$(e) &
#        $(p)fcompl1$(e) $(p)fcompl2$(e) &
        $(p)fdattr$(e) $(p)fdevopen$(e) $(p)fdsattr$(e) $(p)filecomp$(e) $(p)fillcomp$(e) $(p)find$(e) $(p)freep$(e) &
        $(p)frsysblk$(e) $(p)fstpcpy$(e) $(p)gallstr$(e) $(p)get1mcb$(e) $(p)getenv$(e) $(p)goxy$(e) &
        $(p)grabfcom$(e) $(p)gumblink$(e) $(p)hdlrctxt$(e) $(p)hist_get$(e) $(p)hist_set$(e) &
        $(p)inputdos$(e) $(p)is_empty$(e) $(p)is_fnamc$(e) $(p)is_fnstr$(e) $(p)is_pchr$(e) &
        $(p)isadev$(e) $(p)keyprsd$(e) $(p)kswap_c$(e) $(p)lastdget$(e) $(p)lastdset$(e) $(p)leadopt$(e) &
        $(p)lfnfuncs$(e) $(p)lowexec$(e) &
        $(p)ltrimcl$(e) $(p)ltrimsp$(e) $(p)lwr1wd$(e) $(p)match$(e) $(p)messages$(e) &
        $(p)mk_rddir$(e) $(p)mktmpfil$(e) $(p)msg_dflt$(e) $(p)msg_dps$(e) $(p)msg_fstr$(e) &
        $(p)msg_get$(e) $(p)msg_gpt$(e) $(p)msg_mkey$(e) $(p)msg_prmp$(e) $(p)mux_ae$(e) $(p)nls$(e) &
        $(p)nls_date$(e) $(p)nls_time$(e) $(p)num_fmt$(e) $(p)onoff$(e) $(p)openf$(e) $(p)optsb$(e) &
        $(p)optsi$(e) $(p)optss$(e) $(p)parsenum$(e) $(p)prf$(e) $(p)pr_date$(e) $(p)pr_prmpt$(e) $(p)pr_time$(e) &
        $(p)prprompt$(e) $(p)readcmd$(e) $(p)realnum$(e) $(p)res$(e) $(p)res_r$(e) $(p)res_vald$(e) &
        $(p)res_w$(e) $(p)resfile$(e) $(p)rmtmpfil$(e) $(p)rtrimcl$(e) $(p)rtrimsp$(e) $(p)salloc$(e) &
        $(p)samefile$(e) $(p)scancmd$(e) $(p)scanopt$(e) $(p)session$(e) $(p)showcmds$(e) $(p)skqwd$(e) &
        $(p)spfnam$(e) $(p)split$(e) $(p)sumblink$(e) &
#        $(p)tempfile$(e) &
        $(p)timeget$(e) $(p)timeset$(e) &
        $(p)tmpnam$(e) $(p)trimcl$(e) $(p)trimsp$(e) $(p)truepath$(e) $(p)truncate$(e) $(p)txtlend$(e) &
        $(p)unquote$(e) $(p)vcgetch$(e) $(p)vcgetstr$(e) $(p)where$(e) &
$(p)err1$(e) &
$(p)err10$(e) &
$(p)err11$(e) &
$(p)err12$(e) &
$(p)err13$(e) &
$(p)err14$(e) &
$(p)err15$(e) &
$(p)err16$(e) &
$(p)err17$(e) &
$(p)err18$(e) &
$(p)err19$(e) &
$(p)err2$(e) &
$(p)err20$(e) &
$(p)err21$(e) &
$(p)err22$(e) &
$(p)err23$(e) &
$(p)err24$(e) &
$(p)err25$(e) &
$(p)err26$(e) &
$(p)err27$(e) &
$(p)err28$(e) &
$(p)err29$(e) &
$(p)err3$(e) &
$(p)err30$(e) &
$(p)err31$(e) &
$(p)err32$(e) &
$(p)err33$(e) &
$(p)err34$(e) &
$(p)err35$(e) &
$(p)err36$(e) &
$(p)err37$(e) &
$(p)err38$(e) &
$(p)err39$(e) &
$(p)err4$(e) &
$(p)err40$(e) &
$(p)err41$(e) &
$(p)err42$(e) &
$(p)err43$(e) &
$(p)err44$(e) &
$(p)err45$(e) &
$(p)err46$(e) &
$(p)err47$(e) &
$(p)err48$(e) &
$(p)err49$(e) &
$(p)err5$(e) &
$(p)err50$(e) &
$(p)err51$(e) &
$(p)err52$(e) &
$(p)err53$(e) &
$(p)err54$(e) &
$(p)err55$(e) &
$(p)err56$(e) &
$(p)err57$(e) &
$(p)err58$(e) &
$(p)err59$(e) &
$(p)err6$(e) &
$(p)err60$(e) &
$(p)err61$(e) &
$(p)err62$(e) &
$(p)err63$(e) &
$(p)err64$(e) &
$(p)err65$(e) &
$(p)err66$(e) &
$(p)err67$(e) &
$(p)err68$(e) &
$(p)err69$(e) &
$(p)err7$(e) &
$(p)err70$(e) &
$(p)err71$(e) &
$(p)err72$(e) &
$(p)err73$(e) &
$(p)err74$(e) &
$(p)err75$(e) &
$(p)err76$(e) &
$(p)err77$(e) &
$(p)err78$(e) &
$(p)err79$(e) &
$(p)err8$(e) &
$(p)err80$(e) &
$(p)err81$(e) &
$(p)err82$(e) &
$(p)err83$(e) &
$(p)err84$(e) &
$(p)err85$(e) &
$(p)err86$(e) &
$(p)err87$(e) &
$(p)err9$(e)
#DEBUG = all


# defines additional options for C compiler

!include $(%ROOT)tools/mk/libsdos.mk
!include $(MYDIR)..$(SEP)port$(SEP)freecom.mk

.asm: $(PORT_BASE)lib

.c:   $(PORT_BASE)lib

#XMS_SWAP=1

ADD_COPT   = &
!ifdef XMS_SWAP
  -dXMS_SWAP=1 &
!endif
  -dNDEBUG &
#  -dDEBUG &
#  -d1 &
  -ml -dMODEL=l -i=$(BLD)DOS$(SEP)CMD$(SEP)command$(SEP)strings$(SEP)critstrs -i=$(PORT_BASE)lib -i=$(PORT_BASE) &
  -i=$(PATH)..$(SEP)criter$(SEP)criter1 -i=$(PORT_BASE)suppl -i=$(PORT_BASE)include &
  -i=$(MYDIR)..$(SEP)..$(SEP)include -i=$(PATH)

ADD_ASMOPT = &
!ifdef XMS_SWAP
  -dXMS_SWAP=1 &
!endif
  -dNDEBUG &
#  -dDEBUG &
#  -d1 &
  -ml -dMODEL=l -i=$(BLD)DOS$(SEP)CMD$(SEP)command$(SEP)strings$(SEP)critstrs -i=$(PORT_BASE)lib -i=$(PORT_BASE)contrib &
  -i=$(PATH)..$(SEP)criter$(SEP)criter1 -i=$(PORT_BASE)suppl -i=$(PORT_BASE)include &
  -i=$(MYDIR)..$(SEP)..$(SEP)include -i=$(PATH)

ADD_LINKOPT = lib $(BLD)lib$(SEP)doscmd_shared.lib
TARGETS = $(PATH)lib.lib

$(TARGETS): $(OBJS)
 @$(MAKE) $(MAKEOPT) library=$(TARGETS) library
