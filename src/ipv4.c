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
	return (0);
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
	ft_memset(header,0, IP4_HDRLEN);
	header->ip_header_length = IP4_HDRLEN / sizeof(uint32_t);
	header->ip_version = 4;
	header->ip_tos = runtime->param->tos;
	header->ip_len = htons(IP4_HDRLEN + ICMP_HDRLEN + datalen);
	header->ip_id = htons(getpid());
	header->ip_frag_offset = htons(0);
	header->ip_ttl = runtime->param->ttl;
	header->ip_type = IPPROTO_ICMP;
	header->ip_checksum = 0;
//	if (inet_pton(AF_INET, runtime->param->interface->ifa_addr, header->ip_src_addr) < 0)
//		printf("fuckd up bro");
//	if (inet_pton(AF_INET, runtime->param->ipv4_str, header->ip_dst_addr) < 0)
//		printf("fuckd up bro");
}

void		setup_icmpv4_header(t_data *param, struct icmp_hdr *header)
{
	memset(header, 0, ICMP_HDRLEN);
	header->icmp_type = ICMP_ECHO;
	header->icmp_code = 0;
	header->icmp_checksum = 0;
	header->icmp_identifier = getpid();
	header->icmp_sequence = 0;
}