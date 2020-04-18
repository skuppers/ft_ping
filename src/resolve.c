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


static void	prepare_hints(struct addrinfo *hints)
{
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;
	hints->ai_socktype = 0;
	hints->ai_flags = AI_V4MAPPED | AI_ADDRCONFIG;
}

char 		*reverse_target(char *src_addr)
{
	struct sockaddr_in	sa;
	char 				hostname[256];
	
    memset(&sa, 0, sizeof sa);
	sa.sin_family = AF_INET;
  	inet_pton(AF_INET, src_addr, &sa.sin_addr);
	if (getnameinfo((struct sockaddr*)&sa, sizeof(sa),
                    hostname, sizeof(hostname),
                    NULL, 0, NI_NAMEREQD))
		return (NULL);
	return (ft_strdup(hostname));
}

int32_t		resolve_target(t_data *param)
{
	struct addrinfo		hints;
	struct addrinfo		*result;
	struct in_addr		*iadr;
	char				buffer[INET_ADDRSTRLEN];

	
// check for configured interfaces but no inet access
	if  (ft_strequ(param->fqdn, "255.255.255.255"))
	{
		printf("ft_ping: Do you want to ping broadcast? sorry that's not possible.\n");
		return (-1);
	}

	if (param->interface == NULL)
		if (select_dflt_interface(param) != 0)
			return (-1);

	prepare_hints(&hints);


	result = 0;
	if ((getaddrinfo(param->fqdn, NULL, &hints, &result)) != 0)
	{
		printf("ft_ping: %s: Temporary failure in name resolution\n",
			param->fqdn);
		free(param->interface);
		return (-1);
	}

	param->sin = ((struct sockaddr_in*)result->ai_addr);
	iadr = &(((struct sockaddr_in*)result->ai_addr)->sin_addr);

	if (inet_ntop(AF_INET, iadr, buffer, INET_ADDRSTRLEN) == NULL)
	{
		ping_fatal("inet_ntop", "undefined");
		return (-1);
	}
	freeaddrinfo(result);
	param->ipv4_str = ft_strdup(buffer);
	return (0);
}