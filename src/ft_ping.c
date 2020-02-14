/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 08:22:15 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 17:03:27 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "ft_ping.h"

void	store_timings(t_timer *timer, float *timings, int sequence)
{
	timings[sequence - 1] = timer->rtt_sec;
}



void	ping_while(t_data *param, int socket, t_timer *timer)
{
	uint32_t		sequence;
	t_icmppacket	*icmp_pkt;

	sequence = 1;
	while (param->sigint == 0 && sequence <= param->count)
	{
		icmp_pkt = forge_packet(param);
		pkt_setsequence(icmp_pkt, sequence);
		pkt_fix_checksum(icmp_pkt, icmp_pkt, HDR_SZ + param->pkt_size);

		clear_timer(timer);
		start_timer(timer);
		send_packet(param, socket, icmp_pkt);

		if (receive_packet(param, socket) != -1)
		{
			stop_timer(timer);
			store_timings(timer, param->timings, param->pkt_recvd);
			print_ping(param, icmp_pkt, timer);
			update_statistics(param, timer);
		}
		else
			printf("Timeout for icmp sequence %d.\n", sequence);
		++sequence;
		ping_timer(1);
	}
}

void	ping_loop(t_data *param, int socket, t_timer *timer)
{
//	int				sequence;
	uint8_t			*packet;

//	sequence = 1;
	while (param->sigint == 0)
	{
		packet = forge_packet(param);

		pkt_setsequence(icmp_pkt, sequence);
		pkt_fix_checksum(icmp_pkt, icmp_pkt, HDR_SZ + param->pkt_size);

		clear_timer(timer);
		start_timer(timer);
		send_packet(param, socket, icmp_pkt);

		receive_packet(param, socket);
		stop_timer(timer);
		store_timings(timer, param->timings, sequence);
		print_ping(param, icmp_pkt, timer);

		update_statistics(param, timer);
		++sequence;

		ping_timer(1);
	}
}

int32_t ft_ping(t_data *param)
{
	int			socket;
	t_timer		timer;

	if ((socket = createSocket()) < 0)
		return (-1);
	if (setSocketOptions(param, socket) < 0)
		return (-1);

	if (param->count == 0)
		ping_loop(param, socket, &timer);


	//else	
	//	ping_while(param, socket, &timer);
	return (0);
}
