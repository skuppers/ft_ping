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

static uint16_t			forge_ipv4(t_runtime *runtime, uint8_t *packet,
									uint32_t seq)
{
	struct ipv4_hdr		ip_header;
	struct icmp_hdr		icmp_header;
	char				data[65535];
	uint16_t			datalen;

	datalen = setup_message_body(runtime->param, data);
	setup_icmpv4_header(runtime->param, &icmp_header);
	setup_ipv4_header(runtime, &ip_header, datalen);

//	icmp_checksum(&icmp_header, datalen);
//	ip_checksum(&ip_header, ICMP_HDRLEN + datalen);

	packet = ft_memalloc(IP4_HDRLEN + ICMP_HDRLEN + datalen);
	ft_memcpy(packet, &ip_header, IP4_HDRLEN);
	ft_memcpy(packet + IP4_HDRLEN, &icmp_header, ICMP_HDRLEN);
	ft_memcpy(packet + IP4_HDRLEN + ICMP_HDRLEN, data, datalen);

	return (IP4_HDRLEN + ICMP_HDRLEN + datalen);
}

static uint32_t			forge_ipv6(t_runtime *runtime, uint8_t *pkt, uint16_t seq)
{
/*	setup_ipv6_header();
 *	setup_icmpv6_header();
 *	setup_message_body();
 */
	return (0);
}

uint16_t			forge_packet(t_runtime *runtime, uint8_t *pkt, uint16_t seq)
{
	uint16_t	packet_length;

		if (runtime->param->options & OPT_IPV4)
			packet_length = forge_ipv4(runtime, pkt, seq);
		else if (runtime->param->options & OPT_IPV6)
			packet_length = forge_ipv6(runtime, pkt, seq);
	return (packet_length);
}
