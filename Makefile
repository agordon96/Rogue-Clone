all:
	gcc -Wall -std=c99 -pedantic src/rogue.c src/functions.c -Iinclude -o bin/runMe -lncurses
