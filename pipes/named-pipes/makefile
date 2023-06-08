all: reader.exe writer.exe

writer.exe: npipe_writer.c
	gcc npipe_writer.c -o writer.exe
	
reader.exe: npipe_reader.c
	gcc npipe_reader.c -o reader.exe
	
clean:
	rm reader.exe writer.exe
