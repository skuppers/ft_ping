/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 08:22:15 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/07 12:47:10 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

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

int ft_ping(t_data *param)
{
	int 			socket;
	t_icmppacket	*pkt;


	socket = createSocket();
	setSocketOptions(param, socket);

	pkt = forge_packet(param);


}
