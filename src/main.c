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

#include "ft_ping.h"

int		main(int ac, char **av)
{
	t_data		param;
	t_signals	signals;

	if (ac < 2)
		print_usage(42);
	init_param(&param);
	init_signals(&signals);
	parse_opt(ac, av, &param);
	if (param.fqdn == NULL)
		print_usage(42);
	if (resolve_target(&param) < 0)
		return (-1);
	else
	{
		printf("Interface %s\n", param.interface);
		ft_ping(&param);
	}
	return (0);
}
