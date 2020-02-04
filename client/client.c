# include "ft_ping.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define DATASIZE 1472 		// bytes? so x8
# define HOSTNAME 0 		/* LOCALHOST */
# define PORTNAME "1337" // Got no fucking idea

uint16_t	ip_checksum(void *b, size_t len)
{
		unsigned short *buf = b; // for 16 bit casting
		unsigned int sum = 0;    // 1's over sum
		uint16_t result;   // checksum

		for ( sum = 0; len > 1; len -= 2 )
				sum += *buf++;

		if ( len == 1 )
				sum += *(unsigned char*)buf;

		sum = (sum >> 16) + (sum & 0xFFFF);
		sum += (sum >> 16);

		result = ~sum;
		return result;
}

int main (int ac, char **av)
{

		/* CLIENT SOCKET ADDRESS CONFIGURATION */
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

		int ip_ttl = 42;

		setsockopt(clientSocket, SOL_IP, IP_TTL, &ip_ttl, sizeof(ip_ttl));
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
		pkt.header.checksum = ip_checksum(&pkt, sizeof(pkt));


		struct addrinfo hints;
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = 0;
		hints.ai_protocol = 0;
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
