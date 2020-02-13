/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:17:44 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 12:02:28 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "ft_ping.h"

void    sigint_handle(int signo)
{
    g_param->sigint = 1;
}

void    sigalrm_handle(int signo)
{
    g_param->timeout = 1;
}

void		update_statistics(t_data *param, t_timer *timer)
{
	if (param->rtt_min == 0 || timer->rtt_sec < param->rtt_min)
		param->rtt_min = timer->rtt_sec;
	if (param->rtt_max == 0 || timer->rtt_sec > param->rtt_max)
		param->rtt_max = timer->rtt_sec;

//	param->rtt_avg =
}

void		clear_timer(t_timer *timer)
{
	timer->send_sec = 0;
	timer->recv_sec = 0;
	timer->rtt_sec = 0;
}

void		start_timer(t_timer *t)
{
	struct timeval	start;

	if (gettimeofday(&start, NULL) != 0)
	{
		printf("Fatal error getting time.\n");
		exit(42);
	}
	t->send_sec = start.tv_sec + (0.000001f * start.tv_usec);
//	printf("Send Time : %f\n", t->send_sec);
}

void		stop_timer(t_timer *t)
{
	struct timeval	stop;

	if (gettimeofday(&stop, NULL) != 0)
	{
		printf("Fatal error getting time.\n");
		exit(42);
	}
	t->recv_sec = stop.tv_sec + (0.000001f * stop.tv_usec);
	t->rtt_sec = (t->recv_sec - t->send_sec);

	printf("Msg send @ %.3f. Received @ %.3f. RTT: %.3f ms.\n",
					t->send_sec, t->recv_sec, t->rtt_sec);
}

void		ping_timer(int interval)
{
	struct timeval tv_current;
	struct timeval tv_next;

	if (gettimeofday(&tv_current, NULL) < 0)
	        printf(" --- Fatal Error - Kernel Panic ---\n");//	ft_error_str_exit("Error gettimeofday\n");
	tv_next = tv_current;
	tv_next.tv_sec += interval;
	while (tv_current.tv_sec < tv_next.tv_sec ||
			tv_current.tv_usec < tv_next.tv_usec)
	{
		if (gettimeofday(&tv_current, NULL) < 0)
		    printf(" --- Fatal Error - Kernel Panic ---\n");//	ft_error_str_exit("Error gettimeofday\n");
	}
}
