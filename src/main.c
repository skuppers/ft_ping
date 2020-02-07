/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:01 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/07 09:39:08 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_usage(void)
{
	printf("usage: ft_ping [-ovh] [-c count] [-m ttl]\n\
					[-S src_address] [-s packetsize] host\n");
}

int		main(int ac, char **av)
{
	t_data	param;

	if (ac < 2)
	{
		print_usage();
		return(42);
	}

	//parse arguments & fill preliminary data
	if (parse_opt(ac, av, &param) != 0)
		return (42);


	return (0);
}

