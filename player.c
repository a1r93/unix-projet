/*
* server.c
* ROCHEZ Arnaud et PIRARD Delanoe
*
*/

#include "player.h"

message msgRecv, msgSend;
int port, sck;
struct sockaddr_in addr;
struct hostent* host;

int main(int argc, char const *argv[]) {
    // signal(SIGPIPE, err_handler);
    // signal(SIGINT, int_handler);

    if (argc != 3) {
        fprintf(stderr, "Usage: %s host port\n", argv[0]);
        exit(-1);
    }

    port = atoi(argv[2]);
    sck = createSocket();
    host = gethostbyname(argv[1]);
    
    if (host == NULL) {
        fprintf(stderr, "Hôte inconnu\n");
        exit(-1);
    }

    connectSocketPlayer(sck, addr, host, port);
    fprintf(stderr, "Player connected successfully to the server\n");
    
    fprintf(stdout, "Veuillez entrer votre pseudo (max 25 charactères)\n");
    fgets(ibuf, BUFSIZE, stdin);
    
    while (strlen(ibuf) > 25) {
        perror("Le pseudo choisi est trop long !");
        fprintf(stdout, "Veuillez entrer votre pseudo (max 25 charactères)\n");
        fgets(ibuf, BUFSIZE, stdin);
    }
    
    msgSend.typeMsg = CONNECTION;
    strcpy(msgSend.text, ibuf);
    sendMessage(sck, &msgSend);
    recvMessage(sck, &msgRecv);

    if (msgRecv.typeMsg == CONNECTION && strcmp(msgRecv.text, "OK") == 0) {
        fprintf(stdout, "Vous êtes bien inscrit à la partie\n");
    } else {
        fprintf(stderr, "Erreur: nombre de joueurs max à été atteint\n");
        close(sck);
        exit(-1);
    }

    while(1) {
        if (recvMessage(sck, &msgRecv) <= 0) {
            perror("La connection avec le serveur à été perdue");
            close(sck);
            exit(-1);
        }

        if (msgRecv.typeMsg == TEST) {
            msgSend.typeMsg = TEST;
            strcpy(msgSend.text, "test");
            sendMessage(sck, &msgSend);
        }

        // The game started
        if (msgRecv.typeMsg == GAME) {
            fprintf(stdout, "Vous pouvez voir vos cartes, voulez-vous les voir? (O/N)\n");
            fgets(ibuf, BUFSIZE, stdin);
            if (strcmp(ibuf, "O")) {
                // printCards(this???);
                // Je pense qu'il faut accéder à la shared memory ici pour choper les cartes du joueur
            }
        }
    }
}

void err_handler(int unused){   
 	fprintf(stderr,"Connection lost!\n");
  	close(sck);
  	exit(1);
}

void int_handler(int unused) {
	fprintf(stderr,"Connection lost!\n");
	close(sck);
  	exit(1);
}
