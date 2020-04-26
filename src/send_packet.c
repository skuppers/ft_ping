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
		if (errno == EPERM)
			printf("ft_ping: sendto: Operation not permitted\n");
		else if (errno == 90)
			printf("ft_ping: sendto: message too long\n");
		else
			printf("ft_ping: sendto: error code %d\n", errno);
	}
	free(packet);
	if (gettimeofday(&(tv->send), NULL) < 0)
		;
	alarm(1);
	return (SUCCESS);
}
