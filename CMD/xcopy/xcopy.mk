# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PORT_NAME = dos$(SEP)xcopy
PORT_TYPE = git
PORT_URL  = https://github.com/FDOS/xcopy
PORT_REV  = 

!include $(%ROOT)tools/mk/port.mk
