/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 08:55:41 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 15:56:42 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void		handle_standalone_options(int32_t option, t_data *param)
{
	if (option == 'h')
		print_help(1);
	else if (option == 'v')
		param->options |= OPT_VERBOSE;
	else if (option == 'q')
		param->options |= OPT_QUIET;
	else if (option == 'd')
		param->options |= OPT_SO_DEBUG;
	else if (option == 'D')
		param->options |= OPT_TIMESTAMP;
}

void		handle_custom_options(int32_t opt, t_data *prm, char *oarg)
{
	if (opt == 'c')
		(valid_args(oarg, 1, 65535, 'c') == 1) ?
			prm->count = (uint16_t)ft_atoi(oarg) : invalid_count(oarg);
	else if (opt == 'i')
		(valid_args(oarg, 1, 255, 'i') == 1) ?
			prm->interval = ft_atoi(oarg) : invalid_timing(oarg);
	else if (opt == 's')
		(valid_args(oarg, 0, 65507, 's') == 1) ?
			prm->pkt_size = ft_atoi(oarg) : invalid_size(oarg);
	else if (opt == 'Q')
		(valid_args(oarg, 0, 255, 'Q') == 1) ?
			prm->tos = ft_atoi(oarg) : invalid_tos(oarg);
	else if (opt == 't')
		(valid_args(oarg, 1, 255, 't') == 1) ?
			prm->ttl = ft_atoi(oarg) : invalid_ttl(oarg);
}