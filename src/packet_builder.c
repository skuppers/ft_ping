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

void	pkt_setsequence(t_icmppacket *pkt, int sequence)
{
		pkt->header.un.echo.sequence = sequence;
}

void	pkt_fix_checksum(t_icmppacket *packet, void *pkt, size_t len)
{
		unsigned short	*buf;				// for 16 bit casting
		unsigned int 	sum = 0;    		// 1's over sum
		uint16_t 		result;   			// checksum

		buf = pkt;
		for ( sum = 0; len > 1; len -= 2 )
				sum += *buf++;
		if ( len == 1 )
				sum += *(unsigned char*)buf;
		sum = (sum >> 16) + (sum & 0xFFFF);
		sum += (sum >> 16);
		result = ~sum;
		packet->header.checksum = result;
}

void			free_packet(t_icmppacket *pkt)
{
	ft_strdel(&(pkt->msg));
	free(pkt);
}

static void		setup_ip_hdr(struct ip_hdr *header)
{
	header->ip_version_and_header_length = IP4_HDRLEN;
}

uint8_t			*forge_packet(t_data *param, uint16_t total_length)
{
		uint8_t				*packet;
		struct ip_hdr		ip_header;
		struct icmp_hdr		icmp_header;

		packet = allocate_ucharlist(IP_MAXPACKET);

		setup_ip_hdr(&ip_header);
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
