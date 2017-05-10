all: server player

player: player.o socket.o utilities.o
	cc -o player player.o socket.o utilities.o

player.o: player.c socket.h utilities.h
	cc -c player.c

server: server.o socket.o utilities.o
	cc -o  server server.o socket.o utilities.o

server.o: server.c socket.h utilities.h
	cc -c server.c

socket.o: socket.c socket.h utilities.h
	cc -c socket.c

utilities.o: utilities.c utilities.h
	cc -c utilities.c 
