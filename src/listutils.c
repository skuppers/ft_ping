/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:05:02 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 15:44:40 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_packetdata		*pktdatanew(uint8_t *packet,
							size_t size, t_timer *timer)
{
	t_packetdata	*pktdata;

	pktdata = ft_memalloc(sizeof(t_packetdata));
	pktdata->data = packet;
	pktdata->data_size = size;
	if (timer == NULL)
		pktdata->rtt = -42.0;
	else
		pktdata->rtt = plot_timer(timer);
	return (pktdata);
}

uint32_t			list_received(t_list *list_header)
{
	uint32_t		len;
	t_list			*listhdr;

	len = 0;
	listhdr = list_header;
	while (listhdr != NULL)
	{
		if (listhdr->data != NULL
			&& ((t_packetdata*)listhdr->data)->rtt != -42.0)
			len++;
		listhdr = listhdr->next;
	}
	return (len);
}

void				free_packetlist(t_list *pkt_list)
{
	t_list			*current;
	t_list			*next;
	t_packetdata	*meta;

	current = pkt_list;
	while (current != NULL)
	{
		next = current->next;
		meta = (t_packetdata *)current->data;
		if (meta != NULL)
		{
			if (meta->data != NULL)
				free(meta->data);
			free(meta);
		}
		free(current);
		current = next;
	}
}
