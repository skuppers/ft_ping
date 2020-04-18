#include "ft_ping.h"

static void	get_stddev(t_runtime *rt, t_stats *stats)
{
	t_list	*ptr;
	float	dev;

	dev = 0;
	ptr = rt->rpacketlist_head;
	while (ptr != NULL)
	{
		if (ptr->data != NULL)
		{
			dev = (float)((((t_packetdata *)ptr->data)->rtt) - stats->rtt_avg);
			if (dev < 0)
				dev = -dev;
			stats->std_deviation += dev;
		}
		ptr = ptr->next;
	}
	stats->std_deviation = (float)(stats->std_deviation / stats->pkt_recvd);
}

void		update_statistics(t_runtime *rt, t_stats *stats)
{
	t_list	*ptr;

	ptr = rt->rpacketlist_head;
	stats->pkt_send = ft_lstlen(ptr);
	stats->pkt_recvd = list_received(ptr);
	while (ptr != NULL)
	{
		if (ptr->data_size != 0)
		{
			if (((t_packetdata*)ptr->data)->rtt == -42.0)
			{
				++(stats->icmp_errors);
				ptr = ptr->next;
				continue;
			}
			if (stats->rtt_min == 0 || ((t_packetdata *)ptr->data)->rtt < stats->rtt_min)
				stats->rtt_min = ((t_packetdata *)ptr->data)->rtt;
			if (stats->rtt_max == 0 || ((t_packetdata *)ptr->data)->rtt > stats->rtt_max)
				stats->rtt_max = ((t_packetdata *)ptr->data)->rtt;
			stats->rtt_avg += (float)(((t_packetdata *)ptr->data)->rtt);
		}
		ptr = ptr->next;
	}
	stats->rtt_avg = stats->rtt_avg / stats->pkt_recvd;
	get_stddev(rt, stats);
}