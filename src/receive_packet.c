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

void					handle_response(t_runtime *rt, uint8_t *pkt,
							t_meta *pm)
{
	int8_t				response_code;
	int					response_seq;
	int					response_id;
	struct s_icmpv4_hdr	*icmp;

	icmp = (struct s_icmpv4_hdr *)(pkt + sizeof(struct s_ipv4_hdr));
	response_code = icmp->icmp_type;
	response_seq = icmp->icmp_sequence;
	response_id = icmp->icmp_identifier;
	if (response_code == 0)
	{
		if (response_seq != pm->sequence)
			id_seq_mismatch(rt, pkt, pm->timer, pm->sequence);
		else
			resp_code_zero(rt, pkt, pm);
	}
	else if (response_code == 11)
		resp_code_eleven(rt, pkt, pm);
	else if (response_code == 3)
		resp_code_three(rt, pkt, pm);
	else
		resp_code_unknown(rt, pkt, pm);
}

static void				handle_timeout(t_runtime *runtime, uint8_t *pkt,
							t_meta *packetmeta)
{
	free(pkt);
	register_response(runtime, NULL, 0, packetmeta->timer);
}

static void				discard_duplicate(t_runtime *runtime, uint8_t *pkt,
							t_meta *packetmeta)
{
	free(pkt);
	receive_packet(runtime, NULL, packetmeta->timer, packetmeta->sequence);
}

void					prep_msg(struct msghdr *msg, struct iovec *iov,
							uint8_t *pkt)
{
	iov[0].iov_len = MTU;
	iov[0].iov_base = (char *)pkt;
	msg->msg_iov = iov;
	msg->msg_iovlen = 1;
	msg->msg_name = NULL;
	msg->msg_namelen = 0;
	msg->msg_flags = 0;
}

void					receive_packet(t_runtime *runtime, uint8_t *pkt,
							t_timer *tm, uint16_t sequence)
{
	t_meta				packetmeta;
	struct msghdr		msg;
	struct iovec		iov[1];
	uint16_t			response_code;

	pkt = (uint8_t *)ft_memalloc(MTU);
	ft_memset(&msg, '\0', sizeof(msg));
	prep_meta(sequence, &packetmeta, tm);
	prep_msg(&msg, iov, pkt);
	while (g_signals->sigalrm == 0 && packetmeta.r_bts <= 0)
		if ((packetmeta.r_bts = recvmsg(runtime->socket, &msg, 0x40)) <= 0)
			;
	if (packetmeta.r_bts <= 0)
		handle_timeout(runtime, pkt, &packetmeta);
	else
	{
		gettimeofday(&(tm->recv), NULL);
		response_code = ((struct s_icmpv4_hdr *)(pkt + IP4_HDRLEN))->icmp_type;
		if (is_loopback_duplicate(response_code))
			discard_duplicate(runtime, pkt, &packetmeta);
		else
			handle_response(runtime, pkt, &packetmeta);
	}
	alarm(0);
}
