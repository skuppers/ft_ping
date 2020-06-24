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
/*
static int8_t	valid_args(char *argument, int min, int max, char opt)
{
	if (argument == NULL || ft_strlen(argument) == 0)
	{
		printf("ft_ping: option requires an argument -- '%c'\n", opt);
		exit(42);
	}
	if (!ft_isnumeric(argument))
	{
		printf("ft_ping: invalid argument: '%s'\n", argument);
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

uint8_t			check_dest(char **av)
{
	if (g_optind != -1)
	{
		printf("optind:%s | +1: %s\n", av[g_optind], av[g_optind + 1]);
		if (av[g_optind + 1] != NULL)
		{
			printf("ft_ping: multiple hops are not allowed: %s\n",
				av[g_optind + 1]);
			ft_freetab(&av);
			return (-1);
		}
	}
	return (0);
}
*/
#define NB_OPT 10
#define OPT_WITHOUT_ARG 5
/*
static void		error_opt(char *msg)
{
	ft_dprintf(STDERR_FILENO,
			"Error: %s\nFor help, use ./ft_ping -h\n", msg);
	ft_strdel(&msg);
	exit(-1);
//	exit_routine(ERR, NULL);
}
*/
static void		get_arg_opt(char *arg, const char *opt_str[], const int count, t_data *param)
{
	if (arg == NULL)
	{
		printf("ft_ping: option requires an argument -- '%s'\n", opt_str[count]);
		exit(42) ;
	}
	if (ft_strequ(opt_str[count], "-c") == 1)
	{
		if (ft_strlen(arg) > 6 || ft_atoi(arg) < 1 || ft_atoi(arg) > 65535)
		{
			printf("ft_ping: -c: argument '%s' out of range: 1-65535\n", arg);
			exit(42);
		}
		param->count = ft_atoi(arg);
	}
	if (ft_strequ(opt_str[count], "-Q") == 1)
	{
		if (ft_strlen(arg) > 3 || ft_atoi(arg) < 0 || ft_atoi(arg) > 255)
		{
			printf("ft_ping: -Q: argument '%s' out of range: 0-255\n", arg);
			exit(42);
		}
		param->tos = ft_atoi(arg);
	}
	if (ft_strequ(opt_str[count], "-i") == 1)
	{
		if (ft_strlen(arg) > 6 || ft_atoi(arg) < 1 || ft_atoi(arg) > 65535)
		{
			printf("ft_ping: -i: argument '%s' out of range: 1-65535\n", arg);
			exit(42);
		}
		param->interval = ft_atoi(arg);
	}
	if (ft_strequ(opt_str[count], "-t") == 1)
	{
		if (ft_strlen(arg) > 6 || ft_atoi(arg) < 1 || ft_atoi(arg) > 255)
		{
			printf("ft_ping: -t: argument '%s' out of range: 1-255\n", arg);
			exit(42);
		}
		param->ttl = ft_atoi(arg);
	}
	if (ft_strequ(opt_str[count], "-s") == 1)
	{
		if (ft_strlen(arg) > 6 || ft_atoi(arg) < 0 || ft_atoi(arg) > 65535)
		{
			printf("ft_ping: -s: argument '%s' out of range: 0-65535\n", arg);
			exit(42);
		}
		param->pkt_size = ft_atoi(arg);
	}
}

static int		get_one_opt(char **av, int i, t_data *param)
{
	int			count;
	const char	*opt_str[] = {"-h", "-d", "-D", "-q", "-v",
							"-c", "-Q", "-i", "-t", "-s" };
	
	count = 0;
	while (count < NB_OPT)
	{
		if (ft_strequ(av[i], opt_str[count]) == 1)
		{
			if (count < OPT_WITHOUT_ARG)
			{
				param->options |= (1 << count);
				if (param->options & OPT_HELP)
				{
					print_help(42);
					exit(1);
				}
				return (1);
			}
			else
			{
				get_arg_opt(av[i + 1], opt_str, count, param);
			//	printf("Options: %d.\n", param->options);
				return (2);
			}
		}
		count++;
	}
	printf("ft_ping: invalid option -- '%s'\n\n", av[i]);
	exit (-1);
}
/*
static int		get_long_opt(char **av, int i)
{
	const char	*opt_str[] = {"--help", "--sodebug",
							"--timestamp", "--quiet", "--verbose",
							"--count", "--qos", "--interval",
							"--ttl", "--size" };

	return (1);
}
*/
static void		parse_opts(int ac, char **av, t_data *param)
{
	(void)ac;
	int			i;

	i = 0;
	while (av[i] != NULL)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] != '\0' && av[i][1] == '-')
			{
				i += 1;//get_long_opt(av, i);
				continue ;
			}
			i += get_one_opt(av, i, param);
			continue ;
		}
		if (param->fqdn == NULL)
		{
			param->fqdn = ft_strdup(av[i]);
			printf("Destination is %s\n", param->fqdn);
			++i;
		}
		else
		{
			printf("ft_ping: Multiple hops are not allowed: %s\n", av[i]);
			exit(1);
		}
	}
}

int8_t			parse_opt(int ac, char **av, t_data *param)
{
//	int32_t		option;

	++av;
	parse_opts(ac, av, param);

/*	av = ft_getopt_order_arguments(ac, av, OPT_CHARSET);
	ft_showtab(av);
	while ((option = ft_getopt(ac, av, OPT_CHARSET)) != -1)
	{
		if (option == 'h' || option == 'd'
				|| option == 'D' || option == 'v' || option == 'q')
			handle_standalone_options(option, param);
		else if (option == 'c' || option == 'i'
				|| option == 'Q' || option == 't' || option == 's')
			handle_custom_options(option, param, g_optarg);
		else
			option_not_supported(option);
	}


	if (check_dest(av) != 0)
		return (-1);
	if (g_optind != -1 && av[g_optind] != NULL)
		param->fqdn = ft_strdup(av[g_optind]);
	ft_freetab(&av);
*/
	return (0);
}
