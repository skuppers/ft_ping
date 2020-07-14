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

uint16_t	setup_message_body(t_data *param, char *data)
{
	int		i;

	i = 0;
	while (i < param->pkt_size)
		data[i++] = 0x42;
	data[i] = '\0';
	return (i);
}

/*
**	HTONS
*/

void		setup_icmpv4_header(struct s_icmpv4_hdr *header, uint16_t sequence)
{
	ft_memset(header, 0, ICMP_HDRLEN);
	header->icmp_type = 8;
	header->icmp_code = 0;
	header->icmp_identifier = getpid();
	header->icmp_sequence = sequence;
}
