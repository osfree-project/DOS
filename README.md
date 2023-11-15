# osFree DOS Subsystem

## Introdution

osFree DOS subsystem is a (mostly) FreeDOS version adopted to
run under osFree MVM (OS/2 VDM/MVDM).

## DOSKRNL

DOSKRNL is a modified FreeDOS kernel to be used in osFree MVM
and uses SVC API to call host services.

## API

osFree DOS subsystem consist of standard DOS API with some small
OS/2 VDM specific extensions. Most of API implemented in DOS
kernel, but some as virtual device drivers. For documentation
see https://osfree.org/doku/en:docs:dos

## Family API

Family API is a dual mode library which allows to create executables
which works under DOS and OS/2. See http://osfree.org/doku/en:docs:fapi 
for more info

## Libraries

- DFlat+
- Supplimental

## Command processor

- command.com

## Command line tools

- append
- assign
- attrib
- basic
- comp
- debug
- diskcomp
- diskcopy
- doskey
- edlin
- exit_vdm
- find
- fsaccess
- help
- helpmsg
- join
- label
- mem
- more
- move
- qbasic
- sort
- stub
- subst
- vmdisk
- xcopy
