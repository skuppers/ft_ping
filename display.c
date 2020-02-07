/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:05:02 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/07 14:16:53 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_resolve(t_data *param)
{
		printf("PING %s (%s): %d data bytes\n", param->fqdn, param->hostname,
						param->pkt_size);
}

void	print_ping(t_data *param)
{
	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%f ms\n",
					param->pkt_size, param->hostname, 42, param->ttl, 1.420f);
}

void	print_stats(t_data *param)
{
	printf("--- %s ping statistics ---\n", param->fqdn);
	printf("%d packets transmitted, %d packets received, %f%% packet loss\n",
					42, 42, 100.0f);
	printf("round-trip min/avg/max/stddev = %f/%f/%f/%fms\n",
					1.420f,1.420f,1.420f,0.042f);
}
