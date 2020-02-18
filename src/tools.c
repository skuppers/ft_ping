/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:17:44 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:45:25 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

void	extract_ipaddr(const struct sockaddr *sa, char *ip, uint32_t maxlen)
{
	if (sa->sa_family == AF_INET)
		inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr), ip,
			maxlen);
	else if (sa->sa_family == AF_INET6)
		inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr), ip,
			maxlen);
	else
	{
		ping_fatal("extract_ipaddr()","Unknown AF");
		exit(42);
	}
}

void		ping_timer(int interval)
{
	struct timeval tv_current;
	struct timeval tv_next;

	if (gettimeofday(&tv_current, NULL) < 0)
	        printf(" --- Fatal Error - Kernel Panic ---\n");
	tv_next = tv_current;
	tv_next.tv_sec += interval;
	while ((tv_current.tv_sec < tv_next.tv_sec ||
			tv_current.tv_usec < tv_next.tv_usec) &&
			g_signals->sigint == 0)
	{
		if (gettimeofday(&tv_current, NULL) < 0)
		    printf(" --- Fatal Error - Kernel Panic ---\n");
	}
}

float	plot_timer(t_timer *timer)
{
	double	send = 0;
	double	recv = 0;

	send = ((double)timer->send.tv_sec) + ((double)(0.000001f*(double)timer->send.tv_usec));
	recv =  ((double)timer->recv.tv_sec) + ((double)(0.000001f * (double)timer->recv.tv_usec));
	return ((float)(recv - send) * 1000.0f);
}

uint32_t	list_received(t_list *list_header)
{
	uint32_t	len;
	t_list		*listhdr;

	len = 0;
	listhdr = list_header;
	while (listhdr != NULL)
	{
		if (listhdr->data != NULL)
			len++;
		listhdr = listhdr->next;
	}
	return (len);
}

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
			dev = (float)((((t_packetlist *)ptr->data)->rtt) - stats->rtt_avg);
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
			if (stats->rtt_min == 0 || ((t_packetlist *)ptr->data)->rtt < stats->rtt_min)
				stats->rtt_min = ((t_packetlist *)ptr->data)->rtt;
			if (stats->rtt_max == 0 || ((t_packetlist *)ptr->data)->rtt > stats->rtt_max)
				stats->rtt_max = ((t_packetlist *)ptr->data)->rtt;
			stats->rtt_avg += (float)(((t_packetlist *)ptr->data)->rtt);
		}
		ptr = ptr->next;
	}
	stats->rtt_avg = stats->rtt_avg / stats->pkt_recvd;
	get_stddev(rt, stats);
}