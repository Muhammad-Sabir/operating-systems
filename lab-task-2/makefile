all: prod.exe cons.exe

prod.exe: prod.c myheader.h
	gcc -o prod.exe prod.c

cons.exe: cons.c myheader.h
	gcc -o cons.exe cons.c
	
clean:
	rm prod.exe cons.exe
