/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:01 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 11:13:41 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_usage(uint8_t exits)
{
		printf(" usage: ft_ping [-hvf] [-c count] [-m ttl]"
				" [-s packetsize] <host>\n");
		if (exits != 0)
			exit(exits);
}

void	init_param(t_data *param)
{
		param->options = 0;
		param->ttl = 64;
		param->count = 0;
		param->pkt_size = 64;
		param->timeout = 0;
		param->sigint = 0;
		param->fqdn = NULL;
		param->hostname = NULL;
		param->host = NULL;
}

int		main(int ac, char **av)
{
		t_data		param;
		uint32_t	target_index;

		if (ac < 2)
			print_usage(42);
		init_param(&param);
		g_param = &param;
		target_index = parse_opt(ac, av, &param);
		param.fqdn = av[target_index];
		resolve_fqdn(&param);


			printf("\nPING OPTIONS: %x\n", param.options);
			printf("TTL: 			%d\n", param.ttl);
			printf("Count: 			%d\n", param.count);
			printf("Packet size: 	%d\n", param.pkt_size);
			printf("Host/FQDN: 		%s\n", param.fqdn);
			printf("Host IP: 		%s\n\n", param.hostname);

		signal(SIGINT, sigint_handle);
//		signal(SIGALRM, sigalrm_handle);


		print_resolve(&param);
		ft_ping(&param);
		print_stats(&param);

		return (0);
}
