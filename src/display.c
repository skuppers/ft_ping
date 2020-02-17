/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:05:02 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 15:44:40 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_resolve(t_data *param)
{
		printf("PING %s (%s): %d(%d) data bytes\n", param->fqdn, param->ipv4_str,
						param->pkt_size, param->pkt_size + IP4_HDRLEN + ICMP_HDRLEN);
}

void	print_ping(t_data *param, uint8_t *pkt)
{
	struct ipv4_hdr		*ip;
	struct icmpv4_hdr	*icmp;

	ip = (struct ipv4_hdr *)pkt;
	icmp = (struct icmpv4_hdr *)(pkt + sizeof(struct ipv4_hdr));
	char *src = ft_strnew(16);
	inet_ntop(AF_INET, &ip->ip_src, src, 16);
	if (param->options & OPT_TIMESTAMP)
			printf("[timestamp] ");
	printf("%u bytes from %s: icmp_seq=%u ttl=%d time=0.420ms\n",
					ntohs(ip->ip_len), src,
					ntohs(icmp->icmp_sequence),
					ip->ip_ttl);
}

/*
void	get_stddev(t_data *param)
{
	int		iterator;
	float	dev;

	dev = 0;
	iterator = 0;
	while (param->timings[iterator] != 0)
	{
		dev = (float)(param->timings[iterator] - param->rtt_avg);
		if (dev < 0)
				dev = -dev;
		param->std_deviation += dev;
		++iterator;
	}
	param->std_deviation = (float)(param->std_deviation / param->pkt_recvd);
}
*/
void	print_stats(t_runtime *rt)
{
	printf("\n--- %s ping statistics ---\n", rt->param->fqdn);

	printf("%ld packets transmitted, %ld received, %.2f%% packet loss\n",
			ft_lstlen(rt->spacketlist_head), ft_lstlen(rt->rpacketlist_head),
			(100 - ((double)(ft_lstlen(rt->spacketlist_head) / ft_lstlen(rt->rpacketlist_head)) * 100)));

//	param->rtt_avg = (param->rtt_avg / param->pkt_recvd);
//	get_stddev(param);
	printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",0.0,0.0,0.0,0.0);
				/*	param->rtt_min,
					param->rtt_avg,
					param->rtt_max,
					param->std_deviation); */
}