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

void	print_timeout(t_runtime *rt, uint8_t *packet)
{
	(void)packet;
	(void)rt;
	printf("Timeout\n");
}

void	print_ping(t_data *param, uint8_t *pkt, t_timer *tm)
{
	char				*src;
	struct ipv4_hdr		*ip;
	struct icmpv4_hdr	*icmp;
	struct hostent 		*hostdns;

	ip = (struct ipv4_hdr *)pkt;
	icmp = (struct icmpv4_hdr *)(pkt + sizeof(struct ipv4_hdr));
	src = ft_strnew(16);
	inet_ntop(AF_INET, &ip->ip_src, src, 16);
	hostdns = gethostbyaddr(&(param->sin->sin_addr), sizeof(param->sin->sin_addr), AF_INET);

	if (param->options & OPT_TIMESTAMP)
	{
			printf("[%f] ", (double)tm->recv.tv_sec +(double)(0.001f * (double)tm->recv.tv_usec));
	}
	printf("%u bytes from %s(%s): icmp_seq=%u ttl=%d time=%.3fms\n",
					ntohs(ip->ip_len),
					(hostdns == NULL) ? src : hostdns->h_name,
					src,
					ntohs(icmp->icmp_sequence),
					ip->ip_ttl,
					plot_timer(tm));
}

void	print_stats(t_runtime *rt)
{
	t_stats		stats;

	ft_memset(&stats, 0, sizeof(t_stats));
	update_statistics(rt, &stats);
	printf("\n--- %s ping statistics ---\n", rt->param->fqdn);
	printf("%d packets transmitted, %d received, %.2f%% packet loss\n",
			stats.pkt_send,
			stats.pkt_recvd,
			100 - ((double)stats.pkt_recvd / (double)stats.pkt_send * 100));
	printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
					stats.rtt_min,
					stats.rtt_avg,
					stats.rtt_max,
					stats.std_deviation);
}