# osFree DOS Subsystem

## Introdution

osFree DOS subsystem is a (mostly) FreeDOS version adopted to
run under osFree MVM (OS/2 VDM/MVDM).

## DOSKRNL

DOSKRNL is a modified FreeDOS kernel to be used in osFree MVM
and uses SVC API to call host services. It is not required to have  special version of kernel to run in MVM, but to provide access to filesystem it is required to have redirector (like vbox guest additions or MVDM fsaccess driver). Also, special kernel provide more free memory for programs because doesn't contains many parts of code like config.sys parser and filesystem support. also, most of drivers work out of DOS space.

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

- command.com DOS only

## Command line tools

- append DOS only
- assign DOS only
- attrib Dual mode
- basic
- choice
- comp
- debug DOS only
- diskcomp
- diskcopy
- doskey
- edlin
- exit_vdm DOS only
- find
- fsaccess DOS only
- graftabl DOS only
- help DOS only
- helpmsg
- join DOS only
- label
- mem DOS only
- more
- move
- qbasic
- sort
- stub
- subst DOS only
- xcopy
