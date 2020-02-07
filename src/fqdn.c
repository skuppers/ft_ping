/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fqdn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:34:50 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/07 13:54:25 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int		resolve_fqdn(t_data *param)
{
	int error;
	struct addrinfo hints;
	struct addrinfo *result;

	error = 0;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = 0;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_ADDRCONFIG;

	result = 0;
	if ((error = getaddrinfo(param->fqdn, "1337", &hints, &result)) != 0)
	{
		printf("ft_ping: Fatal error when resolving hostname. (getaddrinfo).\n");
		exit(42);
	}
	char buffer[64];

	param->host = result->ai_addr;
	param->hostlen = result->ai_addrlen;

	struct sockaddr_in *sadr = (struct sockaddr_in*)result->ai_addr;
	struct in_addr *iadr = &(sadr->sin_addr);

	if (inet_ntop(AF_INET, iadr, &buffer, sizeof(buffer)) != NULL)
	{
		printf("\nResolved address: %s\n", buffer);

	}
	else
	{
		printf("Error getting resolved address\n");
	}
	return (0);
}
