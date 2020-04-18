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


/*
void		register_request(t_runtime *runtime, uint8_t *packet, size_t size)
{
	t_list			*data;

	data = ft_lstnew(pktlstnew(packet, size), sizeof(t_packetdata));
	if (runtime->spacketlist_head == NULL)
		runtime->spacketlist_head = data;
	else
		ft_lstadd(&runtime->spacketlist_head, data);
}*/

int8_t		send_packet(t_runtime *runtime, uint8_t *packet, t_timer *tv)
{
	int16_t	sent_bytes;
	size_t 	packet_size;
	
	packet_size = ICMP_HDRLEN + runtime->param->pkt_size;
	if ((sent_bytes = sendto(runtime->socket, packet, packet_size, 0,
  		(struct sockaddr *)runtime->param->sin, sizeof (struct sockaddr))) < 0)
	{
    	ping_fatal("send_packet","sendto() failed");
    	exit (EXIT_FAILURE);
	}
	free(packet);
	if (gettimeofday(&(tv->send), NULL) < 0)
		printf("Error getting timeofday()\n");
//	printf("*[%ld:%ld]", tv->send.tv_sec, tv->send.tv_usec);
	//fflush(stdout);
//	register_request(runtime, packet + IP4_HDRLEN, ICMP_HDRLEN);
	alarm(1);
	return (SUCCESS);
}
