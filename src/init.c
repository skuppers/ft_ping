/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:17:44 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:45:25 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	init_param(t_data *param)
{
	ft_memset(param, 0, sizeof(struct s_data));
	param->ttl = BASE_TTL;
	param->interval = 1.0;
	param->pkt_size = 56;
}

void	init_signals(t_signals *signals)
{
	ft_memset(signals, 0, sizeof(struct s_signals));
	g_signals = signals;
	signal(SIGALRM, &sigalrm_handle);
	signal(SIGINT, &sigint_handle);
}
