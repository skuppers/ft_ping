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

int32_t	createSocket(t_data *param)
{
	int clientsocket;

	if (param->options & OPT_IPV4)
	{
		if ((clientsocket = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
		{
			ping_fatal("createSocket()", "Could not create raw ipv4 socket. Are you root?");
			return (-1);
		}
		return (clientsocket);
	}
	if ((clientsocket = socket(AF_INET6, SOCK_RAW, IPPROTO_RAW)) < 0)
	{
		ping_fatal("createSocket()", "Could not create raw ipv6 socket. Are you root?");
		return (-1);
	}
	return (clientsocket);
}

int8_t setSocketOptions(t_data *param, int socket)
{
		int32_t	on;
		struct ifreq	if_bind;

		on = 1;
		memset(&if_bind, 0, sizeof(struct ifreq));
		ft_strncpy(if_bind.ifr_name, (const char*)param->interface->ifa_name, IF_NAMESIZE);
		if (setsockopt(socket, SOL_SOCKET, SO_BINDTODEVICE, (void *)&if_bind, sizeof(if_bind)) < 0)
		{
			ping_fatal("setsockopt", "failed to bind to device");
			return (-1);
		}
		if (setsockopt(socket, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
		{
			ping_fatal("setsockopt", "failed to configure socket");
			return (-1);
		}
		if (param->options & OPT_SO_DEBUG)
		{
			if (setsockopt(socket, IPPROTO_IP, SO_DEBUG, &on, sizeof(int)) < 0)
			{
				ping_fatal("setsockopt", "failed to set SO_DEBUG flag.");
				return (-1);
			}
		}
//		setsockopt(socket, SOL_IP, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
		return (0);
}