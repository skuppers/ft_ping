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
	int 			clientsocket;
	struct ifreq	if_bind;

	if (param->options & OPT_IPV4)
	{
		if ((clientsocket = socket (AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
  		{
    		perror ("socket() failed ");
    		exit (EXIT_FAILURE);
 		 }
		memset(&if_bind, 0, sizeof(struct ifreq));
		ft_strncpy(if_bind.ifr_name, (const char*)param->interface->ifa_name,
			IF_NAMESIZE);
		if (ioctl (clientsocket, SIOCGIFINDEX, &if_bind) < 0)
  			 perror ("ioctl() failed to find interface\n");
		close(clientsocket);

		if ((clientsocket = socket (AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
   			perror ("socket() failed ");
    		exit (EXIT_FAILURE);
  		}

		if (setsockopt(clientsocket, IPPROTO_IP, IP_TTL, &(param->ttl), sizeof(uint8_t)) < 0)
		{
			ping_fatal("setsockopt", "failed to configure ttl socket");
			return (-1);
		}
		if (setsockopt(clientsocket, IPPROTO_IP, IP_TOS, &(param->tos), sizeof(uint8_t)) < 0)
		{
			ping_fatal("setsockopt", "failed to configure ttl socket");
			return (-1);
		}
		if (param->options & OPT_SO_DEBUG)
		{
			int on = 1;
			if (setsockopt(clientsocket, IPPROTO_IP, SO_DEBUG, &on, sizeof(int)) < 0)
			{
				ping_fatal("setsockopt", "failed to set SO_DEBUG flag.");
				return (-1);
			}
		}
		struct timeval timeout;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		if (setsockopt(clientsocket, SOL_IP, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout)) < 0)
			printf("could no set send timeout\n");
		if (setsockopt(clientsocket, SOL_IP, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) < 0)
			printf("could no set recv timeout\n");

		if (setsockopt (clientsocket, SOL_SOCKET, SO_BINDTODEVICE, &if_bind, sizeof (if_bind)) < 0)
		{
    		perror ("setsockopt() failed to bind to interface ");
    		exit (EXIT_FAILURE);
  		}	
		return (clientsocket);
	}
	if ((clientsocket = socket(PF_INET6, SOCK_RAW, IPPROTO_RAW)) < 0)
	{
		ping_fatal("createSocket()", "Could not create raw ipv6 socket. Are you root?");
		return (-1);
	}
	return (clientsocket);
}