all: es1.exe

es1.exe : es1.o checkgroup.o
	gcc -o es1.exe es1.o checkgroup.o

es1.o :  checkgroup.h es1.c
	gcc -c es1.c

checkgroup.o :  checkgroup.h checkgroup.c
	gcc -c checkgroup.c
