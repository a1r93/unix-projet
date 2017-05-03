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

sockaddr_in createSockaddr();

void bindSocketServer(int* sck, sockaddr_in* addr);

void connectSocketPlayer(int* sck, sockaddr_in* addr, char* host, char* port);



#endif