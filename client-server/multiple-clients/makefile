all: server.exe client1.exe client2.exe client3.exe

server.exe: server.c
	gcc server.c -o server.exe

client1.exe: client1.c
	gcc client1.c -o client1.exe
	
client2.exe: client2.c
	gcc client2.c -o client2.exe
	
client3.exe: client3.c
	gcc client3.c -o client3.exe
	
clean:
	rm client1.exe client2.exe client3.exe server.exe
