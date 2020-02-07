/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/07 14:36:13 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <signal.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/cdefs.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <netdb.h>
# include <sys/uio.h>
# include <arpa/inet.h>
# include <netinet/ip_icmp.h>
# include <netinet/in.h>

#include "libft.h"

#define OPT_HELP 	0x01
#define OPT_VERBOSE 0x02
#define OPT_ONCE	0x04
#define OPT_WAITIME 0x08 // maybe not
#define OPT_PKTSIZE 0x10
#define OPT_SOURCE	0x20
#define OPT_COUNT	0x40 // require argument
#define OPT_TTL		0x80

#define TTL 64

typedef struct		s_icmppacket
{
	struct icmphdr	header;
	char			*msg;
}					t_icmppacket;

typedef struct		s_data
{
	unsigned char	options;
	unsigned char	ttl;
	unsigned int	count;
	unsigned int	src_address; // Use pton ou un truc du genre
	unsigned int	pkt_size;
	char			*fqdn;
	char			*hostname;
	struct sockaddr	*host;
	socklen_t		hostlen;

}					t_data;

void				print_usage(void);
void 				print_resolve(t_data *param);
void 				print_ping(t_data *param);
void 				print_stats(t_data *param);

int					send_packet(t_dat *param, int socket, t_icmppacket *pkt);

int					createSocket(void);
int					setSocketOptions(t_data *param, int socket);

int					ft_ping(t_data *param);
uint8_t				parse_opt(int ac, char **av, t_data *param);
t_icmppacket		*forge_packet(t_data *param);
int					resolve_fqdn(t_data *param);

void				pkt_setsequence(t_icmppacket *pkt, int sequence);
uint16_t			pkt_checksum(void *pkt, size_t len);

#endif
