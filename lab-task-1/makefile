mycalc: main.o libmymathlib.a
	gcc -o mycalc main.o -L. -lmymathlib

main.o: main.c
	gcc -c main.c

add.o: add.c
	gcc -c add.c

sub.o: sub.c
	gcc -c sub.c

mul.o: mul.c
	gcc -c mul.c

div.o: div.c
	gcc -c div.c

libmymathlib.a: add.o sub.o mul.o div.o
	ar cr libmymathlib.a add.o sub.o mul.o div.o
