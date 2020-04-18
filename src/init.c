#include "ft_ping.h"

void	init_param(t_data *param)
{
		memset(param, 0, sizeof(struct s_data));
		param->ttl = 255;
		param->interval = 1.0;
		param->pkt_size = 36;
}

void	init_signals(t_signals *signals)
{
	memset(signals, 0, sizeof(struct s_signals));
	g_signals = signals;
	signal(SIGALRM, &sigalrm_handle);
	signal(SIGINT, &sigint_handle);
}