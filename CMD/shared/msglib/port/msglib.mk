# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PORT_NAME = dos$(SEP)msglib
PORT_TYPE = wget
PORT_URL  = https://www.ibiblio.org/pub/micro/pc-stuff/freedos/files/devel/libs/msglib/msglib.zip
PORT_REV  = 
#PORT_PATCHES  = dflatp.diff

!include $(%ROOT)tools/mk/port.mk
