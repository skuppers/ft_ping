/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:17:44 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:45:25 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	invalid_opt(char *arg)
{
	dprintf(2, "ft_ping: invalid argument '%s'\n", arg);
	exit(42);
}

void	option_not_supported(int32_t arg)
{
	dprintf(2, "ft_ping: invalid option -- '%c'\n\n", arg);
	print_help(42);
}

void	print_usage(uint8_t exits)
{
	dprintf(2, "Usage: ft_ping [options] <destination>\n");
	if (exits != 0)
		exit(exits);
}

void	print_help(uint8_t exits)
{
	dprintf(2, "ft_ping:\n"
		"*	Possible options are:\n"
		"*	-c <number>     Send <number> of packets and quit.\n"
		"*	-d      	Set the SO_DEBUG flag on the socket.\n"
		"*	-D		Print the timestamp.\n"
		"*	-h		Shows this page.\n"
		"*	-Q <number>      Set the type of service (ToS).\n"
		"*	-i <number>	Specify send interval in seconds.\n"
		"*	-q		Quiet output.\n"
		"*	-v		Verbose	output.\n"
		"*	-t <number>	Specify the Time to Live of packets.\n"
		"*	-s <number>	Specify the packet size.\n\n");
	print_usage(exits);
}
