# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $



PORT_NAME = dos$(SEP)edlin
PORT_TYPE = wget
PORT_URL  = https://sourceforge.net/projects/freedos-edlin/files/freedos-edlin/2.24/edlin-2.24.zip/download
PORT_REV  = 

!include $(%ROOT)tools/mk/port.mk
