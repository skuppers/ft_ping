# include "ft_ping.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define DATASIZE 1472 		// bytes? so x8
# define HOSTNAME 0 		/* LOCALHOST */
# define PORTNAME "1337" // Got no fucking idea

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

int main (int ac, char **av)
{

		/* CLIENT SOCKET ADDRESS CONFIGURATION */

		// Holds info about something
		//		struct addrinfo hints;
		//		struct addrinfo *res = 0;

		//		memset(&hints, 0, sizeof(hints));
		//		hints.ai_family = AF_INET;
		//		hints.ai_socktype = SOCK_RAW;
		//		hints.ai_protocol = IPPROTO_ICMP;
		//		hints.ai_flags = AI_ADDRCONFIG;

		//		int error = 0;
		//		if ((error = getaddrinfo(HOSTNAME, NULL, &hints, &res)) != 0)
		//		{
		//				printf("Error with getaddrinfo().\n");
		//				exit(42);
		//		}\

		int 					clientSocket;
		char 					*ip_addr, *hostname;

		struct sockaddr_in		address;
		int						address_len;

		typedef struct icmp_packet
		{
				struct icmphdr header;
				char msg[64 - sizeof(struct icmphdr)];
		}				icmp_pkt;

		clientSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
		if (clientSocket == -1) {
				printf("Error creating socket. Are you root?\n");
				exit(42);
		}

		int ip_ttl = 64;

		setsockopt(clientSocket, SOL_IP, IP_TTL, ip_ttl, sizeof(ip_ttl));
		//		setsockopt(clientSocket, SOL_IP, SO_RCVTIMEO, , sizeof());

		icmp_pkt pkt;
		memset(&pkt, 0, sizeof(pkt));
		pkt.header.type = ICMP_ECHO;
		pkt.header.un.echo.id = getpid();
		int i = 0;
		for (i = 0; i < sizeof(pkt.msg); i++)
				pkt.msg[i] = i + '0';
		pkt.msg[i] = 0;
		pkt.header.un.echo.sequence = 1;
		pkt.header.checksum = 0;


		//		struct sockaddr_in addr;
		//		memset(&addr, 0, sizeof(addr));
		//		addr.sin_family = AF_INET;
		//		addr.sin_addr = ;
		//		inet_aton("127.0.0.1", &address.sin_addr.s_addr);

		/*		const size_t req_size = 8;
				struct icmphdr req;
				req.type = 8;
				req.code = 0;
				req.checksum = 0;
				req.un.echo.id = htons(1);
				req.un.echo.sequence = htons(3);
				req.checksum = ip_checksum(&req, req_size);*/

		struct addrinfo hints;
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_RAW;
		hints.ai_protocol = IPPROTO_ICMP;
		hints.ai_flags = AI_ADDRCONFIG;

		struct addrinfo *res = 0;

		int error = 0;
		if ((error = getaddrinfo(HOSTNAME, PORTNAME, &hints, &res)) != 0)
		{
			printf("Error with getaddrinfo().\n");
			exit(42);
		}

		if ( sendto(clientSocket, &pkt, sizeof(pkt), 0,
							res->ai_addr, res->ai_addrlen) == -1 ) {
				printf("Error sending datagram.\n");
				exit(42);
		}
		printf("Successfully sent datagram! Yay!\n");
}
