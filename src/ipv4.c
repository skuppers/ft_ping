/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipv4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:27:51 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:52:20 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

uint16_t		setup_message_body(t_data *param, char *data)
{
	int i;
	for (i = 0; i < param->pkt_size; i++)
		data[i] = 0x42;
	data[i] = '\0';
	return (i);
}
/*
void		setup_ipv6_header(void)
{

}

void		setup_icmpv6_header(void)  // Are they really different?
{

}
*/

void		setup_ipv4_header(t_runtime *runtime, struct ipv4_hdr *header,
								 uint16_t datalen)
{
	char	*src_addr;

	src_addr = ft_strnew(16);
	ft_memset(header,0, IP4_HDRLEN);
	header->ip_header_length = IP4_HDRLEN / sizeof(uint32_t);
	header->ip_version = 4;
	header->ip_tos = runtime->param->tos;
	header->ip_len = htons(IP4_HDRLEN + ICMP_HDRLEN + datalen);
	header->ip_id = htons(0);
	header->ip_frag_offset = htons(0);
	header->ip_ttl = runtime->param->ttl;
	header->ip_type = IPPROTO_ICMP;
	header->ip_checksum = 0;
	extract_ipaddr(runtime->param->interface->ifa_addr, src_addr, 16);
	inet_pton(AF_INET, src_addr, &(header->ip_src_addr));
	inet_pton(AF_INET, runtime->param->ipv4_str, &(header->ip_dst_addr));
	header->ip_checksum = ip_checksum((void *)header, IP4_HDRLEN);
}

void		setup_icmpv4_header(struct icmpv4_hdr *header, uint16_t sequence)
{
	ft_memset(header, 0, ICMP_HDRLEN);
	header->icmp_type = ICMP_ECHO;
	header->icmp_code = 0;
	header->icmp_identifier = htons(0x1234);
	header->icmp_sequence = htons(sequence);
}