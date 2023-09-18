# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PORT_NAME = dos$(SEP)assign
PORT_TYPE = git
PORT_URL  = https://gitlab.com/FreeDOS/base/assign.git
PORT_REV  = v1.4a
#PORT_PATCHES  = freecom.diff

!include $(%ROOT)tools/mk/port.mk
