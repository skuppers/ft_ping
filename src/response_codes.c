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

void	id_seq_mismatch(t_runtime *rt, uint8_t *pkt, t_timer *tm, uint16_t seq)
{
	free(pkt);
	if (g_signals->sigalrm == 0 && g_signals->sigint == 0)
		receive_packet(rt, pkt, tm, seq);
	else
		register_response(rt, NULL, 0, tm);
}

void	resp_code_zero(t_runtime *rt, uint8_t *pkt, t_meta *pm)
{
	if (!(rt->param->options & OPT_QUIET))
		print_ping(rt->param, pkt, pm->timer, pm->sequence);
	register_response(rt, pkt, pm->received_bytes, pm->timer);
}

void	resp_code_eleven(t_runtime *rt, uint8_t *pkt, t_meta *pm)
{
	if (!(rt->param->options & OPT_QUIET))
		print_ttl_exceeded(pkt, pm->sequence);
	register_response(rt, pkt, pm->received_bytes, NULL);
}

void	resp_code_three(t_runtime *rt, uint8_t *pkt, t_meta *pm)
{
	if (!(rt->param->options & OPT_QUIET))
		print_unreachable(pkt, pm->sequence);
	register_response(rt, pkt, pm->received_bytes, NULL);
}

void	resp_code_unknown(t_runtime *rt, uint8_t *pkt, t_meta *pm)
{
	if (!(rt->param->options & OPT_QUIET))
		print_unknown(pkt, pm->sequence);
	register_response(rt, pkt, pm->received_bytes, NULL);
}
