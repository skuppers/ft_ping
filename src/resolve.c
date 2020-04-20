/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fqdn.c                                             :+:      :+:    :+:   */
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
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;
	hints->ai_socktype = 0;
	hints->ai_flags = AI_V4MAPPED | AI_ADDRCONFIG;
}

char					*reverse_target(char *src_addr)
{
	struct sockaddr_in	sa;
	char				hostname[256];

	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	inet_pton(AF_INET, src_addr, &sa.sin_addr);
	if (getnameinfo((struct sockaddr*)&sa, sizeof(sa),
			hostname, sizeof(hostname),
			NULL, 0, NI_NAMEREQD))
		return (NULL);
	return (ft_strdup(hostname));
}

static uint8_t			check_broadcast(char *str)
{
	if (ft_strequ(str, "255.255.255.255"))
	{
		printf("ft_ping: Impossible to ping broadcast.\n");
		return (1);
	}
	return (0);
}

static uint8_t			getsocketresult(char *fqdn, struct addrinfo **results)
{
	struct addrinfo		hints;

	prepare_hints(&hints);
	if ((getaddrinfo(fqdn, NULL, &hints, results)) != 0)
	{
		printf("ft_ping: %s: Temporary failure in name resolution\n", fqdn);
		return (1);
	}
	return (0);
}

int32_t					resolve_target(t_data *param)
{
	struct addrinfo		*result;
	struct in_addr		*iadr;
	char				buffer[INET_ADDRSTRLEN];

	if (check_broadcast(param->fqdn))
		return (-1);
	result = NULL;
	if (getsocketresult(param->fqdn, &result))
		return (-1);
	param->sin = ((struct sockaddr_in*)result->ai_addr);
	iadr = &(((struct sockaddr_in*)result->ai_addr)->sin_addr);
	ft_bzero(buffer, INET_ADDRSTRLEN);
	if (inet_ntop(AF_INET, iadr, buffer, INET_ADDRSTRLEN) == NULL)
	{
		ping_fatal("inet_ntop", "undefined");
		return (-1);
	}
	freeaddrinfo(result);
	param->ipv4_str = ft_strdup(buffer);
	if (param->interface == NULL)
		if (select_dflt_interface(param) != 0)
			return (-1);
	return (0);
}
