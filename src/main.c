/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:01 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/07 15:49:21 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_usage(void)
{
		printf("usage: ft_ping [-ovh] [-c count] [-m ttl]\
						[-S src_address] [-s packetsize] host\n");
}

void	init_param(t_data *param)
{
		param->options = 0;
		param->ttl = 64;
		param->count = 0;
		param->src_address = 0;
		param->pkt_size = 64;
		param->fqdn = NULL;
		param->hostname = NULL;
		param->host = NULL;
}

int		main(int ac, char **av)
{
		t_data	param;

		if (ac < 2)
		{
				print_usage();
				return(42);
		}

		init_param(&param);
		if (parse_opt(ac, av, &param) != 0)
				return (42);

		resolve_fqdn(&param);

		//	printf("\nPING OPTIONS:\n");
		//	printf("TTL: %d\n", param.ttl);
		//	printf("Count: %d\n", param.count);
		//	printf("Src address: %d\n", param.src_address);
		//	printf("Packet size: %d\n", param.pkt_size);
		//	printf("Host/FQDN: %s\n", param.fqdn);
		//	printf("Host IP: %s\n\n", param.hostname);

		int socket = createSocket();
		setSocketOptions(&param, socket);

		t_icmppacket *icmp_pkt;
		icmp_pkt = forge_packet(&param);



		char buffer[548];
		struct sockaddr_storage src_addr;

		struct iovec iov[1];
		iov[0].iov_base=buffer;
		iov[0].iov_len=sizeof(buffer);

		struct msghdr message;
		message.msg_name=&src_addr;
		message.msg_namelen=sizeof(src_addr);
		message.msg_iov=iov;
		message.msg_iovlen=1;
		message.msg_control=0;
		message.msg_controllen=0;

#include <sys/time.h>
		struct timeval a;
		struct timezone z;

		int i = gettimeofday(&a, &z);
		printf("Time sending (%d): | %ld | %d |\n", i, a.tv_sec, a.tv_usec);

		send_packet(&param, socket, icmp_pkt);

		ssize_t count = recvmsg(socket, &message, 0);
		if (count==-1) {
				printf("Fatal error zith recvmsg.\n");
				exit(42);
		} else if (message.msg_flags & MSG_TRUNC) {
				printf("datagram too large for buffer: truncated.\n");
		} else {
//				handle_datagram(buffer,count);
				printf("Received related datagram.\n");
				int i = gettimeofday(&a, &z);
				printf("Time received (%d): | %ld | %d |\n", i, a.tv_sec, a.tv_usec);

		}
		//
		//	calc RTT


//		print_resolve(&param);
//		print_ping(&param);
//		sleep(1);
//		print_ping(&param);
//		sleep(1);
//		print_ping(&param);
//		print_stats(&param);

		return (0);
}
