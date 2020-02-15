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

void		setup_ipv6_header()
{

}

void		setup_icmpv6_header()  // Are they really different?
{

}

void		setup_ipv4_header(t_runtime *runtime)
{
	int		ip_flags[4];

	header->ip_header_length = IP4_HDRLEN / sizeof(uint32_t);
	header->ip_version = 4;
//	header->ip_tos = 0;
//	header->ip_len = htons(IP4_HDRLEN + ICMP_HDRLEN + datalen);
//	header->ip_id = htons(0);

	ip_flags[0] = 0; // Zero
	ip_flags[1] = 0; // Do notfrag bit
	ip_flags[2] = 0; // Fragment following bit
	ip_flags[3] = 0; // Fragemntation offset
	header->ip_frag_offset = htons((ip_flags[0] << 15)
								 + (ip_flags[1] << 14)
								 + (ip_flags[2] << 13)
								 + (ip_flags[3]));
//	header->ip_ttl = BASE_TTL;
	header->ip_type = IPPROTO_ICMP;


}

void		setup_icmpv4_header()
{
		pkt = ft_memalloc(8);
		pkt->msg = ft_strnew(param->pkt_size);
		pkt->header.type = ICMP_ECHO;
		pkt->header.un.echo.id = getpid();
		pkt->header.un.echo.sequence = 0;
		pkt->header.checksum = 0;
}
