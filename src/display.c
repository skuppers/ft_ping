/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:05:02 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 14:28:50 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_resolve(t_data *param)
{
		printf("PING %s (%s): %d data bytes\n", param->fqdn, param->hostname,
						param->pkt_size);
}

void	print_ping(t_data *param, t_icmppacket *pkt, t_timer *t)
{
	(void)pkt;
	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.2f ms\n",
					param->pkt_size, param->hostname,
					pkt->header.un.echo.sequence, param->ttl, t->rtt_sec);
}

void	print_stats(t_data *param)
{
	printf("\n--- %s ping statistics ---\n", param->fqdn);

	printf("%d packets transmitted, %d packets received, %.3f%% packet loss\n",
			param->pkt_send, param->pkt_recvd,
			(100 - ((double)(param->pkt_recvd / param->pkt_send) * 100)));

	printf("round-trip min/avg/max/stddev = %.3f / %.3f / %.3f / %.2f ms\n",
					param->rtt_min, 0.420f,
					param->rtt_max, 0.420f);
}
