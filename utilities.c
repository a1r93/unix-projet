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

card* getCards(int *nbCards) {
	card* cards;
	int i, j;
	*nbCards = 0;

	for (i = 0; i < NB_CARDS/NB_COLORS; i++) {
		for (j = 0; j < NB_COLORS; j++) {
			card newCard;
			newCard.color = j;
			newCard.value = i;
			cards[*nbCards] = newCard;
			nbCards++;
		}
	}

	return cards;
}
