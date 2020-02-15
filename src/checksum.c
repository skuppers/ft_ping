/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 08:23:00 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:25:10 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

uint16_t	checksum(uint16_t *addr, int32_t len)
{
	int32_t		count;
	uint32_t	sum;

	while (count > 1)
	{
		sum += *(addr++);
		count -= 2;
	}
	if (count > 0)
		sum += *(uint8_t *) addr;
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);
	return (~sum);
}
