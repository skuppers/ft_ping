/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 08:55:41 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 15:56:42 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int8_t    valid_args(char *argument, int min, int max, char opt)
{
	if (argument == NULL || ft_strlen(argument) == 0)
	{
		printf("ft_ping: option requires an argument -- '%c'\n", opt);
		exit(42);
	}
    if (!ft_isnumeric(argument))
    {
		printf("ft_ping: invalid argument: %s\n", argument);
		exit(42);
	}
    if (ft_strlen(argument) > 5)
        return (-2);
    if (ft_atoi(argument) > max)
        return (-3);
    if (ft_atoi(argument) < min)
        return (-4);
    return (1);
}

static void		handle_standalone_options(int32_t option, t_data *param)
{
	if (option == 'h')
		print_help(1);
	else if (option == 'v')
		param->options |= OPT_VERBOSE;
	else if (option == 'q')
		param->options |= OPT_QUIET;
	else if (option == 'd')
		param->options |= OPT_SO_DEBUG;
	else if (option == 'D')
		param->options |= OPT_TIMESTAMP;
}

static void		handle_custom_options(int32_t opt, t_data *prm, char *oarg)
{
	if (opt == 'c')
		(valid_args(oarg, 1, 65535, 'c') == 1) ? prm->count = (uint16_t)ft_atoi(oarg) : invalid_count(oarg);

	else if (opt == 'i')
		(valid_args(oarg, 1, 255, 'i') == 1)? prm->interval = ft_atoi(oarg) : invalid_timing(oarg);

	else if (opt == 's')
		(valid_args(oarg, 0, 65507, 's') == 1)? prm->pkt_size = ft_atoi(oarg) : invalid_size(oarg);

	else if (opt == 'Q')
		(valid_args(oarg, 1, 255, 'Q') == 1)? prm->tos = ft_atoi(oarg) : invalid_tos(oarg);

	else if (opt == 't')
		(valid_args(oarg, 1, 255, 't') == 1)? prm->ttl = ft_atoi(oarg) : invalid_ttl(oarg);
}

int32_t			parse_opt(int ac, char **av, t_data *param)
{
	int32_t		option;

	av = ft_getopt_order_arguments(ac, av, OPT_CHARSET);
	while ((option = ft_getopt(ac, av, OPT_CHARSET)) != -1)
	{
		if (option == 'h' || option == 'd'
				|| option == 'D' || option == 'v' || option == 'q')
			handle_standalone_options(option, param);

		else if (option == 'c' || option == 'i'
				|| option == 'Q' || option == 't' || option == 's')
			handle_custom_options(option, param, g_optarg);

		else
			print_usage(1);
	}
	if (g_optind != -1 && av[g_optind + 1] != NULL)
	{
		printf("ft_ping: multiple hops are not allowed: %s\n", av[g_optind + 1]);
	}
	if (g_optind != -1 && av[g_optind] != NULL)
		param->fqdn = ft_strdup(av[g_optind]);
	
//	printf("fqdn:%s +1:%s\n", av[g_optind], av[g_optind + 1]);
//	printf("Options: s:%d t:%d Q:%d i:%d c:%d\n",
//		param->pkt_size, param->ttl, param->tos, param->interval, param->count);

	ft_freetab(&av);
	return (0);
}
