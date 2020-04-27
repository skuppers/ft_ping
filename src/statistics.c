/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:53:48 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 18:04:58 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

float		plot_timer(t_timer *timer)
{
	double	send;
	double	recv;

	send = ((double)timer->send.tv_sec)
		+ ((double)(0.000001f * (double)timer->send.tv_usec));
	recv = ((double)timer->recv.tv_sec)
		+ ((double)(0.000001f * (double)timer->recv.tv_usec));
	return ((float)(recv - send) * 1000.0f);
}

static void	get_stddev(t_runtime *rt, t_stats *s)
{
	t_list	*ptr;
	float	dev;

	ptr = rt->rpacketlist_head;
	while (ptr != NULL)
	{
		if (ptr->data != NULL)
		{
			dev = (float)((((t_packetdata *)ptr->data)->rtt) - s->rtt_avg);
			if (dev < 0)
				dev = -dev;
			s->std_deviation += dev;
		}
		ptr = ptr->next;
	}
	s->std_deviation = (float)(s->std_deviation / s->pkt_recvd);
}

void		update_statistics(t_runtime *rt, t_stats *s)
{
	t_list	*p;

	p = rt->rpacketlist_head;
	s->pkt_send = ft_lstlen(p);
	s->pkt_recvd = list_received(p);
	while (p != NULL)
	{
		if (p->data_size != 0)
		{
			if (((t_packetdata*)p->data)->rtt == -42.0)
			{
				++(s->icmp_errors);
				p = p->next;
				continue;
			}
			if (s->rtt_min == 0 || ((t_packetdata *)p->data)->rtt < s->rtt_min)
				s->rtt_min = ((t_packetdata *)p->data)->rtt;
			if (s->rtt_max == 0 || ((t_packetdata *)p->data)->rtt > s->rtt_max)
				s->rtt_max = ((t_packetdata *)p->data)->rtt;
			s->rtt_avg += (float)(((t_packetdata *)p->data)->rtt);
		}
		p = p->next;
	}
	s->rtt_avg = s->rtt_avg / s->pkt_recvd;
	get_stddev(rt, s);
}
