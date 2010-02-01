#!/bin/bash

files="src/checking/overwritten_functions.c src/patching/original_functions.c src/patching/socket_info.c"

save_files()
{
	while [ "$1" != "" ]
	do
		cp $1 $1.sav
		cp $1 $1.sav$$
		gcc -D_GNU_SOURCE -D_BSD_SOURCE -E -P -Isrc/common $1 | indent -st > $1.debug
		mv $1.debug $1

		shift
	done
}

restore_files()
{
	while [ "$1" != "" ]
	do
		mv $1.sav $1
		touch $1

		shift
	done
}

save_files $files
make
sudo make install
echo -n "DO THE DEBUG THEN PRESS <ENTER>... "
read a
restore_files $files
make
sudo make install
