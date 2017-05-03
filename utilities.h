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

#define SYS(call) ((call) == -1) ? (perror(#call ":ERROR"),exit(1)) : 0

#define CONNEXION 1
#define DECONNEXION 2

#define TROP_JOUEURS -1
#define PARTIE_EN_COURS 0
#define MAX_PLAYERS 4

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
