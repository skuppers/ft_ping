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

void			ping_exit(int exitcode, const char *message, ...)
{
	va_list			args;

	dprintf(STDERR_FILENO, "ft_ping: ");
	va_start(args, message);
	vdprintf(STDERR_FILENO, message, args);
	va_end(args);
	exit(exitcode);
}

static uint8_t	check_valid(char *arg, size_t len, int min, int max)
{
	if (ft_isnumeric(arg) == 0)
		invalid_opt(arg);
	if (ft_strlen(arg) > len || ft_atoi(arg) < min || ft_atoi(arg) > max)
		invalid_count(arg);
	return (1);
}

static int		get_arg_opt(char *arg, const char *opt_str[],
								const int count, t_data *param)
{
	if (arg == NULL)
		ping_exit(42, "option requires an argument -- '%s'\n", opt_str[count]);
	if (ft_strequ(opt_str[count], "-c") == 1 && check_valid(arg, 6, 1, 65535))
		param->count = ft_atoi(arg);
	if (ft_strequ(opt_str[count], "-Q") == 1 && check_valid(arg, 3, 0, 255))
		param->tos = ft_atoi(arg);
	if (ft_strequ(opt_str[count], "-i") == 1 && check_valid(arg, 6, 1, 65535))
		param->interval = ft_atoi(arg);
	if (ft_strequ(opt_str[count], "-t") == 1 && check_valid(arg, 6, 1, 255))
		param->ttl = ft_atoi(arg);
	if (ft_strequ(opt_str[count], "-s") == 1 && check_valid(arg, 6, 0, 65535))
		param->pkt_size = ft_atoi(arg);
	return (2);
}

#ifdef BONUS_H

static int	get_bns_opt(char **av, int i, t_data *param)
{
	int			count;
	const char	*opt_str[] = {"-h", "-d", "-D", "-q", "-v",
							"-c", "-Q", "-i", "-t", "-s" };

	count = 0;
	while (count < 10)
	{
		if (ft_strequ(av[i], opt_str[count]) == 1)
		{
			if (count < 5)
			{
				param->options |= (1 << count);
				if (param->options & OPT_HELP)
					print_help(42);
				return (1);
			}
			else
				return (get_arg_opt(av[i + 1], opt_str, count, param));
		}
		count++;
	}
	ping_exit(42, "invalid option -- '%s'\n", av[i]);
	return (0);
}

static int		get_one_opt(char **av, int i, t_data *param)
{
	return (get_bns_opt(av, i, param));
}

#else

static int	get_std_opt(char **av, int i, t_data *param)
{
	int			count;
	const char	*opt_str[] = {"-h", "-v"};

	count = 0;
	while (count < 2)
	{
		if (ft_strequ(av[i], opt_str[count]) == 1)
		{
			if (count < 2)
			{
				param->options |= (1 << count);
				if (param->options & OPT_HELP)
					print_help(42);
				return (1);
			}
			else
				return (get_arg_opt(av[i + 1], opt_str, count, param));
		}
		count++;
	}
	ping_exit(42, "invalid option -- '%s'\n", av[i]);
	return (0);
}

static int		get_one_opt(char **av, int i, t_data *param)
{
	return (get_std_opt(av, i, param));
}

#endif

int8_t			parse_opt(char **av, t_data *param)
{
	int			i;

	++av;
	i = 0;
	while (av[i] != NULL)
	{
		if (av[i][0] == '-')
		{
			i += get_one_opt(av, i, param);
			continue ;
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
