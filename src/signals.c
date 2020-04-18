#include "ft_ping.h"

void    sigint_handle(int signo)
{
	(void)signo;
    g_signals->sigint = 1;
}

void    sigalrm_handle(int signo)
{
	(void)signo;
    g_signals->sigalrm = 1;
}