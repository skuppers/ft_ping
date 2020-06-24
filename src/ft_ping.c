/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 08:22:15 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:53:17 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "ft_ping.h"

static void			setup_runtime(t_runtime *runtime, t_data *param, int socket)
{
	memset(runtime, 0, sizeof(struct s_runtime));
	runtime->param = param;
	runtime->socket = socket;
	runtime->rpacketlist_head = NULL;
}

static uint8_t		is_paramcount_reached(uint16_t seq, uint32_t count)
{
	if (count == 0)
		return (1);
	else if (seq <= count)
		return (1);
	return (0);
}

static void			ping_while(t_runtime *runtime)
{
	uint8_t			*packet;
	uint16_t		sequence;
	t_timer			timer;

	sequence = 1;
	packet = NULL;
	while (g_signals->sigint == 0
		&& is_paramcount_reached(sequence, runtime->param->count))
	{
		packet = forge_packet(runtime, packet, sequence);

		if (send_packet(runtime, packet, &timer) == SUCCESS)
			receive_packet(runtime, packet, &timer, sequence);

		++sequence;

	//	if (g_signals->sigalrm != 1)
			ping_timer(runtime->param->interval);

		g_signals->sigalrm = 0;
	}
}

int32_t				ft_ping(t_data *param)
{
	int				socket;
	t_runtime		runtime;

	printf("Count: %d\n", param->count);
	printf("Qos: %d\n", param->tos);
	printf("Interval: %d\n", param->interval);
	printf("TTL: %d\n", param->ttl);
	printf("Size: %d\n", param->pkt_size);

	if ((socket = createsocket(param)) < 0)
	{
		ft_strdel(&param->ipv4_str);
		ft_strdel(&param->fqdn);
		return (-1);
	}
	setup_runtime(&runtime, param, socket);
	print_resolve(param);
	ping_while(&runtime);
	print_stats(&runtime);
	ft_strdel(&param->ipv4_str);
	ft_strdel(&param->fqdn);
	return (0);
}
