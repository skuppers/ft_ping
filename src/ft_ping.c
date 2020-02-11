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

void	prep_response(struct msghdr *mess, int socket)
{

	char 					buffer[1500];
	struct iovec 			iov[1];
	struct msghdr			message;
	struct sockaddr_storage src_addr;
	ssize_t					count;
	
	iov[0].iov_base = buffer;
	iov[0].iov_len = sizeof(buffer);
	message.msg_name = &src_addr;
	message.msg_namelen = sizeof(src_addr);
	message.msg_iov = iov;
	message.msg_iovlen = 1;
	message.msg_control = 0;
	message.msg_controllen = 0;
	count = recvmsg(socket, &message, 0);
	perror("recvmsg: ");

		if (count == -1) 
		{
				printf("Fatal error with recvmsg.\n");
				exit(42);
		}
		else if (message.msg_flags & MSG_TRUNC) 
		{
				printf("Datagram too large for buffer: truncated.\n");
		}
		else
		{
//				handle_datagram(buffer,count);
				printf("Received related datagram.");
				//int i = gettimeofday(&a, &z);
				//printf(" | %ld | %d |\n", a.tv_sec, a.tv_usec);
		}
		pg_timer(1);
}

void	ping_while(t_data *param, int socket)
{
	int 			i;

	struct timeval	a;
	struct timezone z;
//	int				time;

	t_icmppacket	*icmp_pkt;
//	struct msghdr	response;
	

	i = 0;
	while (i < param->count && param->sigint == 0)
	{
		icmp_pkt = forge_packet(param);
		pkt_setsequence(icmp_pkt, i + 1);
		icmp_pkt->header.checksum = pkt_checksum(icmp_pkt, 8 + param->pkt_size); //check this
		
//		prep_response(&message);

	//	alarm(1);
		gettimeofday(&a, &z);
		printf("Time sending (%d): | %ld | %d | --- ", i, a.tv_sec, a.tv_usec);

		send_packet(param, socket, icmp_pkt);

		prep_response(NULL, socket);

		if (param->timeout != 0)
		{
			printf("Request timeout. \n");
			alarm(0);
			return ;
		}
	
		++i;
	}
}

int ft_ping(t_data *param)
{
	int socket;


	socket = createSocket();
	setSocketOptions(param, socket);

	//if (param->options & OPT_FLOOD)
	//	ping_flood();

	//else if (param->count != 0)
		ping_while(param, socket);

	//else
	//	ping_loop(param, socket);

	return (0);
}
