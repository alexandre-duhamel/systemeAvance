#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <regex.h>

#include "socket.h"

#define BUF 160

//il faut gerer une infinite de fils morts (option = WNOHANG)
void mon_handler(int signal) {
	printf("signal %d recu\n", signal);
	while(waitpid(-1, NULL, WNOHANG) > 0) {}
}


/* Permet d'ignorer le signal d'erreur si le client se déconnecte avant la fin du 
write */
void initialiser_signaux() {
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        perror("Signal");
		exit(1);
    }
	struct sigaction sa;
	sa.sa_handler = mon_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("erreur sigaction\n");
		exit(1);
	}
}

/* Lit le ficher welcome et le transmet au client, prend la socket client en 
paramètre, et retourne 0 si l'opération c'est passée, sinon -1*/
int bienvenue(int socket_client) {
    int fileDescriptor = open("welcome.txt", O_RDONLY);
 	char buffer[160] = {0};

    // On vérifie que le fichier est correctement ouvert
    if (fileDescriptor == -1) {
        perror("Ouverture du fichier");
        return -1;
    }

    // On lit tant que le fichier n'est pas vide
    while (read(fileDescriptor, buffer, 79) != -1) {
		printf("%d", socket_client);
        //write(socket_client, buffer, strlen(buffer));
        // On vide le buffer
        memset(buffer, 0, 160);
    }
	
    // On ferme le fichier
    close(fileDescriptor);
    return 0;
}

/* Même chose que bienvenue(), sauf qu'elle lit le fichier ligne et le retourne 
au client par un nombre de d'appels à la fonction write équivalent au nombre de 
lignes.
De plus elle intègre un délais d'une seconde */
int bienvenueWithDelay(const int socket_client) {
    sleep(1);

    FILE* fichier = fopen("welcome.txt", "r");
    char* ligne = NULL;
    size_t tailleLigne = 0;

    // On vérifie que le fichier est correctement ouvert
    if (fichier == NULL) {
        perror("Ouverture du fichier");
        return -1;
    }
    
    // On lit le fichier ligne par ligne avec getline
    while(getline(&ligne, &tailleLigne, fichier) != -1) {
        printf("%s", ligne);
        write(socket_client, ligne, tailleLigne);
		printf("%d", socket_client);
        // On réinitialise la ligne à null
        ligne = NULL;    
    }
    // On ferme le fichier
    fclose(fichier);
    return 0;
}


//return 0 pour page existe pas dans l'arborescence locale, 1 pour page existe
int trouvePage(const char * buffer) {
	//printf(buffer);
	//char* nomRessource = "";
	//int reti = regcomp(buffer, "GET /* HTTP/1.1", 0);
	//if (!reti) {
	//	write(socket_client, "pas bon format", 14);
	//	return 0;
	//}
	//int parse_ http_request ( const char * request_line , http_request * request );
	return 1;
}

void lectureDeLaRequete(const int socket_client) {
	char buffer[160] = {0};

	FILE * a = fdopen ( socket_client , "w+" );
	if (a == NULL) {
		printf(" a est nul\n");
	}
	fgets(buffer, 160, a);
	int egaux = strcmp("GET / HTTP/1.1\r\n", buffer);
	/*if(egaux != 0){
		char* response = "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\r\n400 Bad request\r\n";
		write(socket_client, response, strlen(response));
		exit(1);
	}
	else */if (! trouvePage(socket_client, buffer)) {
		char* response = "HTTP/1.1 404 Not Found\r\nConnection: close\r\nContent-Length: 15\r\n\r\n404 Not Found\r\n";
		write(socket_client, response, strlen(response));
		exit(1);
	}
	else {
		char* response = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: 8\r\n\r\n200 OK\r\n";
		write(socket_client, response, strlen(response));
	}
}

int main() {
    initialiser_signaux();
    int socket_server = creer_serveur(8080);
    int socket_client;
    //int pid;
	pid_t pid;
	

    while (1) {
        socket_client = accept(socket_server, NULL, NULL);
 		if (socket_client == -1) {
                perror("accept");
				exit(1);
            }
        // On créer un nouveau processus
        pid = fork();
        // On est dans le processus fils
        if (pid == 0) {
            // On appelle la fonction bienvenue
            //bienvenueWithDelay(socket_client);
			
			
			lectureDeLaRequete(socket_client);
			exit(1);

        // Une erreur c'est produite
        } else if (pid == -1) {
            perror("echec de la creation du processus");
        // On est dans le processus père
        } else {
            // On ferme la socket_client
            close(socket_client);
        }
    }
}
