/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:01 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/07 14:02:57 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_usage(void)
{
	printf("usage: ft_ping [-ovh] [-c count] [-m ttl]\n\
					[-S src_address] [-s packetsize] host\n");
}

void	init_param(t_data *param)
{
	param->options = 0;
	param->ttl = 64;
	param->count = 0;
	param->src_address = 0;
	param->pkt_size = 64;
	param->fqdn = NULL;
	param->hostname = NULL;
	param->host = NULL;
}

int		main(int ac, char **av)
{
	t_data	param;

	if (ac < 2)
	{
		print_usage();
		return(42);
	}

	init_param(&param);
	if (parse_opt(ac, av, &param) != 0)
		return (42);

	resolve_fqdn(&param);

	printf("\nPING OPTIONS:\n");
	printf("TTL: %d\n", param.ttl);
	printf("Count: %d\n", param.count);
	printf("Src address: %d\n", param.src_address);
	printf("Packet size: %d\n", param.pkt_size);
	printf("Host/FQDN: %s\n", param.fqdn);
	printf("Host IP: %s\n\n", param.hostname);




	return (0);
}

