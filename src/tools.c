/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:17:44 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:45:25 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void				print_resolve(t_data *param)
{
	char	*host;

	if (ft_strequ(param->fqdn, "0.0.0.0") != 0)
		host = "127.0.0.1";
	else
		host = param->ipv4_str;
	dprintf(2, "PING %s (%s) %d(%d) bytes of data.\n", param->fqdn,
		host, param->pkt_size,
		param->pkt_size + IP4_HDRLEN + ICMP_HDRLEN);
}

void				extract_ipaddr(const struct sockaddr *sa, char *ip,
						uint32_t maxlen)
{
	if (sa->sa_family == AF_INET)
		inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr), ip,
			maxlen);
	else if (sa->sa_family == AF_INET6)
		inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr), ip,
			maxlen);
	else
	{
		ping_fatal("extract_ipaddr()", "Unknown AF");
		exit(42);
	}
}

void				register_response(t_runtime *runtime, uint8_t *packet,
							ssize_t size, t_timer *timer)
{
	t_list			*data;
	t_packetdata	*packetdata;

	if (packet != NULL && size > 0)
	{
		packetdata = pktdatanew(packet, (size_t)size, timer);
		data = ft_lstnew(packetdata, sizeof(t_packetdata));
		free(packetdata);
	}
	else
		data = ft_lstnew(NULL, 0);
	if (runtime->rpacketlist_head == NULL)
		runtime->rpacketlist_head = data;
	else
		ft_lstadd(&runtime->rpacketlist_head, data);
}

void				ping_timer(int interval)
{
	struct timeval	tv_current;
	struct timeval	tv_next;

	if (gettimeofday(&tv_current, NULL) < 0)
		dprintf(2, " [Error retrieving time ] - ");
	tv_next = tv_current;
	tv_next.tv_sec += interval;
	while ((tv_current.tv_sec < tv_next.tv_sec ||
			tv_current.tv_usec < tv_next.tv_usec) &&
			g_signals->sigint == 0)
	{
		if (gettimeofday(&tv_current, NULL) < 0)
			dprintf(2, " [Error retrieving time ] - ");
	}
}

void				prep_meta(uint16_t seq, t_meta *pktmeta,
						t_timer *tm)
{
	pktmeta->r_bts = -1;
	pktmeta->sequence = seq;
	pktmeta->timer = tm;
}
