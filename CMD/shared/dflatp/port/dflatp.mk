# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PORT_NAME = dos$(SEP)dflatp
PORT_TYPE = wget
PORT_URL  = https://ulukai.org/ecm/editsrc/dfp100s.zip
PORT_REV  = 
PORT_PATCHES  = dflatp.diff

!include $(%ROOT)tools/mk/port.mk
