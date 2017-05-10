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
    int gameStarted = 0;

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
        FD_ZERO(&fdset);
        int ret, i;
        FD_SET(sck, &fdset);
        
        if ((ret = select(sck + 1, &fdset, NULL, NULL, &tv)) < 0) {
            perror("Erreur du select");
            exit(1);
        }

        if (ret > 0) {
            fprintf(stderr, "Ajout joueur\n");
            if (FD_ISSET(sck, &fdset)) {
                if (gameStarted == 0) {
                    int sck2 = acceptSocketPlayer(sck);

                    fprintf(stderr, "socket 2: %d\n", sck2);
                    if (sck2 < 1) {
                        perror("Erreur d'acceptation du socket");
                    } else {
                        recvMessage(sck2, &msg);

                        if (msg.typeMsg == CONNECTION) {
                            if (gameServ.nbplayers < MAX_PLAYERS) {
                                subcribePlayer(msg.text, sck2, &gameServ);
                                msg.typeMsg = CONNECTION;
                                strcpy(msg.text, "OK");
                                sendMessage(sck2, &msg);
                                int ret2 = close(sck2);
                        
                                if(gameServ.nbplayers == 1) {
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

                for(i = 0; i < gameServ.nbplayers; i++) {
                    msg.typeMsg = TEST;
                    strcpy(msg.text, "test");
                    fprintf(stderr, "%d\n", gameServ.players[i].sck);
                    sendMessage(gameServ.players[i].sck, &msg);
                    if(recvMessage(gameServ.players[i].sck, &msg) > 0) {
                        temp.players[temp.nbplayers] = gameServ.players[i];
                        temp.nbplayers++;
                        fprintf(stderr, "%s\n", msg.text);
                    } else {
                        fprintf(stderr, "Connection perdue avec le joueur %s\n", gameServ.players[i].nickname);
                        close(gameServ.players[i].sck);
                    }
                }

                for (i = 0; i < temp.nbplayers; i++) {
                    gameServ.players[i] = temp.players[i];
                }
                gameServ.nbplayers = temp.nbplayers;

                if(gameServ.nbplayers > 1) {
                    gameStarted = 1;
                    perror("Partie démarrée");
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
