/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:01 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 15:23:56 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	ping_fatal(const char *failed_here, const char *errbuff)
{
	printf("Fatal error in %s: %s\n", failed_here, errbuff);
}


static void	init_param(t_data *param)
{
		g_param = param;
		memset(param, 0, sizeof(struct s_data));
		param->ttl = 64;
		param->interval = 1.0;
		param->pkt_size = 64;

//      List interfaces, store references to later select interface & ip. Default to interface 1 ? not 0
//		getifaddrs(&(param->interfaces));
//

}

int		main(int ac, char **av)
{
		t_data		param;
		uint32_t	target_index;

		if (ac < 2)
			print_usage(42);

		init_param(&param);
		parse_opt(ac, av, &param);


		if (resolve_fqdn(&param) < 0)
			return (-1);

			printf("\nPING OPTIONS: %x\n", param.options);
			printf("TTL: 			%d\n", param.ttl);
			printf("Count: 			%d\n", param.count);
			printf("Packet size: 	%d\n", param.pkt_size);
			printf("Tos:		 	%d\n", param.tos);
			printf("Preload:		%d\n", param.preload);
			printf("Timeout: 		%d\n", param.timeout);
			printf("Deadline: 		%d\n", param.deadline);
			printf("Interval: 		%f\n", param.interval);
			printf("Host/FQDN: 		%s\n", param.fqdn);
			printf("Host IP: 		%s\n\n", param.ipv4_str);

//			for (struct ifaddrs *ifa = param.interfaces; ifa != NULL; ifa = ifa->ifa_next)
//			{
//				if(ifa->ifa_addr->sa_family == AF_INET)
//					printf("Interface: %s -- %s\n",
//					ifa->ifa_name,
//					inet_ntoa(((struct sockaddr_in*)(ifa->ifa_addr))->sin_addr));
//			}

//		signal(SIGINT, sigint_handle);
//		signal(SIGALRM, sigalrm_handle);

//		print_resolve(&param);
//		ft_ping(&param);
//		print_stats(&param);

		return (0);
}
