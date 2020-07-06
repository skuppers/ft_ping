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

void		invalid_count(char *oarg)
{
	dprintf(2, "ft_ping: invalid argument '%s': out of range: 1-65535\n", oarg);
	exit(42);
}

void		invalid_timing(char *oarg)
{
	dprintf(2, "ft_ping: bad timing interval: %s\n", oarg);
	exit(42);
}

void		invalid_size(char *oarg)
{
	dprintf(2, "ft_ping: invalid argument '%s': out of range: 0-65507\n", oarg);
	exit(42);
}

void		invalid_tos(char *oarg)
{
	dprintf(2, "ft_ping: the value of TOS bits must be in range 0-255: %s\n",
		oarg);
	exit(42);
}

void		invalid_ttl(char *oarg)
{
	dprintf(2, "ft_ping: invalid argument: '%s': out of range: 1-255\n", oarg);
	exit(42);
}
