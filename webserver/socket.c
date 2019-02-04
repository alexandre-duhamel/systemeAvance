#ifndef __SOCKET_H__
#define __SOCKET_H__
#include <sys/types.h>
#include <sys/socket.h>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(param) close(param)


typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

typedef int socklen_t;

struct sockaddr_in {
    sa_family_t sin_family ; /* address family : AF_INET */
    in_port_t sin_port ;
    /* port in network byte order */
    struct in_addr sin_addr ;
    /* internet address */
};

/* Internet address . */
struct in_addr {
    uint32_t s_addr ;
};


int creer_serveur(int port);


int creer_serveur(int port) {
	int socket_server;
	socket_server = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_server == -1)
	{
		perror("socket_serveur");
	}
	struct sockaddr_in;
	
	bind(socket_server, socket_server&, 200);
	listen();

}

#define closesocket(param) close(param)
