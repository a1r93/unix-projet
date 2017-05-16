/*
* server.c
* ROCHEZ Arnaud et PIRARD Delanoe
*
*/

#include "server.h"

FILE *fdReader;
message msg;
int port, sck, status;
struct sockaddr_in addr;
fd_set fdset;
int gameStarted = 0;

game* gameServ;

int nbmanches = 0;
int actualmanche = 0;

int main(int argc, char const *argv[]) {
    static struct timeval tv;
    tv.tv_sec = 30;
    tv.tv_usec = 0;

    int fdp[2];
    char output[257];

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s port [errorFile]\n", argv[0]);
        exit(-1);
    }

    if( argc == 3) {
		close(2);
		if (open(argv[2], O_RDWR | O_CREAT, 0644) < 0) {
			perror("Error: file opening.\n");
			exit(1);
		}
	}

    if(pipe(fdp) < 0) {
		perror("Error: pipe init\n");
		exit(1);
	}
	pid_t pid = fork();
	
	
	if(pid > 0) {
		close(fdp[1]);
		if((fdReader = fdopen(fdp[0], "r")) == NULL) {
		  perror("Error: fdopen");
		  exit(1);
		}
		wait(&status);
		if(WIFEXITED(status)) {
			fgets(output, 257, fdReader);
			int serveurCount = (atoi(output) - 1);
			if(serveurCount > 1) {
				perror("Only one server can be launched on that machine.\n");
				exit(1);
			}
		}
	} else if (pid == 0) {
		close(fdp[0]);
		if (dup2(fdp[1], 1) < 0) {
			perror("Error: duplication stdout.\n");	
		}
		system("ps -e | grep \"serveur\" | wc -l");
		exit(0);
	} else {
		perror("Error: fork.\n");
		exit(1);
	}	

    port = atoi(argv[1]);
    sck = createSocket();
    bindSocketServer(sck, addr, port);

    gameServ = createAttachShm(KEY);
    gameServ->nbplayers = 0;

    listen(sck,4);

    while(1) {
        FD_ZERO(&fdset);
        FD_SET(sck, &fdset);
        int ret, i;
        
        if ((ret = select(sck + 1, &fdset, NULL, NULL, &tv)) < 0) {
            perror("Error: select()\n");
            close(sck);
            detachShm(gameServ);
            destroyShm();
            exit(1);
        }

        if (ret > 0) {
            fprintf(stderr, "Add player\n");
            if (FD_ISSET(sck, &fdset)) {
                if (gameStarted == 0) {
                    int sck2 = acceptSocketPlayer(sck);

                    fprintf(stderr, "socket 2: %d\n", sck2);
                    if (sck2 < 1) {
                        perror("Erreur d'acceptation du socket");
                    } else {
                        recvMessage(sck2, &msg);

                        if (msg.typeMsg == CONNECTION) {
                            if (gameServ->nbplayers < MAX_PLAYERS) {
                                subcribePlayer(msg.text, sck2, gameServ);
                                msg.typeMsg = CONNECTION;
                                strcpy(msg.text, "OK");
                                sendMessage(sck2, &msg);
                                //int ret2 = close(sck2);
                        
                                if(gameServ->nbplayers == 1) {
                                    tv.tv_sec = 30;
                                    tv.tv_usec = 0;
                                }
                            } else {
                                perror("Nombre de joueurs maximum atteint");
                                msg.typeMsg = CONNECTION;
                                strcpy(msg.text, "KO");
                                sendMessage(sck2, &msg);
                                int ret2 = close(sck2);
                            }
                        }
                    }
                }
            }
        // 30 seconds passed AND ret <= 0 => means that noone subscribed
        } else {
            if (gameStarted == 0) {
                int i;
                game temp;
                temp.nbplayers = 0;

                for(i = 0; i < gameServ->nbplayers; i++) {
                    msg.typeMsg = TEST;
                    strcpy(msg.text, "test");
                    fprintf(stderr, "%d\n", gameServ->players[i].sck);
                    sendMessage(gameServ->players[i].sck, &msg);
                    if(recvMessage(gameServ->players[i].sck, &msg) > 0) {
                        temp.players[temp.nbplayers] = gameServ->players[i];
                        temp.nbplayers++;
                        fprintf(stderr, "%s\n", msg.text);
                    } else {
                        fprintf(stderr, "Lost connection with %s\n", gameServ->players[i].nickname);
                        close(gameServ->players[i].sck);
                    }
                }

                for (i = 0; i < temp.nbplayers; i++) {
                    gameServ->players[i] = temp.players[i];
                }
                gameServ->nbplayers = temp.nbplayers;

                if(gameServ->nbplayers > 1) {
                    gameStarted = 1;
                    msg.typeMsg = GAMESTART;
                    strcpy(msg.text, "Game started");
                    for(i = 0; i < gameServ->nbplayers; i++) {
                        sendMessage(gameServ->players[i].sck, &msg);
                    }

                    for (i = 0; i < 3; i++) {
                        startManche();
                    }
                    // regarde les points et annonce le vainqueur
                    // exit total de tout 
                } else {
                    tv.tv_sec = 30;
                    tv.tv_usec = 0;
                }
            }
        }
    }
    
    return 0;
}

int subcribePlayer(char* nickname, int sck, game* game) {
    player newPlayer;
    strcpy(newPlayer.nickname, nickname);
    newPlayer.score = 0;
    newPlayer.sck = sck;

    game->players[game->nbplayers] = newPlayer; 
    game->nbplayers++;
}

void startManche() {
    // reinitialiser takencards
    actualmanche++;
    fprintf(stderr, "Manche numéro %d\n", actualmanche);

    int nbCards, i, j;
    card* cards = getCards(&nbCards);
    int currentCard = 0;

    for (i = 0; i < nbCards/gameServ->nbplayers; i++) {
        for (j = 0; j < gameServ->nbplayers; j++) { 
            gameServ->players[j].cards[gameServ->players[j].nbcards] = cards[currentCard];
            currentCard++;
            gameServ->players[j].nbcards++;
        }
    }

    msg.typeMsg = GAME;
    strcpy(msg.text, "The cards have been distributed");
    for(i = 0; i < gameServ->nbplayers; i++) {
        sendMessage(gameServ->players[i].sck, &msg);
    }
    // Attendre les messages des joueurs pour confirmer que les 5 cartes ont bien été envoyées
    distributeCards(nbCards);

    // Demander aux joueurs de compter leurs cartes
    // scores a jour dans memoire partagée
}

void distributeCards(int nbCards) {
    // Choper les 5 cartes des joueurs
    // les donner à leurs voisin de gauche (Faudrait pas une liste chainée pour ça?)

    // while (nbCards > 0) {
    //     startTour(&nbCards);
    // }
}

void startTour(int* nbCards) {
    int i;
    msg.typeMsg = CHOOSE_CARD;
    strcpy(msg.text, "Choose a card to send please");
    for(i = 0; i < gameServ->nbplayers; i++) {
        sendMessage(gameServ->players[i].sck, &msg);

        // Attendre pour la réponse du joueur courant
        // mettre la carte dans la mémoire partagée
        
        msg.typeMsg = PLI;
        strcpy(msg.text, "The 'pli' can be consulted");
        sendMessage(gameServ->players[i+1].sck, &msg);

        // Coté player il regarde le pli via la mémoire partagée
    }

    // le joueur avec le plus grand chiffre reçoit toutes les cartes dans takencards
}

void int_handler(int unused) {  
	fprintf(stderr,"Lost connection\n");
	close(sck);
	detachShm(gameServ);
	destroyShm();
  	exit(1);
}
