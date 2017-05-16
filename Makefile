all: server.exe player.exe

player.exe: player.o socket.o utilities.o
	gcc -o player.exe player.o socket.o utilities.o

player.o: player.c socket.h utilities.h
	gcc -c player.c

server.exe: server.o socket.o utilities.o
	gcc -o server.exe server.o socket.o utilities.o

server.o: server.c socket.h utilities.h
	gcc -c server.c

socket.o: socket.c socket.h utilities.h
	gcc -c socket.c

utilities.o: utilities.c utilities.h
	gcc -c utilities.c 
