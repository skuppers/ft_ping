/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 08:22:15 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:53:17 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "ft_ping.h"

/*
void	store_timings(t_timer *timer, float *timings, int sequence)
{
	timings[sequence - 1] = timer->rtt_sec;
}





void	ping_loop(t_data *param, int socket, t_timer *timer)
{
//	int				sequence;
	uint8_t			*packet;

//	probably a list of packets?
//	uint8_t			packet_list[MAX_INET_IP_PKTS]
//	sequence = 1;

	while (g_signals->sigint == 0) //change name maybe
	{
		// make 2 outta 3 fcts
		packet = forge_packet(param);
		pkt_setsequence(icmp_pkt, sequence);
		pkt_fix_checksum(icmp_pkt, icmp_pkt, HDR_SZ + param->pkt_size);

		//Rewiev timing completely
		clear_timer(timer);
		start_timer(timer);

		send_packet(param, socket, icmp_pkt);
    	// Register sent packet w/ timestamp

		//return success or fail for next lines?
		receive_packet(param, socket);
		// just cast them ,store, and print according messages,
		// store packet with timestamp

		stop_timer(timer); // yeah see above

		store_timings(timer, param->timings, sequence);// not needed if timestamp stored

		print_ping(param, icmp_pkt, timer); // deprecated, included in receive_pkt


		//fuck statistics in a loop, if all is stored just do this at the end
		update_statistics(param, timer);
		++sequence; // neccesary? probably

		ping_timer(1);
	}
}*/

void	setup_runtime(t_runtime *runtime, t_data *param, int socket)
{
	memset(runtime, 0, sizeof(struct s_runtime));
	runtime->param = param;
	runtime->socket = socket;
	runtime->rpacketlist_head = NULL;
}

static void	ping_while(t_runtime *runtime)
{
	uint8_t		*packet;
	uint16_t	sequence;
	t_timer		timer;

	sequence = 1;
	while (g_signals->sigint == 0 && sequence <= runtime->param->count)
	{
		packet = forge_packet(runtime, packet, sequence);

/*	printf("Forged a %u bytes ipv4 packet\n", ntohs(((struct ipv4_hdr *)packet)->ip_len));
		printf(" ----------------- \n");
		printf("hdr->hdr_len:\t%u\n", ((struct ipv4_hdr *)packet)->ip_header_length);
		printf("hdr->version:\t%u\n", ((struct ipv4_hdr *)packet)->ip_version);
		printf("hdr->tos    :\t%u\n", ((struct ipv4_hdr *)packet)->ip_tos);
		printf("hdr->len    :\t%u\n", ntohs(((struct ipv4_hdr *)packet)->ip_len));
		printf("hdr->id      :\t%u\n", ntohs(((struct ipv4_hdr *)packet)->ip_id));
		printf("hdr->ttl     :\t%u\n", ((struct ipv4_hdr *)packet)->ip_ttl);
		printf("hdr->type    :\t%u\n", ((struct ipv4_hdr *)packet)->ip_type);
		printf("hdr->checksum:\t%x\n", ((struct ipv4_hdr *)packet)->ip_checksum);
		char *src = ft_strnew(16);
		inet_ntop(AF_INET, &((struct ipv4_hdr *)packet)->ip_src, src, 16);
		printf("hdr->src	 :\t%s\n", src);
		char *dst = ft_strnew(16);
		inet_ntop(AF_INET, &((struct ipv4_hdr *)packet)->ip_dst, dst, 16);
		printf("hdr->dst	 :\t%s\n", dst);
		printf(" ----------------- \n");
		printf("icmp->type     :\t%u\n", ((struct icmpv4_hdr *)packet + IP4_HDRLEN)->icmp_type);
		printf("icmp->code    :\t%u\n", ((struct icmpv4_hdr *)packet + IP4_HDRLEN)->icmp_code);
	printf(" ----------------- \n\n");
*/

		if (send_packet(runtime, packet, &timer) == SUCCESS) 
			receive_packet(runtime, packet, &timer, sequence);
		
		++sequence;

		if (g_signals->sigalrm != 1)
			ping_timer(runtime->param->interval);

		g_signals->sigalrm = 0;
	}
}

static void		ping_loop(t_runtime *runtime)
{
	uint8_t		*packet;
	uint16_t	sequence;
	t_timer		timer;

	sequence = 1;
	while (g_signals->sigint == 0)
	{
		packet = forge_packet(runtime, packet, sequence);
		ft_memset(&timer, 0, sizeof(t_timer));
		if (send_packet(runtime, packet, &timer) == SUCCESS) 
			receive_packet(runtime, packet, &timer, sequence); // do a pointer jutsu here for packet
		++sequence;
		
		if (g_signals->sigalrm != 1)
			ping_timer(runtime->param->interval);

		g_signals->sigalrm = 0;
	}
}

int32_t ft_ping(t_data *param)
{
	int				socket;
	t_runtime		runtime;

	if ((socket = createSocket(param)) < 0)
		return (-1);
	setup_runtime(&runtime, param, socket);
	print_resolve(param);

	if (param->count > 0)
		ping_while(&runtime);
	
	else if (param->count == 0)
		ping_loop(&runtime);

	print_stats(&runtime);

	free(runtime.param->interface);
	ft_strdel(&param->ipv4_str);
	
	return (0);
}