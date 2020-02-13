/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sockets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:26:15 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 10:26:17 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "ft_ping.h"

int send_packet(t_data *param, int socket, t_icmppacket *pkt)
{
	if (sendto(socket, pkt, HDR_SZ + ft_strlen(pkt->msg), 0, param->host, param->hostlen) == -1)
	{
		printf("Error sending datagram. (sendto)\n");
	}
}

int		receive_packet(struct msghdr *msg, int socket)
{
	int count;

	if ((count = recvmsg(socket, msg, 0)) == -1)
	{
		printf("Fatal error zoth recvmsg.\n");
		return (-1);
	}
	else if (msg->msg_flags & MSG_TRUNC)
	{
		printf("Message truncated.\n");
		return (-1);
	}
	printf("Received related datagram.\n");
	return (0);
}

int	createSocket(void)
{
		int clientsocket;

		clientsocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
		if (clientsocket == -1)
		{
				printf("Error creating socket. Are you root?\n");
				exit(42);
		}
		return (clientsocket);
}

int setSocketOptions(t_data *param, int socket)
{
		setsockopt(socket, SOL_IP, IP_TTL, &(param->ttl), sizeof(param->ttl));
		//	setsockopt(socket, SOL_IP, SO_RCVTIMEOUT, &(param));
		return (0);
}
