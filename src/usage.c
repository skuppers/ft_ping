#include "ft_ping.h"

void	print_usage(uint8_t exits)
{
		printf("Usage: ft_ping [-dDhqv] [-c count] [-i interval] [-I interface]\n"
				"\t[-s packetsize] [-Q tos] [-t TTL] <host>\n");
		if (exits != 0)
			exit(exits);
}

void	print_help(uint8_t exits)
{
	printf("Ft_ping:\n"
		"*	Possible options are:\n"
		"*	-c <number>     Send <number of packets and quit.\n"
 		"*	-d      	Set the SO_DEBUG flag on the socket.\n"
		"*	-I <interface>	Specify the interface to use.\n"
 		"*	-D		Print the timestamp.\n"
 		"*	-h		Show this page.\n"
 		"*	-Q <tos>        Set the type of service (ToS).\n"
 		"*	-i <number>	Specify send interval in seconds.\n"
 		"*	-q		Quiet output.\n"
 		"*	-v		Verbose	output.\n"
 		"*	-t <number>	Specify the Time to Live of packets.\n"
 		"*	-s <number>	Specify the packet size.\n\n");
	print_usage(exits);
}