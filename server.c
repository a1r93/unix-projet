/*
* server.c
* ROCHEZ Arnaud et PIRARD Delanoe
*
*/

#include "server.h"

int main(int argc, char const *argv[]) {
    message msg;
    int port, sck;
    struct sockaddr_in addr;
    fd_set fdset;

    static struct timeval tv;
    tv.tv_sec = 30;
    tv.tv_usec = 0;

    game gameServ;

    gameServ.nbplayers = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(-1);
    }

    port = atoi(argv[1]);
    sck = createSocket();
    bindSocketServer(sck, addr, port);

    listen(sck,4);

    while(1) {
        
    }
    
    return 0;
}

int subcribePlayer(char* nickname, int socket, game* game) {

}
