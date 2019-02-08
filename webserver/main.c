#include <stdio.h>
#include <string.h>

#include "socket.h"

int main (/*int argc , char **argv*/ ){

    /* creation des sockets server et client */
    int socket_server = creer_serveur(8080);
    int socket_client = accept (socket_server, NULL, NULL);

    if (socket_client == -1) {
      perror ("accept");
      /* traitement d ’ erreur */
    }
    /* On peut maintenant dialoguer avec le client */
    const char * message_bienvenue = "Bonjour, bienvenue sur mon serveur\n" ;
    write(socket_client, message_bienvenue, strlen(message_bienvenue));

  }
