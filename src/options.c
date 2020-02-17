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
 *	-4				IPv4 only
 *	-6				IPv6 Only
 *	-c <number>     (count)			
 *	-d           	SO_DEBUG		Impl.
 *	-i <number>		interval		
 *	-I				interface		
 *	-l <number>		preload
 *	-D				timestamp		
 *	-h				Help			Impl.
 *	-Q <tos>        Tos				Impl.
 *	-q				Quiet
 *	-v				Verbose
 *	-t <number>		TTL				Impl.
 *	-s <number>		packetsize		Impl.
 *	-w <deadline>	deadline
 *	-W <timeout>	timeout
 */

#include "ft_ping.h"

void	invalid_opt(char * optarg)
{
	printf("ft_ping: invalid argument: %s\n", optarg);
	exit(-1);
}

void	print_usage(uint8_t exits)
{
		printf("Usage: ft_ping [-46dDhqv] [-c count] [-i interval] [-I interface]\n"
				"\t[-l preload] [-s packetsize] [-Q tos] [-t TTL]\n"
				"\t[-w deadline] [-W timeout] <host>\n");
		if (exits != 0)
			exit(exits);
}

static void		handle_standalone_options(int32_t option, t_data *param)
{
	if (option == 'h')
		print_usage(1);
	else if (option == 'v')
		param->options |= OPT_VERBOSE;
	else if (option == 'q')
		param->options |= OPT_QUIET;
	else if (option == 'd')
		param->options |= OPT_SO_DEBUG;
	else if (option == 'D')
		param->options |= OPT_TIMESTAMP;
	else if (option == '4')
		param->options |= OPT_IPV4;
	else if (option == '6')
		param->options |= OPT_IPV6;
}

static void		handle_custom_options(int32_t opt, t_data *prm, char *oarg)
{
	if (opt == 'c')
		(ft_atoi(oarg) > 0) ? prm->count = (uint16_t)ft_atoi(oarg) : invalid_opt(oarg);
	else if (opt == 'i')
		;//(ft_atoi(oarg) > 0) ? prm-> = ft_atoi(oarg) : invalid_opt();
	else if (opt == 'I')
		(is_interface_valid(prm, oarg) == 0) ? 0 : invalid_opt(oarg);
	else if (opt == 'l')
		(ft_atoi(oarg) > 0) ? prm->preload = ft_atoi(oarg) : invalid_opt(oarg);
	else if (opt == 's')
		(ft_atoi(oarg) > 0) ? prm->pkt_size = ft_atoi(oarg) : invalid_opt(oarg);
	else if (opt == 'Q')
		(ft_atoi(oarg) > 0) ? prm->tos = ft_atoi(oarg) : invalid_opt(oarg);
	else if (opt == 't')
		(ft_atoi(oarg) > 0) ? prm->ttl = ft_atoi(oarg) : invalid_opt(oarg);
	else if (opt == 'W')
		(ft_atoi(oarg) > 0) ? prm->deadline = ft_atoi(oarg) : invalid_opt(oarg);
	else if (opt == 'w')
		(ft_atoi(oarg) > 0) ? prm->timeout = ft_atoi(oarg) : invalid_opt(oarg);
}

int32_t	parse_opt(int ac, char **av, t_data *param)
{
	int32_t		option;

	while ((option = getopt(ac, av, "c:i:I:l:Q:t:s:w:W:46dDhqv")) != -1)
	{
		if (option == 'h' || option == '4' || option == '6' || option == 'd'
						|| option == 'D' || option == 'v' || option == 'q')
			handle_standalone_options(option, param);
		else if (option == 'c' || option == 'i' || option == 'I' || option == 'l'
						|| option == 'Q' || option == 't' || option == 's'
						|| option == 'w' || option == 'W')
			handle_custom_options(option, param, optarg);
		else
			print_usage(1);
	}
	if (av[optind] != NULL)
		param->fqdn = av[optind];
	return (0);
}