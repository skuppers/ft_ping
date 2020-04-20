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

/*	Option parsing file.
 *	Possible options are:
 *	-c <number>     (count)			Impl.
 *	-d           	SO_DEBUG		Impl.
 *	-I				interface		Impl.
 *	-D				timestamp		Impl.
 *	-h				Help			Impl.
 *	-Q <tos>        Tos				Impl.
 *	-i <number>		interval		Impl.
 *	-q				Quiet			Impl.
 *	-v				Verbose			Impl.
 *	-t <number>		TTL				Impl.
 *	-s <number>		packetsize		Impl.
 */

#include "ft_ping.h"

void	invalid_opt(char *optarg, char *option)
{
	if (optarg == NULL)
		printf("ft_ping: option requires an argument -- '%s'\n", option);
	else
		printf("ft_ping: invalid argument: %s\n", optarg);
	exit(-1);
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
		(ft_atoi(oarg) > 0) ? prm->count = (uint16_t)ft_atoi(oarg) : invalid_opt(oarg, "c");
	else if (opt == 'i')
		(ft_atoi(oarg) > 0) ? prm->interval = ft_atoi(oarg) : invalid_opt(oarg, "i");
	else if (opt == 'I')
		(is_interface_valid(prm, oarg) == 0) ? 0 : invalid_opt(oarg, "I");
	else if (opt == 's')
		(ft_atoi(oarg) > 0) ? prm->pkt_size = ft_atoi(oarg) : invalid_opt(oarg, "s");
	else if (opt == 'Q')
		(ft_atoi(oarg) > 0) ? prm->tos = ft_atoi(oarg) : invalid_opt(oarg, "Q");
	else if (opt == 't')
		(ft_atoi(oarg) > 0) ? prm->ttl = ft_atoi(oarg) : invalid_opt(oarg, "t");	
}

int32_t	parse_opt(int ac, char **av, t_data *param)
{
	int32_t		option;

	while ((option = ft_getopt(ac, av, "c:i:I:Q:t:s:dDhqv")) != -1)
	{
		if (option == 'h' ||  option == 'd'
				|| option == 'D' || option == 'v' || option == 'q')
			handle_standalone_options(option, param);

		else if (option == 'c' || option == 'i' || option == 'I'
				|| option == 'Q' || option == 't' || option == 's')

			handle_custom_options(option, param, g_optarg);
		else
			print_usage(1);
	}
	if (av[optind] != NULL)
		param->fqdn = av[g_optopt];
	return (0);
}