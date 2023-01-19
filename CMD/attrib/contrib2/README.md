ATTRIB 
======

v2.1 - Displays or changes file attributes.


Copyright (c) 1998-2003, licensed under GNU GPL 2.
Written by: Phil Brutsche


Syntax:
-------
ATTRIB { *options* | [path\][file] | /@[list] }


Options:
--------
 * +H  Sets the Hidden attribute.     -H  Clears the Hidden attribute.
 * +S  Sets the System attribute.     -S  Clears the System attribute.
 * +R  Sets the Read-only attribute.  -R  Clears the Read-only attribute.
 * +A  Sets the Archive attribute.    -A  Clears the Archive attribute.
 * /S  Process files in all directories in the specified path(es).
 * /D  Process directory names for arguments with wildcards.
 * /@  Process files, listed in the specified file [or in stdin].


Examples:
---------
 * `attrib file -rhs`
 * `attrib +a -r dir1\ dir2\*.dat /s`
 * `attrib -hs/sd /@list.txt *.*`
