#include "ft_ping.h"

struct ifaddrs *allocate_interfacedata(struct ifaddrs *iface)
{
    struct ifaddrs *interface = ft_memalloc(sizeof(struct ifaddrs));
    ft_memcpy(interface, iface, sizeof(struct ifaddrs));
    return (interface);
}

uint8_t        select_dflt_interface(t_data *param)
{
    struct ifaddrs  *itf_ptr;
    struct ifaddrs  *interfaces;

    if (getifaddrs(&interfaces) == -1)
    {
        ping_fatal("getifaddrs","could not retreive interfaces");
        return (-1);
    }
    itf_ptr = interfaces;
    
    while (itf_ptr != NULL)
    {
        if ((ft_strbeginswith(param->ipv4_str, "127.0.0.")
            || ft_strbeginswith(param->ipv4_str, "127.0.1."))
            && ft_strequ(itf_ptr->ifa_name, "lo"))
        {
            param->interface = ft_strdup(itf_ptr->ifa_name);
            freeifaddrs(interfaces);
            return (0);
        }
        if (itf_ptr->ifa_addr == NULL || ft_strequ(itf_ptr->ifa_name, "lo"))
        {
            itf_ptr = itf_ptr->ifa_next;
            continue;
        }
        if (itf_ptr->ifa_addr->sa_family == AF_INET)
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