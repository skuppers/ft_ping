/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 08:55:41 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/07 10:28:31 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

uint32_t	check_flags(uint16_t i, char **av,
				uint32_t length, t_data *param)
{
	uint32_t	idx;
	uint8_t		opt_arg;

	idx = 0;
	opt_arg = 0;

	if (av[i] != NULL && ft_strbeginswith(av[i],"-") == 1)
	{
		while (idx < length && av[i][idx] != '\0')
		{
			printf("Parsing |%c|\n", av[i][idx]);
			if (av[i][idx] == 'o')
				param->options |= OPT_ONCE;
			else if (av[i][idx] == 'v')
				param->options |= OPT_VERBOSE;
			else if (av[i][idx] == 'h')
				param->options |= OPT_HELP;
			++idx;
		}
	}
	else
	{
		printf("Interpreted %s as FQND/HOST\n", av[i]);
		// regex for fqdn or host ip
	}
	return (0);
}


uint8_t	parse_opt(int ac, char **av, t_data *param)
{
	// activate option like '-h -c -v -m -o -S -s -W'
	// return the FQDN or IP with regex
	int32_t		i;
	uint32_t	y;
	uint32_t	length;

	i = 1;
	++(*av);
	length = 0;
	while (i < ac && av[i] != NULL)
	{
		y = 0;
		length = ft_strlen(av[i]);
		printf("Parsing argument |%s|\n", av[i]);
		exit(0);
		i = check_flags(i, av, length, param);
		if (i == -42)
			return (-1);
		++i;
	}


	return (0);
}

