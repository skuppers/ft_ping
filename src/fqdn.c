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

void	resolve_error(void)
{
	printf("ft_ping: Fatal error when resolving hostname.\n");
	exit(42);
}

void	prepare_hints(struct addrinfo *hints)
{
	hints->ai_family = AF_INET;
	hints->ai_socktype = 0;
	hints->ai_protocol = 0;
	hints->ai_flags = AI_ADDRCONFIG;
}

int		resolve_fqdn(t_data *param)
{
	char				buffer[64];
	struct addrinfo		hints;
	struct addrinfo		*result;
	struct sockaddr_in	*sadr;
	struct in_addr		*iadr;

	result = 0;
	memset(&hints, 0, sizeof(hints));
	prepare_hints(&hints);
	if ((getaddrinfo(param->fqdn, "1337", &hints, &result)) != 0)
		resolve_error();
	param->host = result->ai_addr;
	param->hostlen = result->ai_addrlen;
	sadr = (struct sockaddr_in*)result->ai_addr;
	iadr = &(sadr->sin_addr);
	if (inet_ntop(AF_INET, iadr, buffer, sizeof(buffer)) != NULL)
		param->hostname = ft_strdup(buffer);
	else
		resolve_error();
	return (0);
}
