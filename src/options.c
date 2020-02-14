/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 08:55:41 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/07 14:02:44 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int8_t	err(void)
{
	printf("ft_ping: invalid argument: %s\n", optarg);
	return (-1);
}

int32_t	parse_opt(int ac, char **av, t_data *param)
{
	int32_t		option;

	while ((option = getopt(ac, av, "vhqfs:t:c:")) != -1)
	{
		if (option == 'h')
			print_usage(1);
		else if (option == 'v')
			param->options |= OPT_VERBOSE;
		else if (option == 's')
			(ft_atoi(optarg) > 0 ? param->pkt_size = ft_atoi(optarg) : err());
		else if (option == 't')
			(ft_atoi(optarg) > 0 ? param->ttl = ft_atoi(optarg) : err());
		else if (option == 'c')
			(ft_atoi(optarg) > 0 ? param->count = ft_atoi(optarg) : err());
		//:welse if ()
		else if (option == 'q')
			param->options |= OPT_SILENT;
		else
			print_usage(42);
	}
	return (optind);
}
