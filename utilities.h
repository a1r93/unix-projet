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
#include    <sys/wait.h>

#define SYS(call) ((call) == -1) ? (perror(#call ":ERROR"),exit(1)) : 0

#define CONNECTION 1
#define DECONNECTION 2
#define TEST 3
#define GAME 4
#define GAMESTART 5
#define CHOOSE_CARD 6
#define PLI 7

#define PIQUE 1
#define CAREAU 2
#define COEUR 3
#define TREFLE 4

#define TROP_JOUEURS -1
#define PARTIE_EN_COURS 0
#define MAX_PLAYERS 4
#define BUFSIZE 256
#define NB_CARDS 32
#define NB_COLORS 4
static char ibuf[BUFSIZE];

typedef struct Message {
	int typeMsg;
	char text[256];
} message;

typedef struct card {
    int color;
    int value;
} card;

typedef struct player {
    char nickname[25];
    int score;
    int sck;
    card* cards;
    int nbcards;
    card* takencards;
} player;

typedef struct game {
    player players[MAX_PLAYERS];
    int nbplayers;
} game;

void sendMessage(int sck, message* msg);
int recvMessage(int sck, message* msg);
card* getCards(int* nbCards);

#endif
