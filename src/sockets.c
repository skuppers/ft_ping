/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sockets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:26:15 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 18:08:47 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int32_t	createSocket(void)
{
		int clientsocket;

		if (!(clientsocket = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
			return (clientsocket);
		ping_fatal("createSocket()", "undefined");
		return (-1);
}

int8_t setSocketOptions(t_data *param, int socket)
{
		int32_t	on;

		on = 1;
		if (setsockopt(socket, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
		{
			ping_fatal("setsockopt", "failed to configure socket");
			return (-1);
		}
//		setsockopt(socket, SOL_IP, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
		return (0);
}



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
	param->timeout = 0;
	alarm(1);

	// Handle count in display

	count = recvmsg(socket, &message, MSG_DONTWAIT);
	while (param->timeout == 0 && param->sigint == 0)
		count = recvmsg(socket, &message, MSG_DONTWAIT);
	alarm(0);
	if (count == -1)
		return (-1);
	param->pkt_recvd++;
	return (0);
}


