#
# A main Makefile for OS/3 boot sequence project
# (c) osFree project,
# valerius, 2006/10/30
#

# First directory must be SHARED which provides shared libs

DIRS = shared doskrnl CMD WIN16

!include $(%ROOT)tools/mk/all.mk

#TARGETS=subdirs
#TARGET=all
