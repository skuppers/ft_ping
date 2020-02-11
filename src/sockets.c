/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 08:22:15 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/07 14:52:32 by skuppers         ###   ########.fr       */
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