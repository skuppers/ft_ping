/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 11:49:16 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <signal.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/cdefs.h>
# include <unistd.h>
# include <getopt.h>
# include <stdio.h>
# include <time.h>
# include <netdb.h>
# include <sys/uio.h>
# include <arpa/inet.h>
# include <netinet/ip_icmp.h>
# include <netinet/in.h>

#include "libft.h"

#define OPT_HELP 	0x01 // -h
#define OPT_VERBOSE 0x02 // -v
#define OPT_SILENT	0x04 // -q
#define OPT_FLOOD	0x08 // -f see manual

#define IOV_BUFFER_SZ	1500 // MTU
#define BASE_TTL		64
#define HDR_SZ			8
#define BASE_PAYLOAD	56

typedef struct		s_icmppacket
{
	struct icmphdr	header;
	char			*msg;
}					t_icmppacket;

typedef struct		s_data
{
	uint8_t			options;
	uint8_t			timeout;
	uint8_t			sigint;
	unsigned char	ttl;
	unsigned int	count;
	unsigned int	pkt_size;
	char			*fqdn;
	char			*hostname;
	struct sockaddr	*host;
	socklen_t		hostlen;

	uint32_t		pkt_send;
	uint32_t		pkt_recvd;

	float			rtt_min;
	float			rtt_max;
	float			rtt_avg;

	float			std_deviation;
}					t_data;

typedef struct		s_timer
{
	float			send_sec;
	float			recv_sec;
	float			rtt_sec;
}					t_timer;

t_data				*g_param;	//global

void				print_usage(uint8_t exit);
void 				print_resolve(t_data *param);
void 				print_ping(t_data *param);

void				update_statistics(t_data *param, t_timer *timer);
void 				print_stats(t_data *param);

int					send_packet(t_data *param, int socket, t_icmppacket *pkt);
int					receive_packet(t_data *param, int socket);

int					createSocket(void);
int					setSocketOptions(t_data *param, int socket);

int					ft_ping(t_data *param);
uint32_t			parse_opt(int ac, char **av, t_data *param);
t_icmppacket		*forge_packet(t_data *param);
int					resolve_fqdn(t_data *param);

void				pkt_setsequence(t_icmppacket *pkt, int sequence);
void				pkt_fix_checksum(t_icmppacket *pkts, void *pkt, size_t len);

void				sigint_handle(int signo);
void				sigalrm_handle(int signo);

void				ping_timer(int interval);
void				clear_timer(t_timer *t);
void				start_timer(t_timer *t);
void				stop_timer(t_timer *t);

#endif
