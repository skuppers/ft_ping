/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:37:47 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/09 10:37:38 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t			ft_strlen(const char *str)
{
	size_t		size;

	size = 0;
	if (str == NULL || *str == '\0')
		return (0);
	while (str[size] != '\0')
		size++;
	return (size);
}
