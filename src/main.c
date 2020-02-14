/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:01 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 16:41:31 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	ping_fatal(const char *failed_here, const char *errbuff)
{
	printf("Fatal error in %s: %s\n", failed_here, errbuff);
}

void	print_usage(uint8_t exits)
{
		printf(" usage: ft_ping [-hvf] [-c count] [-m ttl]"
				" [-s packetsize] <host>\n");
		if (exits != 0)
			exit(exits);
}

static void	init_param(t_data *param)
{
		memset(param, 0, sizeof(*param));
		memset(param->timings, 0, 4096);
		param->ttl = 64;
		param->pkt_size = 64;
		getifaddrs(&(param->interfaces));
		
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

		if (resolve_fqdn(&param) < 0)
			return (-1);




//			printf("\nPING OPTIONS: %x\n", param.options);
//			printf("TTL: 			%d\n", param.ttl);
//			printf("Count: 			%d\n", param.count);
//			printf("Packet size: 	%d\n", param.pkt_size);
			printf("Host/FQDN: 		%s\n", param.fqdn);
			printf("Host IP: 		%s\n\n", param.ipv4_str);
			for (struct ifaddrs *ifa = param.interfaces; ifa != NULL; ifa = ifa->ifa_next)
			{
				if(ifa->ifa_addr->sa_family == AF_INET) 
					printf("Interface: %s -- %s\n",
					ifa->ifa_name,
					inet_ntoa(((struct sockaddr_in*)(ifa->ifa_addr))->sin_addr));
			}
//		signal(SIGINT, sigint_handle);
//		signal(SIGALRM, sigalrm_handle);

//		print_resolve(&param);
//		ft_ping(&param);
//		print_stats(&param);

		return (0);
}
