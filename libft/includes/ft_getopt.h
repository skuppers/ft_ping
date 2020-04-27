/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETOPT_H
# define FT_GETOPT_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <stdio.h>
# include "str.h"
# include "list.h"

extern char	*g_optarg;
extern int	g_optind;
extern int	g_optopt;
void		ft_lstiter_elem_ctx(t_list *l, void *c,
				void (*f)(void *d, void *c));
int			is_option_or_not(void *opt1, void *opt2);
int			is_option_or_argument(void *opt1, void *opt2);
int32_t		ft_getopt(int ac, char **av, char *charset);
char		**ft_getopt_order_arguments(int ac, char **av, char *charset);
int8_t		option_needs_argument(char *opt, char *charset);
#endif
