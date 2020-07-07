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
							uint8_t *pkt, uint8_t code, uint16_t sequence)
{
	char				src[16];
	struct s_ipv4_hdr	*ip;
	char				*node;

	ft_bzero(src, 16);
	ip = (struct s_ipv4_hdr *)pkt;
	inet_ntop(AF_INET, &ip->ip_src, src, 16);
	node = reverse_target(src);
	if (param->options & OPT_NUMERIC)
		printf("From %s: ", src);
	else
		printf("From %s (%s): ", (node == NULL) ? src : node, src);
	printf("icmp_seq=%u ", sequence);
	if (code == 0)
		printf("Destination network unreachable\n");
	else if (code == 1)
		printf("Destination host unreachable\n");
	else
		printf("Destination unreachable\n");
	ft_strdel(&node);
}

void					print_unknown(t_data *param, uint8_t *pkt,
							uint16_t sequence)
{
	char				src[16];
	struct s_ipv4_hdr	*ip;
	struct s_icmpv4_hdr	*icmp;
	char				*node;

	ft_bzero(src, 16);
	ip = (struct s_ipv4_hdr *)pkt;
	icmp = (struct s_icmpv4_hdr *)(pkt + IP4_HDRLEN);
	inet_ntop(AF_INET, &ip->ip_src, src, 16);
	node = reverse_target(src);
	if (param->options & OPT_NUMERIC)
		printf("From %s: ", src);
	else
		printf("From %s (%s): ", (node == NULL) ? src : node, src);
	printf("icmp_seq=%u Unknown error: type:%u code:%u\n",
		sequence,
		icmp->icmp_type,
		icmp->icmp_code);
	ft_strdel(&node);
}

void					print_ttl_exceeded(t_data *param, uint8_t *pkt,
							uint16_t sequence)
{
	char				src[16];
	struct s_ipv4_hdr	*ip;
	char				*node;

	ft_bzero(src, 16);
	ip = (struct s_ipv4_hdr *)pkt;
	inet_ntop(AF_INET, &ip->ip_src, src, 16);
	node = reverse_target(src);
	if (param->options & OPT_NUMERIC)
		printf("From %s: ", src);
	else
		printf("From %s (%s): ", (node == NULL) ? src : node, src);
	printf("icmp_seq=%u Time to live exceeded\n",
		sequence);
	ft_strdel(&node);
}

void					print_ping(t_data *param, uint8_t *pkt, t_timer *tm,
										uint16_t sequence)
{
	char				src[16];
	struct s_ipv4_hdr	*ip;
	char				*hostdns;
	float				ff;

	ip = (struct s_ipv4_hdr *)pkt;
	inet_ntop(AF_INET, &ip->ip_src, src, 16);

	hostdns = NULL;
	if (!(param->options & OPT_NUMERIC))
		hostdns = reverse_target(src);
	
//	dprintf(2, "hostname is %s\n", hostdns);

/*	char *ips = ft_strnew(256);
	extract_ipaddr((struct sockaddr*)param->sin, ips, 256);
	dprintf(2, "IP is: %s\n", ips);
*/
	if (param->options & OPT_TIMESTAMP)
		dprintf(2, "[%f] ", (double)tm->recv.tv_sec
			+ (double)(0.001f * (double)tm->recv.tv_usec));
	dprintf(2, "%u bytes from ", ntohs(ip->ip_len) - IP4_HDRLEN);
	if (param->options & OPT_NUMERIC)
		dprintf(2, "%s: ", src);
	else
		dprintf(2, "%s (%s): ", (hostdns == NULL) ? src : hostdns, src);
	ff = plot_timer(tm);
	print_resolution(ff, sequence, ip->ip_ttl);
	ft_strdel(&hostdns);
}

void					print_stats(t_runtime *rt)
{
	t_stats				stats;

	ft_memset(&stats, 0, sizeof(t_stats));
	update_statistics(rt, &stats);
	printf("\n--- %s ping statistics ---\n", rt->param->fqdn);
	printf("%d packets transmitted, %d received,",
			stats.pkt_send,
			stats.pkt_recvd);
	if (stats.icmp_errors != 0)
		printf(" +%u errors,", stats.icmp_errors);
	printf(" %.2f%% packet loss\n",
		100 - ((double)stats.pkt_recvd / (double)stats.pkt_send * 100));
	if (stats.pkt_recvd > 0)
		printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
					stats.rtt_min,
					stats.rtt_avg,
					stats.rtt_max,
					stats.std_deviation);
	else
		printf("\n");
	free_packetlist(rt->rpacketlist_head);
}
