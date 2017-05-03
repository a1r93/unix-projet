/*
* socket.h
* ROCHEZ Arnaud et PIRARD Delanoe, série 1
*
*/

#if !defined(_SERVER_H_)
#define _SERVER_H_

#include "socket.h"
#include "utilities.h"

#include <signal.h>

#include <netinet/in.h>

#define MAX_PLAYERS 4

typedef struct player {
    char nickname[25];
    int score;
    int sck;
}

typedef struct game {
    player players[MAX_PLAYERS];
    int nbplayers;
}

int subcribePlayer(char* nickname, int socket, game* game);

#endif