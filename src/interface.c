/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:53:48 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 18:04:58 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static uint8_t		retrieve_interfaces(struct ifaddrs **interfaces)
{
	if (getifaddrs(interfaces) == -1)
	{
		ping_fatal("getifaddrs", "could not retreive interfaces");
		return (1);
	}
	return (0);
}

static int8_t		dest_is_on_loopback(char *ip, char *interface)
{
	if ((ft_strbeginswith(ip, "127.0.0.") || ft_strbeginswith(ip, "127.0.1."))
		&& ft_strequ(interface, "lo"))
		return (1);
	return (0);
}

static uint8_t		is_valid_ipv4(char *ip, struct ifaddrs *itf)
{
	if (dest_is_on_loopback(ip, itf->ifa_name) == 0
			&& ft_strequ(itf->ifa_name, "lo") == 0)
		if (itf->ifa_addr->sa_family == AF_INET)
			return (1);
	return (0);
}

uint8_t				select_dflt_interface(t_data *param)
{
	struct ifaddrs	*itf_ptr;
	struct ifaddrs	*interfaces;

	if (retrieve_interfaces(&interfaces))
		return (-1);
	itf_ptr = interfaces;
	while (itf_ptr != NULL)
	{
		if (itf_ptr->ifa_addr == NULL)
		{
			itf_ptr = itf_ptr->ifa_next;
			continue;
		}
		if (dest_is_on_loopback(param->ipv4_str, itf_ptr->ifa_name)
			|| is_valid_ipv4(param->ipv4_str, itf_ptr))
		{
			param->interface = ft_strdup(itf_ptr->ifa_name);
			freeifaddrs(interfaces);
			return (0);
		}
		itf_ptr = itf_ptr->ifa_next;
	}
	freeifaddrs(interfaces);
	printf("ft_ping: Network is unreachable.\n");
	return (-1);
}

uint8_t				is_interface_valid(t_data *param, char *interface)
{
	struct ifaddrs	*itf_ptr;
	struct ifaddrs	*interfaces;

	if (retrieve_interfaces(&interfaces))
		return (-1);
	itf_ptr = interfaces;
	while (itf_ptr != NULL)
	{
		if (itf_ptr->ifa_addr == NULL)
			continue;
		if (ft_strequ(itf_ptr->ifa_name, interface))
		{
			if (itf_ptr->ifa_addr->sa_family == AF_INET)
			{
				param->interface = ft_strdup(itf_ptr->ifa_name);
				freeifaddrs(interfaces);
				return (0);
			}
		}
		itf_ptr = itf_ptr->ifa_next;
	}
	printf("Invalid interface: %s\n", interface);
	freeifaddrs(interfaces);
	exit(42);
}
