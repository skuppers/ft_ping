/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:17:44 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/07 12:46:33 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static uint16_t calcChecksum(void *pkt, size_t len)
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
		return (result);
}


t_icmppacket *forge_packet(t_data *param)
{
		t_icmppacket	*pkt;
		char			*msg;
		unsigned long	datafiller;

		pkt = ft_memalloc(param->pkt_size);
		pkt->header.type = ICMP_ECHO;
		pkt->header.un.echo.id = getpid();
		pkt->header.un.echo.sequence = 1;
		pkt->header.checksum = 0;
		datafiller = 0;
		while (datafiller < (param->pkt_size - sizeof(struct icmphdr)))
				pkt->msg[datafiller++] = '0';
		pkt->msg[datafiller] = 0;
		pkt->header.checksum = calcChecksum(pkt, sizeof(pkt));
		return (pkt);
}
