# include "ft_ping.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define DATASIZE 1472 		// bytes? so x8
# define HOSTNAME 0 		/* LOCALHOST */
# define PORTNAME "daytime" // Got no fucking idea

int main (__unused int ac, __unused char **av)
{

		/* CLIENT SOCKET ADDRESS CONFIGURATION */

		// Holds info about something
		struct addrinfo hints;
		struct addrinfo *res = 0;

		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_protocol = 0;
		hints.ai_flags = AI_ADDRCONFIG;

		int error = 0;
		if ((error = getaddrinfo(HOSTNAME, PORTNAME, &hints, &res)) != 0)
		{
				printf("Error with getaddrinfo().\n");
				exit(42);
		}

		int clientSocket = socket(res->ai_family, res->ai_socktype,
						res->ai_protocol);
		if (clientSocket == -1) {
				printf("Error creating socket.\n");
				exit(42);
		}


		const size_t req_size = 8;
		struct icmphdr req;
		req.type = 8;
		req.code = 0;
		req.checksum = 0;
		req.un.echo.id = htons(rand());
		req.un.echo.sequence = htons(1);
//		req.checksum = ip_checksum(&req, req_size);


//		if ( sendto(clientSocket, , sizeof(), 0,
//					res->ai_addr, res->ai_addrlen) == -1 ) {
//			printf("Error sending datagram.\n");
//			exit(42);
//		}
}
