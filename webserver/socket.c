#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>

int creer_serveur(int port) {
    int socket_server;
    struct sockaddr_in socketAddr;

    // paramètrage de la structure socketAddr
    socketAddr.sin_family = AF_INET;
    socketAddr.sin_port = htons (8080);
    socketAddr.sin_addr.s_addr = INADDR_ANY;

    // création de la socket serveur 
    socket_server = socket(AF_INET, SOCK_STREAM, 0);
    // Vérification du bon déroullement de sa création
    if (socket_server == -1) {
        perror("socket_serveur");
    }

    // Attachement de la socket à une interface réseau et paramètrage
    if (bind(socket_server, (struct sockaddr *)&socketAddr, sizeof(socketAddr)) == -1) {
        perror("bind socket_serveur");
    }

    // démarrer l'attente de connexions
    if (listen(socket_server, 10) == -1) {
        perror("listen socket_serveur");
    }
}


