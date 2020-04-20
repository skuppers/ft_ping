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

int8_t		send_packet(t_runtime *runtime, uint8_t *packet, t_timer *tv)
{
	int16_t	sent_bytes;
	size_t	packet_size;

	packet_size = ICMP_HDRLEN + runtime->param->pkt_size;
	if ((sent_bytes = sendto(runtime->socket, packet, packet_size, 0,
		(struct sockaddr *)runtime->param->sin, sizeof(struct sockaddr))) < 0)
	{
		ping_fatal("send_packet", "sendto() failed");
		exit(EXIT_FAILURE);
	}
	free(packet);
	if (gettimeofday(&(tv->send), NULL) < 0)
		printf("Error getting timeofday()\n");
	alarm(1);
	return (SUCCESS);
}
