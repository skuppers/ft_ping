/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:17:44 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 18:05:41 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static uint32_t			forge_ipv4(t_runtime *runtime, uint8_t packet,
									uint32_t seq)
{
	struct ipv4_hdr		ip_header;
	struct icmp_hdr		icmp_header;
	char				*data;
	uint32_t			datalen;

	setup_ipv4_header(runtime, &ip_header);
	setup_icmpv4_header(runtime, &icmp_header);
	setup_message_body(runtime);
}

static uint32_t			forge_ipv6()
{
	setup_ipv6_header();
	setup_icmpv6_header();
	setup_message_body();
}

uint8_t			*forge_packet(t_runtime *runtime, uint8_t *pkt, uint32_t seq)
{
	uint32_t	packet_length;

		if (param->options & OPT_IPV4)
			packet_length = forge_ipv4(runtime, pkt, seq);

		else if (param->options & OPT_IPV6)
			packet_length = forge_ipv6(runtime, pkt, seq);

//		packet = allocate_ucharlist(IP_MAXPACKET); // 65535, really?
/*		unsigned long	datafiller;
		datafiller = 0;
		while (datafiller < (param->pkt_size))
				pkt->msg[datafiller++] = 'a' + datafiller;
		pkt->msg[datafiller] = 0;
*/
		return (SUCCESS);
}
