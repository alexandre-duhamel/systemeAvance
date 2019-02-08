#include <stdio.h>
#include <string.h>

#include "socket.h"

#define BUFFER_LEN 10

int main (/*int argc , char **argv*/ ){

    /* creation des sockets server et client */
    int socket_server = creer_serveur(8080);

    while(1){
      int socket_client = accept (socket_server, NULL, NULL);

      if (socket_client == -1) {
        perror ("accept");
        /* traitement d ’ erreur */
      }
      /* On peut maintenant dialoguer avec le client */

      const char * message_bienvenue = "Bonjour, bienvenue sur mon serveur\n" ;
      for (int i = 0; i < 10; i++) {
	//sleep(1);
      	write(socket_client, message_bienvenue, strlen(message_bienvenue));
      }
      char buffer[BUFFER_LEN];
      int ret;
      while( (ret = read(socket_client, buffer, BUFFER_LEN)) > 0){
        write(socket_client, buffer, ret);
      }
      fprintf(stdout, "client deconnecte\n");
      close(socket_client);
    }
}
