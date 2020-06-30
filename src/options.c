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

void				ping_exit(int exitcode, const char *message, ...)
{
	va_list			args;

	dprintf(STDERR_FILENO, "ft_ping: ");
	va_start(args, message);
	vdprintf(STDERR_FILENO, message, args);
	va_end(args);
	exit(exitcode);
}

static void		get_arg_opt(char *arg, const char *opt_str[],
								const int count, t_data *param)
{
	if (arg == NULL)
		ping_exit(42, "option requires an argument -- '%s'\n", opt_str[count]);
	if (ft_strequ(opt_str[count], "-c") == 1)
	{
		if (ft_strlen(arg) > 6 || ft_atoi(arg) < 1 || ft_atoi(arg) > 65535)
			invalid_count(arg);
		param->count = ft_atoi(arg);
	}
	if (ft_strequ(opt_str[count], "-Q") == 1)
	{
		if (ft_strlen(arg) > 3 || ft_atoi(arg) < 0 || ft_atoi(arg) > 255)
			invalid_tos(arg);
		param->tos = ft_atoi(arg);
	}
	if (ft_strequ(opt_str[count], "-i") == 1)
	{
		if (ft_strlen(arg) > 6 || ft_atoi(arg) < 1 || ft_atoi(arg) > 65535)
			invalid_timing(arg);
		param->interval = ft_atoi(arg);
	}
	if (ft_strequ(opt_str[count], "-t") == 1)
	{
		if (ft_strlen(arg) > 6 || ft_atoi(arg) < 1 || ft_atoi(arg) > 255)
			invalid_ttl(arg);
		param->ttl = ft_atoi(arg);
	}
	if (ft_strequ(opt_str[count], "-s") == 1)
	{
		if (ft_strlen(arg) > 6 || ft_atoi(arg) < 0 || ft_atoi(arg) > 65535)
			invalid_size(arg);
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
					print_help(42);
				return (1);
			}
			else
			{
				get_arg_opt(av[i + 1], opt_str, count, param);
				return (2);
			}
		}
		count++;
	}
	ping_exit(42, "invalid option -- '%s'\n", av[i]);
	return (0);
}

int8_t			parse_opt(char **av, t_data *param)
{
	int			i;

	++av;
	i = 0;
	while (av[i] != NULL)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] != '\0' && av[i][1] == '-')
				i += 1;
			else
			{
				i += get_one_opt(av, i, param);
				continue ;
			}
		}
		if (param->fqdn == NULL)
		{
			param->fqdn = ft_strdup(av[i]);
			++i;
		}
		else if (av[i] != NULL)
			ping_exit(42, "Multiple hops are not allowed: %s\n", av[i]);
	}
	return (0);
}
