# include "ft_ping.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define DATASIZE 1472 		// bytes? so x8
# define HOSTNAME 0 		/* LOCALHOST */
# define PORTNAME "daytime" // Got no fucking idea

uint16_t	ip_checksum(void *vdata, size_t length)
{
	//Cast data pointer for indexing
	char *data = (char*)vdata;

	//initialise accumulator
	uint32_t acc = 0xffff;

	// Handle 16bit blocks
	for (size_t i = 0; i + 1 < length; i += 2) {
		uint16_t word;
		memcpy(&word, data + i, 2);
		acc += ntohs(word);
		if (acc > 0xffff)
			acc -= 0xffff;
	}
	if (length & 1)
	{
		uint16_t word = 0;
		memcpy(&word, data + length - 1, 1);
		acc += ntohs(word);
		if (acc > 0xffff)
			acc -= 0xffff;
	}
	return (htons(~acc));
}

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
		req.un.echo.id = htons(0x1234);
		req.un.echo.sequence = htons(1);
		req.checksum = ip_checksum(&req, req_size);


		if ( sendto(clientSocket, req, req_size, 0,
					res->ai_addr, res->ai_addrlen) == -1 ) {
			printf("Error sending datagram.\n");
			exit(42);
		}
		printf("Successfully sent datagram! Yay!");
}
