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
	uint16_t	packet_size;
	int16_t send_bytes = 0;

	if (runtime->param->options & OPT_IPV6)
		packet_size = 40;// + datalen + icmpv6?;
	else
	packet_size = ntohs((((struct ipv4_hdr*)packet)->ip_len));
	printf("Trying to send %u byte packet to socket %d\n", packet_size, runtime->socket);
	if ((send_bytes = sendto(runtime->socket, packet, packet_size,
				0, runtime->param->interface->ifa_addr,
				sizeof(struct sockaddr))) == -1
				|| send_bytes != packet_size)
	{
		printf("Error sending packet. Sendto()\n");
		printf("%s",strerror(errno));
		return (FAILURE);
	}
	printf("Sent %u bytes\n", send_bytes);
	//register_packet(); // add it to linked list
	return (SUCCESS);
}
