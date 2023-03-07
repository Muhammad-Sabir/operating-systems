simple: simple.o libsimple.a
	gcc -o simple simple.o -L. -lsimple

simple.o: simple.c simple.h
	gcc -c simple.c

libsimple.a: util.o
	ar cr libsimple.a util.o

util.o: util.c
	gcc -c util.c
