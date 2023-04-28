all: server.exe client.exe

server.exe: server.c
	gcc server.c -o server.exe

client.exe: client.c
	gcc client.c -o client.exe
	
clean:
	rm client.exe server.exe
