#include "ft_ping.h"

void	ping_fatal(const char *failed_here, const char *errbuff)
{
	printf("Fatal error in %s: %s\n", failed_here, errbuff);
}