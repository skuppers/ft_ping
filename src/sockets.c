/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sockets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:26:15 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 15:44:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int8_t		configuresocket(int clientsocket, t_data *param)
{
	int				on;

	if (setsockopt(clientsocket, IPPROTO_IP, IP_TTL, &(param->ttl),
		sizeof(uint8_t)) < 0)
	{
		ping_fatal("setsockopt", "failed to configure ttl");
		return (-1);
	}
	if (setsockopt(clientsocket, IPPROTO_IP, IP_TOS, &(param->tos),
		sizeof(uint8_t)) < 0)
	{
		ping_fatal("setsockopt", "failed to configure Tos");
		return (-1);
	}
	if (param->options & OPT_SO_DEBUG)
	{
		on = 1;
		if (setsockopt(clientsocket, IPPROTO_IP, SO_DEBUG, &on,
			sizeof(int)) < 0)
		{
			ping_fatal("setsockopt", "failed to set the SO_DEBUG flag");
			return (-1);
		}
	}
	return (0);
}

static int8_t		configuretimeouts(int clientsocket)
{
	struct timeval	timeout;

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	if (setsockopt(clientsocket, SOL_IP, SO_SNDTIMEO, (char*)&timeout,
		sizeof(timeout)) < 0)
	{
		ping_fatal("configureTimeouts", "could no set snd timeout");
		return (-1);
	}
	if (setsockopt(clientsocket, SOL_IP, SO_RCVTIMEO, (char*)&timeout,
		sizeof(timeout)) < 0)
	{
		ping_fatal("configureTimeouts", "could no set recv timeout");
		return (-1);
	}
	return (0);
}

int32_t				createsocket(t_data *param)
{
	int				clientsocket;

	if ((clientsocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		ping_fatal("createsocket", "socket() failed");
		return (-1);
	}
	if (configuresocket(clientsocket, param) != 0)
		return (-1);
	if (configuretimeouts(clientsocket) != 0)
		return (-1);
	return (clientsocket);
}
