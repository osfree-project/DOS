# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PORT_NAME = dos$(SEP)mem
PORT_TYPE = git
PORT_URL  = https://gitlab.com/FreeDOS/base/mem.git
PORT_REV  = 
PORT_PATCHES = mem.diff

!include $(%ROOT)tools/mk/port.mk
