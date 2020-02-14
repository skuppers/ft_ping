/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 14:56:40 by skuppers         ###   ########.fr       */
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
#include <errno.h>

#include <bits/endian.h>

#include "libft.h"

#define OPT_HELP 	0x01 // -h
#define OPT_VERBOSE 0x02 // -v
#define OPT_SILENT	0x04 // -q


#define BASE_TTL		64

#define IP4_HDRLEN		20
#define ICMP_HDRLEN		8

struct				ip_hdr
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
	unsigned short	icmp_id;
	unsigned short	icmp_sequence;
};

typedef struct		s_data
{
	uint8_t			options;

	uint8_t			timeout;
	uint8_t			sigint;

	unsigned char		ttl;
	unsigned int		count;
	unsigned int		pkt_size;

	char				*fqdn;
	char				*ipv4_str;
	struct sockaddr_in	*ipv4;
	

	

	

	uint32_t		pkt_send;
	uint32_t		pkt_recvd;

	float			rtt_min;
	float			rtt_max;
	float			rtt_avg;

	float			std_deviation;
	float			timings[4096];
}					t_data;


uint16_t				checksum(uint16_t *addr, int32_t len);
uint8_t					*allocate_ucharlist(int32_t len);
int32_t					*allocate_intlist(int32_t len);

void					ping_fatal(const char *failed, const char *errbuff);

int32_t					ft_ping(t_data *param);

int32_t					resolve_fqdn(t_data *param);
int32_t			parse_opt(int ac, char **av, t_data *param);
int32_t					createSocket(void);
int8_t					setSocketOptions(t_data *param, int socket);

uint8_t					*forge_packet(t_data *param, uint16_t total_length);

typedef struct		s_icmppacket
{
	struct icmphdr	header;
	char			*msg;
}					t_icmppacket;



typedef struct		s_timer
{
	double			send_sec;
	double			recv_sec;
	double			rtt_sec;
}					t_timer;

t_data				*g_param;	//global

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
