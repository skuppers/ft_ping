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

t_packetlist	*pktlstnew(uint8_t *packet, size_t size)
{
	t_packetlist	*pktlst;
	struct timeval	*tv;

	tv = (struct timeval*) ft_memalloc(sizeof(struct timeval));
	gettimeofday(tv, NULL);
	pktlst = ft_memalloc(sizeof(t_packetlist));
	pktlst->data = packet;
	pktlst->data_size = size;
	pktlst->timestamp = tv;
	return (pktlst);
}

void		register_request(t_runtime *runtime, uint8_t *packet, size_t size)
{
	t_list			*data;

	data = ft_lstnew(pktlstnew(packet, size), sizeof(t_packetlist));
	if (runtime->spacketlist_head == NULL)
		runtime->spacketlist_head = data;
	else
		ft_lstadd(&runtime->spacketlist_head, data);
}

int8_t		send_packet(t_runtime *runtime, uint8_t *packet)
{
//TODO:	if (runtime->param->options & OPT_IPV6)
	int16_t	sent_bytes;
	size_t 	packet_size;
	
	packet_size = ICMP_HDRLEN + runtime->param->pkt_size;
	if ((sent_bytes = sendto (runtime->socket, packet + IP4_HDRLEN, packet_size, 0,
  		(struct sockaddr *) runtime->param->sin, sizeof (struct sockaddr))) < 0)
	{
    	perror ("sendto() failed ");
    	exit (EXIT_FAILURE);
	}
	register_request(runtime, packet + IP4_HDRLEN, ICMP_HDRLEN);
	alarm(1);
	return (SUCCESS);
}
