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

static int8_t	configureSocket(int clientsocket, t_data *param)
{
	if (setsockopt(clientsocket, IPPROTO_IP, IP_TTL, &(param->ttl), sizeof(uint8_t)) < 0)
	{
		ping_fatal("setsockopt", "failed to configure ttl");
		return (-1);
	}
	if (setsockopt(clientsocket, IPPROTO_IP, IP_TOS, &(param->tos), sizeof(uint8_t)) < 0)
	{
		ping_fatal("setsockopt", "failed to configure Tos");
		return (-1);
	}
	if (param->options & OPT_SO_DEBUG)
	{
		int on = 1;
		if (setsockopt(clientsocket, IPPROTO_IP, SO_DEBUG, &on, sizeof(int)) < 0)
		{
			ping_fatal("setsockopt", "failed to set the SO_DEBUG flag");
			return (-1);
		}
	}
	return (0);
}

static int8_t	configureTimeouts(int clientsocket)
{
	struct timeval timeout;
		
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	if (setsockopt(clientsocket, SOL_IP, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout)) < 0)
	{
		ping_fatal("configureTimeouts","could no set snd timeout");
		return (-1);
	}
	if (setsockopt(clientsocket, SOL_IP, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) < 0)
	{
		ping_fatal("configureTimeouts","could no set recv timeout");
		return(-1);
	}
	return (0);
}

static int8_t bindToInterface(int clientsocket, struct ifreq *if_bind)
{
	if (setsockopt(clientsocket, SOL_SOCKET, SO_BINDTODEVICE, if_bind, sizeof(if_bind)) < 0)
	{
    	ping_fatal("bindToInterface","setsockopt() failed to bind to interface");
  		return(-1);
  	}
	return (0);
}

static int8_t	indexSocket(t_data *param, struct ifreq *if_bind)
{
	int		tempsocket;

	// This first socket is for indexing the interface w/ ioctl
	if ((tempsocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
   		ping_fatal("indexSocket","socket() failed");
  		return(-1);
	}
	
	ft_strncpy(if_bind->ifr_name, (const char*)param->interface,
		IF_NAMESIZE);

	if (ioctl(tempsocket, SIOCGIFINDEX, if_bind) < 0)
	{ 
		ping_fatal("indexSocket", "ioctl() failed to find interface");
		return (-1);
	}
	close(tempsocket);

	return (0);
}

int32_t	createSocket(t_data *param)
{
	int 			clientsocket;
	struct ifreq	if_bind;

	clientsocket = -1;
	memset(&if_bind, 0, sizeof(struct ifreq));
	if (indexSocket(param, &if_bind) != 0)
		return (-1);
	if ((clientsocket = socket (AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
   		ping_fatal("createsocket","socket() failed");
  		return(-1);
  	}
	if (configureSocket(clientsocket, param) != 0)
		return (-1);
	if (configureTimeouts(clientsocket) != 0)
		return (-1);
	if (bindToInterface(clientsocket, &if_bind) != 0)
		return (-1);
	return (clientsocket);
}