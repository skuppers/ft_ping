/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sockets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:26:15 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 16:08:03 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "ft_ping.h"

int send_packet(t_data *param, int socket, t_icmppacket *pkt)
{
	if (sendto(socket, pkt, HDR_SZ + ft_strlen(pkt->msg),
							0, param->host, param->hostlen) == -1)
		printf("Error sending datagram. (sendto)\n");
	else
		param->pkt_send++;
}

int		receive_packet(t_data *param, int socket)
{
	int 					count;
	struct msghdr			message;
	struct iovec 			iov[1];
	char 					buffer[1500];
	struct sockaddr_storage src_addr;

	iov[0].iov_base = buffer;
	iov[0].iov_len = IOV_BUFFER_SZ;
	message.msg_name = &src_addr;
	message.msg_namelen = sizeof(src_addr);
	message.msg_iov = iov;
	message.msg_iovlen = 1;
	message.msg_control = 0;
	message.msg_controllen = 0;
	if ((count = recvmsg(socket, &message, 0)) == -1)
		return (-1);
	else if (message.msg_flags & MSG_TRUNC)
		return (42);
	param->pkt_recvd++;
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
		struct timeval timeout;

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		setsockopt(socket, SOL_IP, IP_TTL, &(param->ttl), sizeof(param->ttl));
		setsockopt(socket, SOL_IP, SO_RCVTIMEO, &timeout, sizeof(timeout));
		return (0);
}
