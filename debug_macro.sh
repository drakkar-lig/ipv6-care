#!/bin/bash
cp src/checking/overwritten_functions.c src/checking/overwritten_functions.c.sav
cp src/checking/overwritten_functions.c src/checking/overwritten_functions.c.sav$$
gcc -E -P -Isrc/common src/checking/overwritten_functions.c | indent -st > src/checking/overwritten_functions.debug
cp src/checking/overwritten_functions.debug src/checking/overwritten_functions.c
make
sudo make install
echo -n "DO THE DEBUG THEN PRESS <ENTER>... "
read a
mv src/checking/overwritten_functions.c.sav src/checking/overwritten_functions.c
touch src/checking/overwritten_functions.c
make
sudo make install
