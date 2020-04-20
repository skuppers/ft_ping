/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:01 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:23:24 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BYTE_TO_BIN_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BIN(byte) \
		(byte & 0x80 ? '1' : '0'), \
		(byte & 0x40 ? '1' : '0'), \
		(byte & 0x20 ? '1' : '0'), \
		(byte & 0x10 ? '1' : '0'), \
		(byte & 0x08 ? '1' : '0'), \
		(byte & 0x04 ? '1' : '0'), \
		(byte & 0x02 ? '1' : '0'), \
		(byte & 0x01 ? '1' : '0')

#include "ft_ping.h"

int		main(int ac, char **av)
{
		t_data		param;
		t_signals	signals;

		if (ac < 2)
			print_usage(42);

		init_param(&param);
		init_signals(&signals);

// look here for corrections
		parse_opt(ac, av, &param);

/*
		printf("\nPING OPTIONS: "BYTE_TO_BIN_PATTERN,BYTE_TO_BIN(param.options));
		printf("\nTTL: 			%d\n", param.ttl);
		printf("Count: 			%d\n", param.count);
		printf("Packet size: 	%d\n", param.pkt_size);
		printf("Tos:		 	%d\n", param.tos);
		printf("Interval: 		%d\n", param.interval);
		printf("Interface:		%s\n", param.interface);
*/
		if (param.fqdn == NULL)
			print_usage(42);

// check for configured interfaces but no inet access
// also for special ips: broadcast, localhost, etc
		if (resolve_target(&param) < 0)
			return (-1);
		else 
		{
/*			printf("Interface:		%s\n", param.interface);
			printf("Host/FQDN: 		%s\n", param.fqdn);
			printf("Host IP: 		%s\n\n", param.ipv4_str);
*/
			ft_ping(&param);
		}
		return (0);
}