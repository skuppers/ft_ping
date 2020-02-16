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
	struct icmpv4_hdr	icmp_header;
	struct ipv4_hdr		ip_header;
	uint16_t			datalen;

	datalen = setup_message_body(runtime->param, data);
	packet = ft_memalloc(IP4_HDRLEN + ICMP_HDRLEN + datalen);
	ft_memcpy(packet + IP4_HDRLEN + ICMP_HDRLEN, data, datalen);
	setup_icmpv4_header(runtime->param, &icmp_header, datalen, seq);
	ft_memcpy(packet + IP4_HDRLEN, &icmp_header, ICMP_HDRLEN);
	icmp_header.icmp_checksum = ip_checksum((void *)packet + IP4_HDRLEN, ICMP_HDRLEN + datalen);
	ft_memcpy(packet + IP4_HDRLEN, &icmp_header, ICMP_HDRLEN);
	setup_ipv4_header(runtime, &ip_header, datalen);
	ft_memcpy(packet, &ip_header, IP4_HDRLEN);
	return (packet);
}

static uint8_t			*forge_ipv6(t_runtime *runtime, uint8_t *pkt, uint16_t seq)
{
/*	setup_ipv6_header();
 *	setup_icmpv6_header();
 *	setup_message_body();
 */
	return (0);
}

uint8_t			*forge_packet(t_runtime *runtime, uint8_t *pkt, uint16_t seq)
{
		if (runtime->param->options & OPT_IPV4)
			pkt = forge_ipv4(runtime, pkt, seq);
		else if (runtime->param->options & OPT_IPV6)
			pkt = forge_ipv6(runtime, pkt, seq);
	return (pkt);
}
