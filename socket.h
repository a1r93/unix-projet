/*
* socket.h
* ROCHEZ Arnaud et PIRARD Delanoe, série 1
*
*/

#if !defined(_SOCKET_H_)
#define _SOCKET_H_

#include "utilities.h"

#include    <netdb.h>
#include    <signal.h>
#include    <sys/socket.h>
#include    <sys/types.h>

#include    <netinet/in.h>

/*
* Create a socket and send a descriptor.
*/
int createSocket();

struct sockaddr_in createSockaddr();

void bindSocketServer(int sck, struct sockaddr_in addr, int port);

void connectSocketPlayer(int sck, struct sockaddr_in addr, struct hostent* host, int port);

int acceptSocketPlayer(int sck);

#endif