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

void	plot_stats(t_runtime *rt)
{
	for (t_list *slst = rt->spacketlist_head; slst != NULL; slst = slst->next)
	{
		for (t_list *rlst = rt->rpacketlist_head; rlst != NULL; rlst = rlst->next)
		{
			if (rlst->data == NULL)
			{
				//lst = lst->nest;
				continue;
			}
		//	t_packetlist *pkt = (t_packetlist*)slst->data;
	//		uint16_t seq = ((struct icmpv4_hdr *)pkt->data + ICMP_HDRLEN)->icmp_sequence;
			


		//	t_packetlist *pkt = (t_packetlist*)rlst->data;
	//		uint16_t seq = ((struct icmpv4_hdr *)pkt->data + ICMP_HDRLEN)->icmp_sequence;

			//printf("icmp sequence");
		}
	}

}

/*
void		update_statistics(t_data *param, t_timer *timer)
{
	if (param->rtt_min == 0 || timer->rtt_sec < param->rtt_min)
		param->rtt_min = timer->rtt_sec;
	if (param->rtt_max == 0 || timer->rtt_sec > param->rtt_max)
		param->rtt_max = timer->rtt_sec;
	param->rtt_avg += (float)timer->rtt_sec;
}

void		clear_timer(t_timer *timer)
{
	timer->send_sec = 0;
	timer->recv_sec = 0;
	timer->rtt_sec = 0;
}

void		start_timer(t_timer *t)
{
	struct timeval	start;

	if (gettimeofday(&start, NULL) != 0)
	{
		printf("Fatal error getting time.\n");
		exit(42);
	}
	t->send_sec = start.tv_sec + (double)(0.001f * (double)start.tv_usec);
}

void		stop_timer(t_timer *t)
{
	struct timeval	stop;

	if (gettimeofday(&stop, NULL) != 0)
	{
		printf("Fatal error getting time.\n");
		exit(42);
	}
	t->recv_sec = stop.tv_sec + (double)(0.001f * (double)stop.tv_usec);
	t->rtt_sec = (double)(t->recv_sec - t->send_sec);
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
			g_param->sigint == 0)
	{
		if (gettimeofday(&tv_current, NULL) < 0)
		    printf(" --- Fatal Error - Kernel Panic ---\n");
	}
}
*/