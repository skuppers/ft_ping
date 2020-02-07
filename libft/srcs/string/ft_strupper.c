/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cedricmpassi <cempassi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 12:24:35 by cedricmpa         #+#    #+#             */
/*   Updated: 2019/02/03 12:25:48 by cedricmpa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strupper(char *str)
{
	while (*str)
	{
		*str = ft_toupper(*str);
		str++;
	}
}