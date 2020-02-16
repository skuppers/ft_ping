#include "ft_ping.h"

uint8_t        select_dflt_interface(t_data *param)
{
    struct ifaddrs  *itf_ptr;
    struct ifaddrs  *interfaces;

    if (getifaddrs(&interfaces) == -1)
    {
        ping_fatal("getifaddrs","could not retreive interfaces");
        exit(1);
    }
    itf_ptr = interfaces;
    
//    resolve_if_fqdn_is_ipv4_or_ipv6;
    while (itf_ptr != NULL)
    {
        if (itf_ptr->ifa_addr == NULL || ft_strequ(itf_ptr->ifa_name, "lo"))
        {
            itf_ptr = itf_ptr->ifa_next;
            continue;
        }
        if ((param->options & OPT_IPV4) && (itf_ptr->ifa_addr->sa_family == AF_INET))
        {
            param->interface = itf_ptr;
            return (0);
        }
        else if ((param->options & OPT_IPV6) && (itf_ptr->ifa_addr->sa_family == AF_INET6))
        {
            param->interface = itf_ptr;
            return (0);
        }   
        itf_ptr = itf_ptr->ifa_next;
    }
    printf("Could not select a good interface.\n");
    return (-1);
}

uint8_t     is_interface_valid(t_data *param, char *interface)
{
    struct ifaddrs  *itf_ptr;
    struct ifaddrs  *interfaces;

    if (getifaddrs(&interfaces) == -1)
    {
        ping_fatal("getifaddrs","could not retreive interfaces");
        exit(1);
    }
    itf_ptr = interfaces;
    while (itf_ptr != NULL)
    {
        if (itf_ptr->ifa_addr == NULL)
            continue;
        if (ft_strequ(itf_ptr->ifa_name, interface))
        {
            if ((param->options & OPT_IPV4) && (itf_ptr->ifa_addr->sa_family == AF_INET))
            {
                param->interface = itf_ptr;
                return (0);
            }
            else if ((param->options & OPT_IPV6) && (itf_ptr->ifa_addr->sa_family == AF_INET6))
            {
                param->interface = itf_ptr;
                return (0);
            }
        }
        itf_ptr = itf_ptr->ifa_next;
    }
    printf("Invalid interface: %s\n", interface);
    exit(42);
}