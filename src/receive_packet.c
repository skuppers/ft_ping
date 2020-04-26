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
	response_seq = ntohs(icmp->icmp_sequence);
	response_id = ntohs(icmp->icmp_identifier);
	if (response_code == 0)
	{
		if (response_seq != pm->sequence || response_id != getpid())
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

static int8_t			is_loopback_duplicate(uint16_t code)
{
	if (code == 8)
		return (1);
	return (0);
}

static void				discard_duplicate(t_runtime *runtime, uint8_t *pkt,
							t_meta *packetmeta)
{
	free(pkt);
	receive_packet(runtime, NULL, packetmeta->timer, packetmeta->sequence);
}

void					receive_packet(t_runtime *runtime, uint8_t *pkt,
							t_timer *tm, uint16_t sequence)
{
	t_meta				packetmeta;
	uint16_t			response_code;

	packetmeta.received_bytes = -1;
	packetmeta.sequence = sequence;
	packetmeta.timer = tm;
	pkt = (uint8_t *)ft_memalloc(MTU);
	while (g_signals->sigalrm == 0 && packetmeta.received_bytes <= 0)
		if ((packetmeta.received_bytes = recvfrom(runtime->socket,
			(void*)pkt, MTU, MSG_DONTWAIT, NULL,
			(socklen_t*)sizeof(struct sockaddr))) <= 0)
		{
		}
	if (packetmeta.received_bytes <= 0)
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
