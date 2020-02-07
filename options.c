/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 08:55:41 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/07 09:00:00 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

uint8_t	parse_opt(int ac, char **av, t_data *param)
{
	// activate option like '-h -c -v -m -o -S -s -W'
	// return the FQDN or IP with regex
	uint32_t i;

	i = 0;
	while (i < (uint32_t)(ac))
	{
		printf("Parsing argument |%s|\n", *av);
	}


	return (0);
}

