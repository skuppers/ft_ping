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

int16_t	opt_check_count(char **av, uint16_t i, t_data *param)
{
	if (ft_strequ(av[i],"-c"))
	{
		if (av[i + 1] == NULL || ft_strequ(av[i + 1], "\0"))
		{
			printf("ft_ping: option requires an argument -- 'c'\n");
			print_usage();
			return (-1);
		}
		if (ft_atoi(av[i + 1]) == 0)
		{
			printf("ft_ping: invalid count of packets to transmit: %s\n", av[i + 1]);
			return (-1);
		}
		param->count = ft_atoi(av[i + 1]);
		printf("Set count to %d\n", param->count);
	}
	return (i + 1);
}
int16_t	opt_check_ttl(char **av, uint16_t i, t_data *param)
{
	if (ft_strequ(av[i], "-m"))
	{
		if (av[i + 1] == NULL || ft_strequ(av[i + 1], "\0"))
		{
			print_usage();
			return (-1);
		}
		if (ft_atoi(av[i + 1]) == 0 || ft_atoi(av[i + 1]) > 255)
		{
			printf("ft_ping: invalid TTL: %s\n", av[i + 1]);
			return (-1);
		}
		param->ttl = ft_atoi(av[i + 1]);
		printf("Set TTL to %d\n", param->ttl);

	}
	return (i + 1);
}
int16_t	opt_check_src(char **av, uint16_t i, t_data *param)
{
	if (ft_strequ(av[i],"-S"))
	{
		if (av[i + 1] == NULL || ft_strequ(av[i + 1], "\0"))
		{
			print_usage();
			return (-1);
		}
		if (ft_atoi(av[i + 1]) == 0)
		{
			printf("ft_ping: invalid source ip: %s\n", av[i + 1]);
			return (-1);
		}
		param->src_address = 0; //ft_atoi(av[i + 1]);
		printf("Set source to %d\n", param->src_address);
	}
	return (i + 1);
}
int16_t	opt_check_pktsize(char **av, uint16_t i, t_data *param)
{
	if (ft_strequ(av[i],"-s"))
	{
		if (av[i + 1] == NULL || ft_strequ(av[i + 1], "\0"))
		{
			print_usage();
			return (-1);
		}
		if (ft_atoi(av[i + 1]) == 0 | ft_atoi(av[i + 1]) > 65507)
		{
			printf("ft_ping: packet size too large: %s\n", av[i + 1]);
			return (-1);
		}
		param->pkt_size = ft_atoi(av[i + 1]);
		printf("Set packet size to %d\n", param->pkt_size);
	}
	return (i + 1);
}
int32_t	check_flags(uint16_t i, char **av,
				uint32_t length, t_data *param)
{
	uint32_t	idx;
	uint8_t		opt_arg;

	idx = 0;
	opt_arg = 0;

	if (av[i] != NULL && ft_strbeginswith(av[i],"-") == 1)
	{
		idx = 1;
		while (idx < length && av[i][idx] != '\0')
		{
//			printf("Parsing |%c|\n", av[i][idx]);
			if (av[i][idx] == 'o')
				param->options |= OPT_ONCE;
			else if (av[i][idx] == 'v')
				param->options |= OPT_VERBOSE;
			else if (av[i][idx] == 'h')
				param->options |= OPT_HELP;

			else if (av[i][idx] == 'c')
			{	return(opt_check_count(av, i, param));
			}
			else if (av[i][idx] == 'm')
			{	return(opt_check_ttl(av, i, param));
			 }
			else if (av[i][idx] == 'S')
			{	return(opt_check_src(av, i, param));
			}
			else if (av[i][idx] == 's')
			{	return(opt_check_pktsize(av, i, param));
			}
			else
				return (-42);
			++idx;
		}
	}
	else
	{
		param->fqdn = av[i];
//		printf("Interpreted |%s| as FQND/HOST\n", av[i]);
// regex for fqdn or host ip
	}
	return (i);
}


uint8_t	parse_opt(int ac, char **av, t_data *param)
{
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
		i = check_flags(i, av, length, param);
		if (i == -1)
				return (-1);
		++i;
	}
	if (param->fqdn == NULL)
	{
		print_usage();
		return (-1);
	}
	return (0);
}
