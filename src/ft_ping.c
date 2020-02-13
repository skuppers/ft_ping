/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 08:22:15 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 12:25:33 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "ft_ping.h"

void	ping_loop(t_data *param, int socket, t_timer *timer)
{
	int				sequence;
	t_icmppacket	*icmp_pkt;

	sequence = 1;
	while (param->sigint == 0)
	{
		icmp_pkt = forge_packet(param);
		pkt_setsequence(icmp_pkt, sequence);
		pkt_fix_checksum(icmp_pkt, icmp_pkt, HDR_SZ + param->pkt_size);

		clear_timer(timer);
		start_timer(timer);

		send_packet(param, socket, icmp_pkt);

		receive_packet(param, socket);

		stop_timer(timer);

		print_ping(param, icmp_pkt, timer);

				update_statistics(param, timer);
		++sequence;

		ping_timer(1);
	}
}

void	ping_while(t_data *param, int socket, t_timer *timer)
{
	(void) param; (void) socket; (void) timer;
}

int ft_ping(t_data *param)
{
	int			socket;
	t_timer		timer;

	socket = createSocket();
	setSocketOptions(param, socket);
	if (param->count != 0)
		ping_while(param, socket, &timer);
	else
		ping_loop(param, socket, &timer);
	return (0);
}
