#!/bin/bash
cp overwritten_functions.c overwritten_functions.c.sav
cp overwritten_functions.c overwritten_functions.c.sav$$
gcc -E -P overwritten_functions.c | indent -st > overwritten_functions.debug
cp overwritten_functions.debug overwritten_functions.c
make
echo -n "DO THE DEBUG THEN PRESS <ENTER>... "
read a
mv overwritten_functions.c.sav overwritten_functions.c
make
