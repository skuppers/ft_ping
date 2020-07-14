/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:05:02 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 15:44:40 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

#ifdef BONUS_H

void	print_reverse(t_data *param, char *src)
{
	char	*hostdns;

	if (param->options & OPT_NUMERIC)
		dprintf(2, "%s: ", src);
	else
	{
		hostdns = reverse_target(src);
		dprintf(2, "%s (%s): ", (hostdns == NULL) ? src : hostdns, src);
		ft_strdel(&hostdns);
	}
}

#else

void	print_reverse(t_data *param, char *src)
{
	(void)param;
	dprintf(2, "%s: ", src);
}

#endif

void	print_timestamp(t_data *param, t_timer *tm)
{
	if (param->options & OPT_TIMESTAMP)
		dprintf(2, "[%f] ", (double)tm->recv.tv_sec
			+ (double)(0.001f * (double)tm->recv.tv_usec));
}

void	ft_freeaddrinfo(struct addrinfo *todel)
{
	struct addrinfo	*tmp;

	while (todel != NULL)
	{
		tmp = todel->ai_next;
		free(todel);
		todel = tmp;
	}
}

int8_t	is_loopback_duplicate(uint16_t code)
{
	if (code == 8)
		return (1);
	return (0);
}
