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

#ifdef BONUS_H

static int		get_bns_opt(char **av, int i, t_data *param)
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

static int		get_std_opt(char **av, int i, t_data *param)
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
