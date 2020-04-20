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

static uint8_t			*forge_ipv4(t_runtime *runtime, uint8_t *packet,
									uint32_t seq)
{
	char				data[65535];
	struct s_icmpv4_hdr	icmp_header;
	uint16_t			datalen;

	datalen = setup_message_body(runtime->param, data);
	packet = ft_memalloc(ICMP_HDRLEN + datalen);
	setup_icmpv4_header(&icmp_header, seq);
	ft_memcpy(packet, &icmp_header, ICMP_HDRLEN);
	ft_memcpy(packet + ICMP_HDRLEN, data, datalen);
	icmp_header.icmp_checksum = ip_checksum((void *)packet,
		ICMP_HDRLEN + datalen);
	ft_memcpy(packet, &icmp_header, ICMP_HDRLEN);
	return (packet);
}

uint8_t					*forge_packet(t_runtime *runtime,
							uint8_t *pkt, uint16_t seq)
{
	pkt = forge_ipv4(runtime, pkt, seq);
	return (pkt);
}
