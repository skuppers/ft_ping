/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_packet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:53:48 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 18:04:58 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	receive_packet(t_runtime *runtime, uint8_t *packet)
{
	packet = NULL;
	while (/* Timeout is not reached -- alarm() */)
	{
		if (recvfrom(runtime->socket, packet, SOME_SIZE_FOR_IPV4_6,
				MSG_DONTWAIT, NULL, (socklen_t*)sizeof (struct sockaddr)) <= 0)
			;//just do nothing
	}
	if (packet == NULL)
		// Handle timeout
	else
		register_response();
}
