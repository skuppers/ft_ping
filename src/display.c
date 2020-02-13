/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:05:02 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 15:42:29 by skuppers         ###   ########.fr       */
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
		printf("Added %f to std_deviation. total: %f\n", dev, param->std_deviation);

		++iterator;
	}
	param->std_deviation = (float)(param->std_deviation / param->pkt_recvd);
}

void	print_stats(t_data *param)
{
	printf("\n--- %s ping statistics ---\n", param->fqdn);

	printf("%d packets transmitted, %d received, %.2f%% packet loss\n",
			param->pkt_send, param->pkt_recvd,
			(100 - ((double)(param->pkt_recvd / param->pkt_send) * 100)));

	param->rtt_avg = (param->rtt_avg / param->pkt_recvd);
	get_stddev(param);
	printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.2f ms\n",
					param->rtt_min,
					param->rtt_avg,
					param->rtt_max,
					param->std_deviation);
}
