# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PORT_NAME = dos$(SEP)debug
PORT_TYPE = git
PORT_URL  = https://github.com/Baron-von-Riedesel/DOS-debug
PORT_REV  = v2.02
PORT_PATCHES  = debug.diff

!include $(%ROOT)tools/mk/port.mk
