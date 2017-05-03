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

int subcribePlayer(char* nickname, int socket, game* game);

#endif