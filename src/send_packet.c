/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_packet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:10:16 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:25:56 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int8_t		send_packet(t_runtime *runtime, uint8_t *packet)
{
	size_t	packet_size;

	if (runtime->param->options & OPT_IPV6)
		packet_size = IP6_HDR;// + datalen + icmpv6?;
	else
		packet_size = ((struct ipv4_hdr*)packet)->ip_len;

	if (sendto(runtime->param->socket, packet, packet_size,
				0, runtime->param->host, runtime->param->hostlen) == -1)
	{
		printf("Error sending packet. Sendto()\n");
		return (FAILURE);
	}
	register_packet(); // add it to linked list
	return (SUCCESS);
}
