# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PORT_NAME = dos$(SEP)freecom
PORT_TYPE = git
PORT_URL  = https://github.com/FDOS/freecom
PORT_REV  = com085a
PORT_PATCHES  = freecom.diff freecom2.diff

!include $(%ROOT)tools/mk/port.mk
