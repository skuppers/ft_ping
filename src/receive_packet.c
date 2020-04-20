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

static t_packetdata	*pktdatanew(uint8_t *packet, size_t size, t_timer *timer)
{
	t_packetdata	*pktdata;

	pktdata = ft_memalloc(sizeof(t_packetdata));
	pktdata->data = packet;
	pktdata->data_size = size;
	if (timer == NULL)
		pktdata->rtt = -42.0;
	else
		pktdata->rtt = plot_timer(timer);
	return (pktdata);
}

static void		register_response(t_runtime *runtime, uint8_t *packet, ssize_t size,
								t_timer *timer)
{
	t_list			*data;
	t_packetdata	*packetdata;

	if (packet != NULL && size > 0)
	{
		packetdata = pktdatanew(packet, (size_t) size, timer);
		data = ft_lstnew(packetdata, sizeof(t_packetdata));
		free(packetdata);
	}
	else
		data = ft_lstnew(NULL, 0);
	if (runtime->rpacketlist_head == NULL)
		runtime->rpacketlist_head = data;
	else
		ft_lstadd(&runtime->rpacketlist_head, data);
}

/*
uint8_t check_response(uint8_t *pkt)
{	
		struct icmpv4_hdr *icmp =  (struct icmpv4_hdr *)(pkt + sizeof(struct ipv4_hdr));

		printf("%u bytes from %s: icmp_seq=%u ttl=%u time= ms\n",
			ntohs(((struct ipv4_hdr *)pkt)->ip_len) - IP4_HDRLEN,
			src,
			ntohs(icmp->icmp_sequence),
			((struct ipv4_hdr *)pkt)->ip_ttl);

		printf("\nReceived a %u bytes IPv4 packet\n", ntohs(((struct ipv4_hdr *)pkt)->ip_len));
		printf(" ----------------- \n");
		printf("hdr->hdr_len:\t%u\n", ((struct ipv4_hdr *)pkt)->ip_header_length);
		printf("hdr->version:\t%u\n", ((struct ipv4_hdr *)pkt)->ip_version);
		printf("hdr->tos    :\t%u\n", ((struct ipv4_hdr *)pkt)->ip_tos);
		printf("hdr->len    :\t%u\n", ntohs(((struct ipv4_hdr *)pkt)->ip_len));
		printf("hdr->id      :\t%u\n", ntohs(((struct ipv4_hdr *)pkt)->ip_id));
		printf("hdr->ttl     :\t%u\n", ((struct ipv4_hdr *)pkt)->ip_ttl);
		printf("hdr->type    :\t%u\n", ((struct ipv4_hdr *)pkt)->ip_type);
		printf("hdr->checksum:\t%x\n", ((struct ipv4_hdr *)pkt)->ip_checksum);
		char *srcs = ft_strnew(16);
		inet_ntop(AF_INET, &((struct ipv4_hdr *)pkt)->ip_src, srcs, 16);
		printf("hdr->src	 :\t%s\n", srcs);
		char *dst = ft_strnew(16);
		inet_ntop(AF_INET, &((struct ipv4_hdr *)pkt)->ip_dst, dst, 16);
		printf("hdr->dst	 :\t%s\n", dst);
		printf(" ----------------- \n");
		
		printf("icmp->type     :\t%u\n", ((struct icmpv4_hdr *)(pkt + IP4_HDRLEN))->icmp_type);
		printf("icmp->code    :\t%u\n", ((struct icmpv4_hdr *)(pkt + IP4_HDRLEN))->icmp_code);
		printf("icmp->seq     :\t%u\n", ntohs(icmp->icmp_sequence));
		printf("icmp->id      :\t%u\n", ntohs(icmp->icmp_identifier));
		printf(" ----------------- \n\n");
		return (0);
}
*/
void	handle_response(t_runtime *rt, uint8_t *pkt, t_timer *tm,
							uint8_t recvd_bytes, uint16_t sequence)
{
	int8_t	response_code;
	struct icmpv4_hdr *icmp =  (struct icmpv4_hdr *)(pkt + sizeof(struct ipv4_hdr));

	response_code = ((struct icmpv4_hdr *)(pkt + IP4_HDRLEN))->icmp_type;
	int response_seq = ntohs(icmp->icmp_sequence);
	int response_id = ntohs(icmp->icmp_identifier);

	if (response_seq != sequence || response_id != getpid())
	{
		print_timeout(rt, pkt, sequence);
		free(pkt);
		if (g_signals->sigalrm == 0 && g_signals->sigint == 0)
			receive_packet(rt, pkt, tm, sequence);
		else
			register_response(rt, NULL, 0, tm);
	}
	else if (response_code == 0)
	{
		if (!(rt->param->options & OPT_QUIET))
			print_ping(rt->param, pkt, tm, sequence);
		register_response(rt, pkt, recvd_bytes, tm);
	}
	else if (response_code == 11)
	{
		if (!(rt->param->options & OPT_QUIET))
			print_ttl_exceeded(pkt, sequence);
		register_response(rt, pkt, recvd_bytes, NULL);
	}
	else if (response_code == 3)
	{
		if (!(rt->param->options & OPT_QUIET))
			print_unreachable(pkt, sequence);
		register_response(rt, pkt, recvd_bytes, NULL);
	} 
	else
	{
		if (!(rt->param->options & OPT_QUIET))
			print_unknown(pkt, sequence);
		register_response(rt, pkt, recvd_bytes, NULL);
	}
}

void	receive_packet(t_runtime *runtime, uint8_t *pkt,
							t_timer *tm, uint16_t sequence)
{
	int32_t	recvd_bytes;
	uint16_t response_code;

	recvd_bytes = -1;
	pkt = (uint8_t *)ft_memalloc(MTU);
	while (g_signals->sigalrm == 0 && recvd_bytes <= 0)
		if ((recvd_bytes = recvfrom(runtime->socket, (void*)pkt, MTU,
				MSG_DONTWAIT, NULL, (socklen_t*)sizeof (struct sockaddr))) <= 0)
		{ }
	alarm(0);
	if (recvd_bytes <= 0)
	{
		print_timeout(runtime, pkt, sequence);
		free(pkt);
		register_response(runtime, NULL, 0, tm);
	}
	else
	{
		if (gettimeofday(&(tm->recv), NULL) < 0)
		{ }
		response_code = ((struct icmpv4_hdr *)(pkt + IP4_HDRLEN))->icmp_type;
		if (response_code == 8 && ft_strequ(runtime->param->interface, "lo"))
		{
			free(pkt);
			receive_packet(runtime, pkt, tm, sequence);
		}
		else
			handle_response(runtime, pkt, tm, recvd_bytes, sequence);
	}
}