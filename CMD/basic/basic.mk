# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PORT_NAME = dos$(SEP)basic
PORT_TYPE = git
PORT_URL  = https://github.com/nerun/bwbasic/
PORT_REV  = 
PORT_PATCHES  = basic.diff

!include $(%ROOT)tools/mk/port.mk
