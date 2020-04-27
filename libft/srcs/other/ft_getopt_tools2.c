/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <skuppers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:15:30 by skuppers          #+#    #+#             */
/*   Updated: 2020/04/17 20:16:01 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getopt.h"
#include "list.h"
#include "memory.h"

void	ft_lstiter_elem_ctx(t_list *lst, void *context,
			void (*f)(void *data, void *ctx))
{
	if (lst)
	{
		f(lst, context);
		ft_lstiter_elem_ctx(lst->next, context, f);
	}
}

int		is_option_or_not(void *opt1, void *opt2)
{
	if (opt1 == NULL || opt2 == NULL)
		return (0);
	if (ft_strbeginswith((char *)opt1, "-")
		&& ft_strbeginswith((char *)opt2, "-"))
		return (0);
	else
	{
		if (ft_strbeginswith((char *)opt1, "-"))
			return (-1);
		return (1);
	}
}

int		is_option_or_argument(void *opt1, void *opt2)
{
	if (opt1 == NULL || opt2 == NULL)
		return (0);
	if (ft_strlen((char *)opt1) > ft_strlen((char *)opt2))
		return (1);
	else
		return (-1);
}
