/*
* socket.c
* ROCHEZ Arnaud et PIRARD Delanoe
*
*/

#include "socket.h"

int createSocket() {
	printf("Creation du socket...\n");
	int sck;
	if((sck = socket(AF_INET,SOCK_STREAM,0)) < 0 ) {
		perror("Erreur lors de la création du socket\n");
		exit(1);
	}
	return sck;
}

void bindSocketServer(int sck, struct sockaddr_in addr, int port) {
	bzero((char*)&addr,sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
	
	if(bind(sck, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Le socket n'a pas pu se lier\n");
		exit(1);
	}
}

void connectSocketPlayer(int sck, struct sockaddr_in addr, struct hostent* host, int port) {
	bzero((char*)&addr,sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	bcopy(host->h_addr,(char*)&addr.sin_addr.s_addr,host->h_length);
	addr.sin_port = htons(port);
	
	if( connect(sck, (struct sockaddr *)&addr, sizeof(addr)) < 0 ) {
		perror("Erreur lors de la connexion au socket\n");
		exit(1);
	}
}

int acceptSocketPlayer(int sck) {
	struct sockaddr_in addr2;
    u_int len2 = sizeof(addr2);
    int ret = accept(sck, (struct sockaddr *) &addr2, &len2);

    return ret;
}
