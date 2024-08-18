PORT_NAME = dos$(SEP)debug
PORT_TYPE = git
PORT_URL  = https://github.com/Baron-von-Riedesel/DOS-debug
PORT_REV  = v2.50
PORT_PATCHES  = debug.diff

!include $(%ROOT)tools/mk/port.mk
