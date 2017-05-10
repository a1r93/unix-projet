/*
* utilities.c
* ROCHEZ Arnaud et PIRARD Delanoe
*
*/

#include "utilities.h" 

void sendMessage(int sck, message *msg){
	printf("Envoi de message... : %s\n", msg->text);
	if(send(sck, msg, sizeof(message),0)<0){
		perror("Erreur d'envoi du message.");
		exit(errno);
	}
}

int recvMessage(int sck, message *msg){
	printf("Reception de message... : %s\n", msg->text);
	int ret = recv(sck, msg, sizeof(message), 0);
	if(ret < 0){
		perror("Erreur de reception du message.");
    close(sck);
		exit(errno);
	}
	return ret;
}
