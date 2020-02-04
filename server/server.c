# include "ft_ping.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define DATASIZE 1472 		// bytes? so x8
# define HOSTNAME 0 		/* WILDCARD */
# define PORTNAME "daytime" // Got no fucking idea

int main (__unused int ac, __unused char **av)
{

/* LOCAL SOCKET ADDRESS CONFIGURATION */

	// Holds info about something
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = 0;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;

	struct addrinfo *res = 0;

	int error = 0;
	if ((error = getaddrinfo(HOSTNAME, PORTNAME, &hints, &res)) != 0)
	{
		printf("Error with getaddrinfo().\n");
		exit(42);
	}

/*   ---------------------------------- */

	// create socket
	int serverSocket = socket(res->ai_family, res->ai_socktype,
					res->ai_protocol);
	if (serverSocket == -1) {
			printf("Error creating socket.\n");
			exit(42);
	}

/* Bind the socket to a local address (Only needed for server-side listening) */

	if (bind(serverSocket, res->ai_addr, res->ai_addrlen) == -1) {
		printf("Error binding socket!\n");
		exit(42);
	}

/* Release memory created by getaddrinfo */
	freeaddrinfo(res);


/* HANDLING INCOMING DATAGRAMS */

// Holds all the info about our socket
//	struct sockaddr_in sockin;
//	sockin.sin_family = ;
//	sockin.sin_port = ;
//	sockin.sin_addr = ;

	// Data buffer for datagrams
	char data_buffer[DATASIZE];

	// General structure to store address
	struct sockaddr_storage src_addr;

	// Data storage vector
	struct iovec iov[1];
	iov[0].iov_base = data_buffer;
	iov[0].iov_len = sizeof(data_buffer);

	// Message Header -> where to store received datagram infos
	struct msghdr message;
	message.msg_name = &src_addr;
	message.msg_namelen = sizeof(src_addr);
	message.msg_iov = iov;
	message.msg_iovlen = 1;
	message.msg_control = 0;
	message.msg_controllen = 0;

	printf("Now listening to incoming datagrams...\n");
	ssize_t count = recvmsg(serverSocket, &message, 0);
	if (count == -1) {
			printf("Error w/ recvmsg().\n");
	} else if (message.msg_flags & MSG_TRUNC) {
			printf("Message truncated.\n");
	} else {
			printf("Received datagram.\n");
	}
	close(serverSocket);
	exit(0);
}
