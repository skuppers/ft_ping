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

void					print_unreachable(t_data *param,
							uint8_t *pkt, uint8_t code, uint16_t seq)
{
	char				src[16];
	struct s_ipv4_hdr	*ip;

	ft_bzero(src, 16);
	ip = (struct s_ipv4_hdr *)pkt;
	inet_ntop(AF_INET, &ip->ip_src, src, 16);
	dprintf(2, "From ");
	print_reverse(param, src);
	dprintf(2, "icmp_seq=%u ", seq);
	if (code == 0)
		dprintf(2, "Destination network unreachable\n");
	else if (code == 1)
		dprintf(2, "Destination host unreachable\n");
	else
		dprintf(2, "Destination unreachable\n");
}

void					print_unknown(t_data *param, uint8_t *pkt,
							uint16_t sequence)
{
	char				src[16];
	struct s_ipv4_hdr	*ip;
	struct s_icmpv4_hdr	*icmp;

	ft_bzero(src, 16);
	ip = (struct s_ipv4_hdr *)pkt;
	icmp = (struct s_icmpv4_hdr *)(pkt + IP4_HDRLEN);
	inet_ntop(AF_INET, &ip->ip_src, src, 16);
	dprintf(2, "From ");
	print_reverse(param, src);
	dprintf(2, "icmp_seq=%u Unknown error: type:%u code:%u\n",
		sequence,
		icmp->icmp_type,
		icmp->icmp_code);
}

void					print_ttl_exceeded(t_data *param, uint8_t *pkt,
							uint16_t sequence)
{
	char				src[16];
	struct s_ipv4_hdr	*ip;

	ft_bzero(src, 16);
	ip = (struct s_ipv4_hdr *)pkt;
	inet_ntop(AF_INET, &ip->ip_src, src, 16);
	dprintf(2, "From ");
	print_reverse(param, src);
	dprintf(2, "icmp_seq=%u Time to live exceeded\n",
		sequence);
}

void					print_ping(t_data *param, uint8_t *pkt, t_meta *mt)
{
	char				src[16];
	struct s_ipv4_hdr	*ip;
	float				ff;

	ip = (struct s_ipv4_hdr *)pkt;
	inet_ntop(AF_INET, &ip->ip_src, src, 16);
	print_timestamp(param, mt->timer);
	dprintf(2, "%u bytes from ", mt->r_bts);
	print_reverse(param, src);
	ff = plot_timer(mt->timer);
	print_resolution(ff, mt->sequence, ip->ip_ttl);
}

void					print_stats(t_runtime *rt)
{
	t_stats				stats;

	ft_memset(&stats, 0, sizeof(t_stats));
	update_statistics(rt, &stats);
	dprintf(2, "\n--- %s ping statistics ---\n", rt->param->fqdn);
	dprintf(2, "%d packets transmitted, %d received,",
			stats.pkt_send,
			stats.pkt_recvd);
	if (stats.icmp_errors != 0)
		dprintf(2, " +%u errors,", stats.icmp_errors);
	dprintf(2, " %.2f%% packet loss\n",
		100 - ((double)stats.pkt_recvd / (double)stats.pkt_send * 100));
	if (stats.pkt_recvd > 0)
		dprintf(2, "rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
					stats.rtt_min,
					stats.rtt_avg,
					stats.rtt_max,
					stats.std_deviation);
	else
		dprintf(2, "\n");
	free_packetlist(rt->rpacketlist_head);
}
