/*
* socket.h
* ROCHEZ Arnaud et PIRARD Delanoe, série 1
*
*/

#if !defined(_SERVER_H_)
#define _SERVER_H_

#include "socket.h"
#include "utilities.h"
#include "sharedMemory.h"

#include <signal.h>

#include <netinet/in.h>

int subcribePlayer(char* nickname, int sck, game* game);
void int_handler(int unused);
void startManche();
void distributeCards(int nbCards);
void startTour(int* nbCards);

#endif