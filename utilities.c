/*
* utilities.c
* ROCHEZ Arnaud et PIRARD Delanoe
*
*/

#include "utilities.h" 

void sendMessage(int sck, message *msg){
	printf("Envoi de message au serveur...\n");
	if(send(sck, msg, sizeof(message),0)<0){
		perror("Erreur d'envoi du message.");
		exit(errno);
	}
}

int recvMessage(int sck, message *msg){
	printf("Reception de message de client...\n");
	int ret = recv(sck, msg, sizeof(message), 0);
	if(ret < 0){
		perror("Erreur de reception du message.");
    close(sck);
		exit(errno);
	}
	return ret;
}
