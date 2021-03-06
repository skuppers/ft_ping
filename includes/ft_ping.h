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
# include <sys/time.h>
# include <ifaddrs.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <net/if.h>
# include <bits/endian.h>
# include "libft.h"

# define OPT_HELP			0x001
# define OPT_SO_DEBUG		0x002
# define OPT_TIMESTAMP		0x004
# define OPT_QUIET			0x008
# define OPT_VERBOSE		0x010
# define OPT_NUMERIC		0x20
# define BASE_TTL			64
# define IP4_HDRLEN			20
# define ICMP_HDRLEN		8
# define MTU				1500

typedef struct				s_signals
{
	volatile sig_atomic_t	sigalrm;
	volatile sig_atomic_t	sigint;
}							t_signals;

extern t_signals			*g_signals;

typedef struct				s_data
{
	uint16_t				options;
	char					padding[2];
	unsigned int			count;
	uint32_t				interval;
	uint16_t				pkt_size;
	uint8_t					tos;
	uint8_t					ttl;
	struct sockaddr_in		*sin;
	char					*fqdn;
	char					*ipv4_str;
}							t_data;

struct						s_ipv4_hdr
{
# if __BYTE_ORDER == __LITTLE_ENDIAN

	unsigned char			ip_header_length:4;
	unsigned char			ip_version:4;
# elif __BYTE_ORDER == __BIG_ENDIAN

	unsigned char			ip_version:4;
	unsigned char			ip_header_length:4;
# else
#  error "Please fix <bits/endian.h>"
# endif

	unsigned char			ip_tos;
	unsigned short			ip_len;
	unsigned short			ip_id;
	unsigned short			ip_frag_offset;
	unsigned char			ip_ttl;
	unsigned char			ip_type;
	unsigned short			ip_checksum;
	struct in_addr			ip_src;
	struct in_addr			ip_dst;
};

struct						s_icmpv4_hdr
{
	uint8_t					icmp_type;
	uint8_t					icmp_code;
	uint16_t				icmp_checksum;
	uint16_t				icmp_identifier;
	uint16_t				icmp_sequence;
};

typedef struct				s_packetdata
{
	void					*data;
	uint32_t				data_size;
	char					padding[4];
	struct timeval			*timestamp;
	double					rtt;
}							t_packetdata;

typedef struct				s_stats
{
	uint32_t				pkt_send;
	uint32_t				pkt_recvd;
	uint16_t				icmp_errors;
	char					padding[2];
	float					rtt_min;
	float					rtt_max;
	float					rtt_avg;
	float					std_deviation;
}							t_stats;

typedef struct				s_timer
{
	struct timeval			send;
	struct timeval			recv;
}							t_timer;

typedef	struct				s_meta
{
	int32_t					r_bts;
	char					padding[4];
	struct s_timer			*timer;
	uint16_t				sequence;
	char					paddings[6];
}							t_meta;

typedef struct				s_runtime
{
	int						socket;
	char					padding[4];
	t_data					*param;
	t_list					*rpacketlist_head;
}							t_runtime;

void						print_reverse(t_data *param, char *src);
void						handle_standalone_options(int32_t option,
								t_data *param);
void						handle_custom_options(int32_t opt, t_data *prm,
								char *oarg);
void						free_packetlist(t_list *pkt_list);
t_packetdata				*pktdatanew(uint8_t *packet,
								size_t size, t_timer *timer);
void						register_response(t_runtime *runtime, uint8_t *p,
								ssize_t size, t_timer *timer);
void						id_seq_mismatch(t_runtime *rt, uint8_t *pkt,
								t_timer *tm, uint16_t seq);
void						resp_code_zero(t_runtime *rt, uint8_t *pkt,
								t_meta *pm);
void						resp_code_eleven(t_runtime *rt, uint8_t *pkt,
								t_meta *pm);
void						resp_code_three(t_runtime *rt, uint8_t *pkt,
								t_meta *pm);
void						resp_code_unknown(t_runtime *rt, uint8_t *pkt,
								t_meta *pm);
void						del_metadata(void *metadata);
void						print_help(uint8_t exits);
char						*reverse_target(char *src_addr);
void						print_ttl_exceeded(t_data *p, uint8_t *k,
								uint16_t seq);
void						print_unreachable(t_data *p, uint8_t *k, uint8_t c,
								uint16_t s);
void						print_unknown(t_data *p, uint8_t *k, uint16_t s);
void						init_param(t_data *param);
void						init_signals(t_signals *signals);
uint32_t					list_received(t_list *list_header);
void						print_stats(t_runtime *param);
void						update_statistics(t_runtime *rt, t_stats *stats);
uint16_t					ip_checksum(void *vdata, size_t length);
void						ping_timer(int interval);
float						plot_timer(t_timer *timer);
void						sigalrm_handle(int signo);
void						sigint_handle(int signo);
void						receive_packet(t_runtime *runtime, uint8_t *packet,
								t_timer *tv, uint16_t seq);
int8_t						send_packet(t_runtime *rt, uint8_t *packet,
								t_timer *tv);
void						extract_ipaddr(const struct sockaddr *sa, char *ip,
								uint32_t maxlen);
uint16_t					checksum(uint16_t *addr, int32_t len);
void						ping_fatal(const char *failed, const char *errbuff);
int32_t						ft_ping(t_data *param);
int32_t						resolve_target(t_data *param);
int8_t						parse_opt(char **av, t_data *param);
int32_t						createsocket(t_data *param);
uint8_t						*forge_packet(t_runtime *rt, uint8_t *pkt,
								uint16_t seq);
void						setup_icmpv4_header(struct s_icmpv4_hdr *hdr,
								uint16_t seq);
uint16_t					setup_message_body(t_data *param, char *data);
void						print_ping(t_data *param, uint8_t *pkt, t_meta *tm);
void						print_usage(uint8_t exit);
void						print_resolve(t_data *param);
void						invalid_ttl(char *oarg);
void						invalid_tos(char *oarg);
void						invalid_size(char *oarg);
void						invalid_timing(char *oarg);
void						invalid_count(char *oarg);
void						option_not_supported(int32_t arg);
void						invalid_opt(char *arg);
void						print_resolution(float ff, uint16_t seq,
								unsigned char ip_ttl);
void						print_timestamp(t_data *param, t_timer *tm);
void						print_reverse(t_data *params, char *src);
void						ft_freeaddrinfo(struct addrinfo *todel);
int8_t						is_loopback_duplicate(uint16_t code);
uint8_t						check_valid(char *arg, size_t len, int min,
								int max);
void						prep_meta(uint16_t seq, t_meta *pktmeta,
								t_timer *tm);
int							get_arg_opt(char *arg, const char *opt_str[],
								const int count, t_data *param);
uint8_t						check_valid(char *arg, size_t len, int min,
								int max);
void						ping_exit(int exitcode, const char *message, ...);
#endif
