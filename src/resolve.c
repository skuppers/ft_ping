/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:34:50 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 15:38:52 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void				prepare_hints(struct addrinfo *hints)
{
	ft_memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;
	hints->ai_socktype = 0;
	hints->ai_flags = AI_V4MAPPED | AI_ADDRCONFIG;
}

char					*reverse_target(char *src_addr)
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

static uint8_t			getsocketresult(char *fqdn, struct addrinfo **results)
{
	int32_t				code;
	struct addrinfo		hints;

	prepare_hints(&hints);
	if ((code = getaddrinfo(fqdn, NULL, &hints, results)) != 0)
	{
		if (code == -2)
			dprintf(2, "ft_ping: %s: Name or service not known\n", fqdn);
		else
			dprintf(2,
			"ft_ping: %s: Temporary failure in name resolution\n", fqdn);
		return (1);
	}
	return (0);
}

int8_t					check_numeric(char *str)
{
	struct in_addr		test;

	if (inet_pton(AF_INET, str, &test) != 1)
		return (1);
	return (0);
}

int32_t					resolve_target(t_data *param)
{
	struct in_addr		*iadr;
	char				buffer[INET_ADDRSTRLEN];
	struct sockaddr_in	*sisi;
	struct addrinfo		*result;

	if (check_numeric(param->fqdn) == 0)
		param->options |= OPT_NUMERIC;
	result = NULL;
	if (getsocketresult(param->fqdn, &result))
	{
		ft_strdel(&param->fqdn);
		return (-1);
	}
	sisi = malloc(sizeof(struct sockaddr_in));
	ft_memcpy(sisi, result->ai_addr, sizeof(struct sockaddr_in));
	param->sin = sisi;
	iadr = &sisi->sin_addr;
	ft_bzero(buffer, INET_ADDRSTRLEN);
	if (inet_ntop(AF_INET, iadr, buffer, INET_ADDRSTRLEN) == NULL)
	{
		ping_fatal("inet_ntop", "undefined");
		return (-1);
	}
	param->ipv4_str = ft_strdup(buffer);
	return (0);
}
