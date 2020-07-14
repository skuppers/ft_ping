/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 08:55:41 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 15:56:42 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void			ping_exit(int exitcode, const char *message, ...)
{
	va_list			args;

	dprintf(STDERR_FILENO, "ft_ping: ");
	va_start(args, message);
	vdprintf(STDERR_FILENO, message, args);
	va_end(args);
	exit(exitcode);
}

uint8_t			check_valid(char *arg, size_t len, int min, int max)
{
	if (ft_isnumeric(arg) == 0)
		invalid_opt(arg);
	if (ft_strlen(arg) > len || ft_atoi(arg) < min || ft_atoi(arg) > max)
		invalid_count(arg);
	return (1);
}

int				get_arg_opt(char *arg, const char *opt_str[],
								const int count, t_data *param)
{
	if (arg == NULL)
		ping_exit(42, "option requires an argument -- '%s'\n", opt_str[count]);
	if (ft_strequ(opt_str[count], "-c") == 1 && check_valid(arg, 6, 1, 65535))
		param->count = ft_atoi(arg);
	if (ft_strequ(opt_str[count], "-Q") == 1 && check_valid(arg, 3, 0, 255))
		param->tos = ft_atoi(arg);
	if (ft_strequ(opt_str[count], "-i") == 1 && check_valid(arg, 6, 1, 65535))
		param->interval = ft_atoi(arg);
	if (ft_strequ(opt_str[count], "-t") == 1 && check_valid(arg, 6, 1, 255))
		param->ttl = ft_atoi(arg);
	if (ft_strequ(opt_str[count], "-s") == 1 && check_valid(arg, 6, 0, 65535))
		param->pkt_size = ft_atoi(arg);
	return (2);
}

char			*reverse_target(char *src_addr)
{
	struct sockaddr_in	sa;
	char				*hostname;

	hostname = ft_strnew(256);
	ft_bzero(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	inet_pton(AF_INET, src_addr, &sa.sin_addr);
	if (getnameinfo((struct sockaddr*)&sa, sizeof(sa),
			hostname, 255,
			NULL, 0, 0) != 0)
	{
		ft_strdel(&hostname);
		return (NULL);
	}
	return (hostname);
}
