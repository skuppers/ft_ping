/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <skuppers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:15:30 by skuppers          #+#    #+#             */
/*   Updated: 2020/04/17 20:16:01 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getopt.h"

int				g_optind = -1;
int				g_optopt = 0;
char			*g_optarg = NULL;

int8_t		opt_needs_argument(char *opt, char *charset)
{
	char	*target;

	if (opt[0] != '-')
		return (-2);
	else
		opt++;
	target = ft_strchr(charset, *opt);
	if (target != NULL)
	{
		if (target + 1 == '\0')
			return (0);
		else if (*(target + 1) == ':')
			return (1);
	}
	return (-1);
}

int32_t			extract_option(char *option, char *charset)
{
	int32_t		option_char;

	if (ft_strbeginswith(option, "-"))
	{
		if (ft_strchr(charset, *(option + 1)) == NULL)
			return ('?');
		if (opt_needs_argument(option, charset) == 1)
		{
			option++;
			option_char = *option;
			option++;
			g_optarg = option;
			return (option_char);
		}
		else
			return (*(++option));
	}
	else if (g_optind == -1)
		g_optind = g_optopt - 1;
	return (-1);
}

int32_t			ft_getopt(int ac, char **av, char *charset)
{
	static char		*option;
	
	if (ac < 2 || charset == NULL || ft_strlen(charset) == 0)
		return (-1);

	option = av[g_optopt++];
	if (option == NULL)
		return (-1);

	return (extract_option(option, charset));
}
