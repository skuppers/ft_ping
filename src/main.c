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

void	ping_fatal(const char *failed_here, const char *errbuff)
{
	printf("Fatal error in %s: %s\n", failed_here, errbuff);
}

static void	init_param(t_data *param)
{
		memset(param, 0, sizeof(struct s_data));
		param->ttl = 255;
		param->interval = 1.0;
		param->pkt_size = 36;
}

static void	init_signals(t_signals *signals)
{
	memset(signals, 0, sizeof(struct s_signals));
	g_signals = signals;
	signal(SIGALRM, &sigalrm_handle);
	signal(SIGINT, &sigint_handle);
}

int		main(int ac, char **av)
{
		t_data		param;
		t_signals	signals;

		if (ac < 2)
			print_usage(42);
		init_param(&param);
		init_signals(&signals);
		parse_opt(ac, av, &param);
		if (resolve_target(&param) < 0)
			return (-1);
		else 
		{
			printf("\nPING OPTIONS: "BYTE_TO_BIN_PATTERN,BYTE_TO_BIN(param.options));
			printf("\nTTL: 			%d\n", param.ttl);
			printf("Count: 			%d\n", param.count);
			printf("Packet size: 	%d\n", param.pkt_size);
			printf("Tos:		 	%d\n", param.tos);
			printf("Preload:		%d\n", param.preload);
			printf("Timeout: 		%d\n", param.timeout);
			printf("Deadline: 		%d\n", param.deadline);
			printf("Interval: 		%f\n", param.interval);
			printf("Interface:		%s\n", param.interface->ifa_name);
			printf("Host/FQDN: 		%s\n", param.fqdn);
			printf("Host IP: 		%s\n\n", param.ipv4_str);
		
			ft_ping(&param);
		}
		return (0);
}