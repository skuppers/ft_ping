/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_packet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:53:48 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 18:04:58 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_packetlist	*pktlstnew(uint8_t *packet, size_t size, t_timer *timer)
{
	t_packetlist	*pktlst;

	pktlst = ft_memalloc(sizeof(t_packetlist));
	pktlst->data = packet;
	pktlst->data_size = size;
	pktlst->rtt = plot_timer(timer);
	return (pktlst);
}

static void		register_response(t_runtime *runtime, uint8_t *packet, ssize_t size,
								t_timer *timer)
{
	t_list			*data;

	if (packet != NULL && size > 0)
		data = ft_lstnew(pktlstnew(packet, (size_t) size, timer), sizeof(t_packetlist));
	else
		data = ft_lstnew(NULL, 0);
	if (runtime->rpacketlist_head == NULL)
		runtime->rpacketlist_head = data;
	else
		ft_lstadd(&runtime->rpacketlist_head, data);
}

void	receive_packet(t_runtime *runtime, uint8_t *pkt, t_timer *tm)
{
	int32_t	recvd_bytes;

	recvd_bytes = -1;
	pkt = (uint8_t *)ft_memalloc(1500);
	while (g_signals->sigalrm == 0 && recvd_bytes <= 0)
		if ((recvd_bytes = recvfrom (runtime->socket, (void*)pkt, 1500,
				MSG_DONTWAIT, NULL, (socklen_t*)sizeof (struct sockaddr))) <= 0)
		{ }
	alarm(0);
	if (recvd_bytes <= 0)
	{
		print_timeout(runtime, pkt);
		register_response(runtime, NULL, 0, tm);
	}
	else
	{
		if (gettimeofday(&(tm->recv), NULL) < 0)
			printf("Error getting time of day\n");
		print_ping(runtime->param, pkt, tm);
		register_response(runtime, pkt, recvd_bytes, tm);
	}
}
/*
		if (runtime->param->options & OPT_TIMESTAMP)
			printf("[timestamp] ");
		
		char *src = ft_strnew(16);
		inet_ntop(AF_INET, &((struct ipv4_hdr *)pkt)->ip_src, src, 16);
		struct icmpv4_hdr *icmp =  (struct icmpv4_hdr *)(pkt + sizeof(struct ipv4_hdr));

		printf("%u bytes from %s: icmp_seq=%u ttl=%u time= ms\n",
			ntohs(((struct ipv4_hdr *)pkt)->ip_len) - IP4_HDRLEN,
			src,
			ntohs(icmp->icmp_sequence),
			((struct ipv4_hdr *)pkt)->ip_ttl);

		printf("\nReceived a %u bytes ipv4 packet\n", ntohs(((struct ipv4_hdr *)pkt)->ip_len));
		printf(" ----------------- \n");
		printf("hdr->hdr_len:\t%u\n", ((struct ipv4_hdr *)pkt)->ip_header_length);
		printf("hdr->version:\t%u\n", ((struct ipv4_hdr *)pkt)->ip_version);
		printf("hdr->tos    :\t%u\n", ((struct ipv4_hdr *)pkt)->ip_tos);
		printf("hdr->len    :\t%u\n", ntohs(((struct ipv4_hdr *)pkt)->ip_len));
		printf("hdr->id      :\t%u\n", ntohs(((struct ipv4_hdr *)pkt)->ip_id));
		printf("hdr->ttl     :\t%u\n", ((struct ipv4_hdr *)pkt)->ip_ttl);
		printf("hdr->type    :\t%u\n", ((struct ipv4_hdr *)pkt)->ip_type);
		printf("hdr->checksum:\t%x\n", ((struct ipv4_hdr *)pkt)->ip_checksum);
		char *src = ft_strnew(16);
		inet_ntop(AF_INET, &((struct ipv4_hdr *)pkt)->ip_src, src, 16);
		printf("hdr->src	 :\t%s\n", src);
		char *dst = ft_strnew(16);
		inet_ntop(AF_INET, &((struct ipv4_hdr *)pkt)->ip_dst, dst, 16);
		printf("hdr->dst	 :\t%s\n", dst);
		printf(" ----------------- \n");
		
		printf("icmp->type     :\t%u\n", ((struct icmpv4_hdr *)pkt + IP4_HDRLEN)->icmp_type);
		printf("icmp->code    :\t%u\n", ((struct icmpv4_hdr *)pkt + IP4_HDRLEN)->icmp_code);
		printf("icmp->seq     :\t%u\n", ntohs(icmp->icmp_sequence));
		printf("icmp->id      :\t%u\n", ntohs(icmp->icmp_identifier));
		printf(" ----------------- \n\n");
*/