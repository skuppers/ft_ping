/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
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
# include <netinet/ip.h>
#include <sys/time.h>
#include <ifaddrs.h>
#include <errno.h>

#include <bits/endian.h>

#include "libft.h"

#define OPT_VERBOSE		0x0002 // -v
#define OPT_QUIET		0x0004 // -q
#define OPT_SO_DEBUG	0x0008 // -d

#define OPT_TIMESTAMP	0x0010 // -D
#define OPT_IPV4		0x0020 // -4
#define OPT_IPV6		0x0040 // -6
#define OPT_PRELOAD		0x0080 // -l <number>

#define OPT_COUNT		0x0100 //-c <number
#define OPT_PKTSZ		0x0200 //-s <pkt-size>

//The following opt's have default value so will see
//#define OPT_TOS
//#define OPT_TTL
//#define OPT_INTERVAL
//#define OPT_DEADLINE
//#define OPT_TIMEOUT
//#define OPT_INTERFACE

#define BASE_TTL		64
#define IP4_HDRLEN		20
#define ICMP_HDRLEN		8

typedef struct			s_data
{
//	struct ifaddrs		*interface_list;
	uint16_t			options;
	unsigned int		count;
	float				interval;
//						interface;
	uint16_t			preload;
	uint16_t			pkt_size;
	uint8_t				tos;
	uint8_t				ttl;
	uint16_t			deadline;
	uint16_t			timeout;
	char				*fqdn;
	char				*ipv4_str;
	struct sockaddr_in	*ipv4;
}						t_data;

struct				ipv4_hdr //ipv4_hdr
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
	unsigned char	ip_header_length:4;
	unsigned char	ip_version:4;
#elif __BYTE_ORDER == __BIG_ENDIAN
	unsigned char	ip_version:4;
	unsigned char	ip_header_length:4;
#else
# error "Please fix <bits/endian.h>"
#endif
	unsigned char	ip_tos;
	unsigned short	ip_len;
	unsigned short	ip_id;
	unsigned short	ip_frag_offset;
	unsigned char 	ip_ttl;
	unsigned char	ip_type;
	unsigned short	ip_checksum;
	unsigned int	ip_src_addr;
	unsigned int	ip_dst_addr;
};

struct				icmp_hdr
{
	unsigned char	icmp_type;
	unsigned char	icmp_code;
	unsigned short	icmp_checksum;
	unsigned short	icmp_identifier;
	unsigned short	icmp_sequence;
};

typedef struct 		s_packetlist
{
	void			*data;
	uint32_t		data_size;
	struct timeval	timestamp;

}					t_packetlist;

typedef struct      s_signals
{
	uint8_t         sigalrm;
	uint8_t         sigint;
}                   t_signals;

t_signals           *g_signals;


typedef struct      s_stats
{
    uint32_t		pkt_send;
	uint32_t		pkt_recvd;
	float			rtt_min;
	float			rtt_max;
	float			rtt_avg;
	float			std_deviation;

//	float			*timings;
}                   t_stats;

//typedef struct		s_timer
//{
//	double			send_sec;
//	double			recv_sec;
//	double			rtt_sec;
//}					t_timer;

typedef struct		s_runtime
{
	int				socket;
	t_data			*param;
	t_list			*packetlist_head;

}					t_runtime;

uint16_t				checksum(uint16_t *addr, int32_t len);
uint8_t					*allocate_ucharlist(int32_t len);
int32_t					*allocate_intlist(int32_t len);

void					ping_fatal(const char *failed, const char *errbuff);

int32_t					ft_ping(t_data *param);

int32_t					resolve_fqdn(t_data *param);
int32_t					parse_opt(int ac, char **av, t_data *param);
int32_t					createSocket(void);
int8_t					setSocketOptions(t_data *param, int socket);

uint8_t					*forge_packet(t_data *param, uint16_t total_length);
void					setup_ipv4_header(t_runtime *rt);
void					setup_ipv6_header(t_runtime *rt);
void					setup_icmp_header(t_runtime *rt);


void				print_usage(uint8_t exit);
void 				print_resolve(t_data *param);
void 				print_ping(t_data *param, t_icmppacket *pkt, t_timer *t);

void				update_statistics(t_data *param, t_timer *timer);
void 				print_stats(t_data *param);

int					send_packet(t_data *param, int socket, t_icmppacket *pkt);
int					receive_packet(t_data *param, int socket);







void				pkt_setsequence(t_icmppacket *pkt, int sequence);
void				pkt_fix_checksum(t_icmppacket *pkts, void *pkt, size_t len);

void				sigint_handle(int signo);
void				sigalrm_handle(int signo);

void				ping_timer(int interval);
void				clear_timer(t_timer *t);
void				start_timer(t_timer *t);
void				stop_timer(t_timer *t);

#endif
