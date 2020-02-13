/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:17:44 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 10:35:40 by skuppers         ###   ########.fr       */
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

void		start_timer(t_timer *t)
{
	struct timeval	start;

	if (gettimeofday(&start, NULL) != 0)
	{
		printf("Fatal error getting time.\n");
		exit(42);
	}
	t->send_sec = start.tv_sec;
	t->send_usec = start.tv_usec;
}

void		stop_timer(t_timer *t)
{
	struct timeval	stop;

	if (gettimeofday(&stop, NULL) != 0)
	{
		printf("Fatal error getting time.\n");
		exit(42);
	}
	t->recv_sec = stop.tv_sec;
	t->recv_usec = stop.tv_usec;
	printf("Msg send @ %llu - %llu. Received @ %llu - %llu. RTT: .\n",
					t->send_sec, t->send_usec, t->recv_sec, t->recv_usec);
}

void		pg_timer(int interval)
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
