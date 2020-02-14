/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:17:44 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 14:59:09 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void			free_packet(t_icmppacket *pkt)
{
	ft_strdel(&(pkt->msg));
	free(pkt);
}

static void		setup_ip_hdr(struct ip_hdr *header, uint16_t datalen, t_data *param)
{
	int		ip_flags[4];

	header->ip_header_length = IP4_HDRLEN / sizeof(uint32_t);
	header->ip_version = 4;
	header->ip_tos = 0;
	header->ip_len = htons(IP4_HDRLEN + ICMP_HDRLEN + datalen);
	header->ip_id = htons(0);

	ip_flags[0] = 0; // Zero
	ip_flags[1] = 0; // Do notfrag bit
	ip_flags[2] = 0; // Fragment following bit
	ip_flags[3] = 0; // Fragemntation offset
	header->ip_frag_offset = htons((ip_flags[0] << 15)
								 + (ip_flags[1] << 14)
								 + (ip_flags[2] << 13)
								 + (ip_flags[3]));
	header->ip_ttl = BASE_TTL;
	header->ip_type = IPPROTO_ICMP;
	//if (inet_pton(AF_INET, param->))
}

uint8_t			*forge_packet(t_data *param, uint16_t data_len)
{
		uint8_t				*packet;
		struct ip_hdr		ip_header;
		struct icmp_hdr		icmp_header;

		packet = allocate_ucharlist(IP_MAXPACKET);

		setup_ip_hdr(&ip_header, data_len, param);
		setup_icmp_hdr(&icmp_header);


		unsigned long	datafiller;

		pkt = ft_memalloc(8);
		pkt->msg = ft_strnew(param->pkt_size);
		pkt->header.type = ICMP_ECHO;
		pkt->header.un.echo.id = getpid();
		pkt->header.un.echo.sequence = 0;
		pkt->header.checksum = 0;
		datafiller = 0;
		while (datafiller < (param->pkt_size))
				pkt->msg[datafiller++] = 'a' + datafiller;
		pkt->msg[datafiller] = 0;
		return (pkt);
}
