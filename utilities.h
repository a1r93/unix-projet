/*
*
* utilities.h
* ROCHEZ Arnaud et PIRARD Delanoe
*
*/

#if !defined(_UTILITIES_H_)
#define _UTILITIES_H_

#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <errno.h>
#include    <unistd.h>
#include    <fcntl.h>
#include    <sys/types.h>
#include    <sys/socket.h>

#define SYS(call) ((call) == -1) ? (perror(#call ":ERROR"),exit(1)) : 0

#define CONNECTION 1
#define DECONNECTION 2
#define TEST 3

#define TROP_JOUEURS -1
#define PARTIE_EN_COURS 0
#define MAX_PLAYERS 4
#define BUFSIZE 256
static char ibuf[BUFSIZE];

typedef struct Message {
	int typeMsg;
	char text[256];
} message;

typedef struct player {
    char nickname[25];
    int score;
    int sck;
} player;

typedef struct game {
    player players[MAX_PLAYERS];
    int nbplayers;
} game;

void sendMessage(int sck, message* msg);
int recvMessage(int sck, message* msg);

#endif
