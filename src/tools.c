/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:17:44 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/13 17:01:00 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ping.h"

// Error handling??
uint8_t		*allocate_ucharlist(int32_t len)
{
	void *tmp;

	if (len <= 0)
		printf("Cannot allocate memory. ucharlist(len <= 0).\n");
	if ((tmp = (uint8_t*)ft_memalloc(len * sizeof(uint8_t))) == NULL)
		printf("Cannot allocate memory. malloc().\n");
	return (tmp);

}

int32_t		*allocate_intlist(int32_t len)
{
	void *tmp;

	if (len <= 0)
		printf("Cannot allocate memory. intlist(len <= 0).\n");
	if ((tmp = (int32_t*)ft_memalloc(len * sizeof(int32_t))) == NULL)
		printf("Cannot allocate memory. malloc().\n");
	return (tmp);
}

float        *allocate_floatlist()
{
	void *tmp;

	if (len <= 0)
		printf("Cannot allocate memory. floatlist(len <= 0).\n");
	if ((tmp = (int32_t*)ft_memalloc(len * sizeof(float))) == NULL)
		printf("Cannot allocate memory. malloc().\n");
	return (tmp);
}


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
	param->rtt_avg += (float)timer->rtt_sec;
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
	t->send_sec = start.tv_sec + (double)(0.001f * (double)start.tv_usec);
}

void		stop_timer(t_timer *t)
{
	struct timeval	stop;

	if (gettimeofday(&stop, NULL) != 0)
	{
		printf("Fatal error getting time.\n");
		exit(42);
	}
	t->recv_sec = stop.tv_sec + (double)(0.001f * (double)stop.tv_usec);
	t->rtt_sec = (double)(t->recv_sec - t->send_sec);
}

void		ping_timer(int interval)
{
	struct timeval tv_current;
	struct timeval tv_next;

	if (gettimeofday(&tv_current, NULL) < 0)
	        printf(" --- Fatal Error - Kernel Panic ---\n");
	tv_next = tv_current;
	tv_next.tv_sec += interval;
	while ((tv_current.tv_sec < tv_next.tv_sec ||
			tv_current.tv_usec < tv_next.tv_usec) &&
			g_param->sigint == 0)
	{
		if (gettimeofday(&tv_current, NULL) < 0)
		    printf(" --- Fatal Error - Kernel Panic ---\n");
	}
}
