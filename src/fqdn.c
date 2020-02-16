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


void	prepare_hints(struct addrinfo *hints, uint32_t family)
{
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = family;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_flags = hints->ai_flags | AI_CANONNAME;//AI_ADDRCONFIG;
}

uint32_t	guess_format(t_data *param)
{
	if (0)
	{
		param->options |= OPT_IPV4;
		if (param->interface == NULL)
			return (select_dflt_interface(param));
		return (AF_INET);
	}
	else
	{
		param->options |= OPT_IPV4;	
		if (param->interface == NULL)
			return (select_dflt_interface(param));
		return (AF_INET);
	}
}

// Add support for ipv6 here
int32_t		resolve_target(t_data *param)
{
	struct addrinfo		hints;
	struct addrinfo		*result;
	struct in_addr		*iadr;
	char				buffer[INET_ADDRSTRLEN];

	result = 0;
	if (param->fqdn == NULL)
		return (-1);
	prepare_hints(&hints, guess_format(param));
	if ((getaddrinfo(param->fqdn, NULL, &hints, &result)) != 0)
	{
		ping_fatal("getaddrinfo", "Could not resolve hostname");
		return (-1);
	}
	iadr = &(((struct sockaddr_in*)result->ai_addr)->sin_addr);
	if (inet_ntop(AF_INET, iadr, buffer, INET_ADDRSTRLEN) == NULL)
	{
		ping_fatal("inet_ntop", "undefined");
		return (-1);
	}
	param->ipv4_str = ft_strdup(buffer);
	return (0);
}