/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:33:14 by ablanco-          #+#    #+#             */
/*   Updated: 2024/02/12 20:28:01 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_sleep(long ms, t_info *info)
{
	long	start;
	long	finish;
	
	start = get_time();
	finish = start + ms;
	while (start < finish && info->death == 0)
	{
		usleep(50);
		start = get_time();
	}
}

long get_time()
{
	struct timeval	start_time;
	long				ms;

	gettimeofday(&start_time, NULL);
	ms = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	return(ms);
}

long dif_time(t_info *info)
{
	long	now;

	now = get_time();
	return (now - info->start);
}
