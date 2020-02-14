/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fqdn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:34:50 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 14:07:22 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"


void	prepare_hints(struct addrinfo *hints)
{
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_flags = hints->ai_flags | AI_CANONNAME;//AI_ADDRCONFIG;
}

int32_t		resolve_fqdn(t_data *param)
{
	struct addrinfo		hints;
	struct addrinfo		*result;
	struct in_addr		*iadr;
	char				buffer[INET_ADDRSTRLEN];

	result = 0;
	memset(&hints, 0, sizeof(struct addrinfo));
	prepare_hints(&hints);
	if ((getaddrinfo(param->fqdn, NULL, &hints, &result)) != 0) //port 1337 ?
	{
		ping_fatal("getaddrinfo", "Could not resolve hostname");
		return (-1);
	}
	param->ipv4 = (struct sockaddr_in*) result->ai_addr;
	iadr = &(param->ipv4->sin_addr);
	if (inet_ntop(AF_INET, iadr, buffer, INET_ADDRSTRLEN) == NULL)
	{
		ping_fatal("inet_ntop", "undefined");
		return (-1);
	}
	param->ipv4_str = ft_strdup(buffer);
	return (0);
}
