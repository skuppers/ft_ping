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

int				g_optind = 0;
int				g_optopt = 1;
char			*g_optarg = NULL;

int32_t			retrieve_argument(char **av,
					char **option, char **processing)
{
	char	*argstart;
	char	*argument;
	int32_t	option_processing;

	argstart = (*processing + 1);
	if (argstart != NULL && *argstart != 0)
	{
		argument = argstart;
		g_optarg = argument;
		option_processing = (int32_t)**processing;
	}
	else
	{
		*option = av[++g_optind];
		g_optarg = *option;
		option_processing = (int32_t)**processing;
	}
	*processing = NULL;
	*option = NULL;
	return (option_processing);
}

int32_t			inspect_option(char **av, char **option, char **processing,
									char *charset)
{
	char		*target;

	if (*processing != NULL && **processing != '\0')
	{
		if ((target = ft_strchr(charset, **processing)) != NULL)
		{
			if (*(target + 1) != '\0' && *(target + 1) == ':')
				return (retrieve_argument(av, option, processing));
			else
				return ((int32_t)**processing);
		}
		else
			return ('?');
	}
	*processing = NULL;
	*option = NULL;
	return (0);
}

int32_t			process_next_opt(char **av, char *charset,
									char **option, char **processing)
{
	int32_t		returnval;

	if (ft_strbeginswith(*option, "-"))
	{
		*processing = ++(*option);
		if ((returnval = inspect_option(av, option, processing, charset)) == 0)
			return (ft_getopt(2, av, charset));
		return (returnval);
	}
	g_optopt = g_optind;
	*option = NULL;
	return (ft_getopt(2, av, charset));
}

int32_t			continue_process(char **av, char *charset,
									char **option, char **processing)
{
	int32_t		returnval;

	++(*processing);
	if ((returnval = inspect_option(av, option, processing, charset)) == 0)
		return (ft_getopt(2, av, charset));
	return (returnval);
}

int32_t			ft_getopt(int ac, char **av, char *charset)
{
	static char	*option;
	static char	*processing;

	if (ac < 2 || charset == NULL || ft_strlen(charset) == 0)
		return (-1);
	if (option == NULL)
		option = av[++g_optind];
	if (option == NULL)
		return (-1);
	if (processing == NULL)
		return (process_next_opt(av, charset, &option, &processing));
	return (continue_process(av, charset, &option, &processing));
}
