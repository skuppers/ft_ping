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

//relook at this
uint32_t	list_received(t_list *list_header)
{
	uint32_t	len;
	t_list		*listhdr;

	len = 0;
	listhdr = list_header;
	while (listhdr != NULL)
	{
		if (listhdr->data != NULL && ((t_packetdata*)listhdr->data)->rtt != -42.0)
			len++;
		listhdr = listhdr->next;
	}
	return (len);
}