# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PORT_NAME = dos$(SEP)attrib
PORT_TYPE = git
PORT_URL  = https://github.com/FDOS/attrib
PORT_REV  = 
PORT_PATCHES  = attrib.diff attrib2.diff

!include $(%ROOT)tools/mk/port.mk
