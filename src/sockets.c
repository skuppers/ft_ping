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

//	if (param->options & OPT_IPV4)
		if (!(clientsocket = socket(AF_INET, SOCK_RAW, IPPROTO_RAW) < 0))
			return (clientsocket);
//	if (!(clientsocket = socket(AF_INET6, SOCK_RAW, IPPROTO_RAW) < 0))
//		return (clientsocket);
	ping_fatal("createSocket()", "Could not create raw socket. Are you root?");
	return (-1);
}

int8_t setSocketOptions(t_data *param, int socket)
{
		int32_t	on;
		struct ifreq	ifr;

		on = 1;
		memset(&ifr, 0, sizeof(ifr));
		snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "ens33");
		if (setsockopt(socket, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0)
		{
			ping_fatal("setsockopt", "failed to bind to device");
			if (errno == ENOTSOCK)
				printf("not a socket??\n");
			printf("%s\n", strerror(errno));
			return (-1);
		}
		if (setsockopt(socket, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
		{
			ping_fatal("setsockopt", "failed to configure socket");
			return (-1);
		}
		if (param->options & OPT_SO_DEBUG)
			if (setsockopt(socket, IPPROTO_IP, SO_DEBUG, &on, sizeof(int)) < 0)
			{
				ping_fatal("setsockopt", "failed to set SO_DEBUG flag.");
				return (-1);
			}
//		setsockopt(socket, SOL_IP, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
		return (0);
}