/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 08:55:41 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/07 11:22:44 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"


int16_t	opt_check_count(char **av, uint16_t i, t_data *param)
{
	if (av[i] == "-c")
	{
		if (ft_atoi(av[i + 1]) == 0)
		{
			printf("ft_ping: invalid count of packets to transmit: %s\n", av[i + 1]);
			return (-1);
		}
		else
			param->count = ft_atoi(av[i + 1]);
	}
	return (i + 1);
}
int16_t	opt_check_ttl(char **av, uint16_t i, t_data *param)
{
	if (av[i] == "-m")
	{
		if (ft_atoi(av[i + 1]) == 0 || ft_atoi(av[i + 1]) > 255)
		{
			printf("ft_ping: invalid TTL: %s\n", av[i + 1]);
			return (-1);
		}
		else
			param->ttl = ft_atoi(av[i + 1]);
	}
	return (i + 1);
}
int16_t	opt_check_src(char **av, uint16_t i, t_data *param)
{
	if (av[i] == "-S")
	{
		if (ft_atoi(av[i + 1]) == 0)
		{
			printf("ft_ping: invalid count of packets to transmit: %s\n", av[i + 1]);
			return (-1);
		}
		else
			param->src_address = NULL; //ft_atoi(av[i + 1]);
	}
	return (i + 1);
}
int16_t	opt_check_pktsize(char **av, uint16_t i, t_data *param)
{
	if (av[i] == "-s")
	{
		if (ft_atoi(av[i + 1]) == 0 | ft_atoi(av[i + 1]) > 65507)
		{
			printf("ft_ping: packet size too large: %s\n", av[i + 1]);
			return (-1);
		}
		else
			param->pkt_size = ft_atoi(av[i + 1]);
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
			printf("Parsing |%c|\n", av[i][idx]);
			if (av[i][idx] == 'o')
				param->options |= OPT_ONCE;
			else if (av[i][idx] == 'v')
				param->options |= OPT_VERBOSE;
			else if (av[i][idx] == 'h')
				param->options |= OPT_HELP;

			else if (av[i][idx] == 'c')
			{	i = opt_check_count(av, i, param);
				return (0);
			}
			else if (av[i][idx] == 'm')
			{	i = opt_check_ttl(av, i, param);
				return (0); }
			else if (av[i][idx] == 'S')
			{	i = opt_check_src(av, i, param);
				return (0); }
			else if (av[i][idx] == 's')
			{	i = opt_check_pktsize(av, i, param);
				return (0); }
			else
				return (-42);
			++idx;
		}
	}
	else
	{
		printf("Interpreted |%s| as FQND/HOST\n", av[i]);
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
		int returns = check_flags(i, av, length, param);
		printf("Returned %d\n", returns);

		if (i == -42)
			return (-1);
		++i;
	}


	return (0);
}

