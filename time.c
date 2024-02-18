/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:33:14 by ablanco-          #+#    #+#             */
/*   Updated: 2024/02/18 18:58:12 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_sleep(long ms, t_info *info)
{
	long	start;
	long	finish;
	
	start = get_time();
	finish = start + ms;
	pthread_mutex_lock(&info->mutex_dead);
	while (start < finish && info->death == 0)
	{
		usleep(50);
		start = get_time();
	}
	pthread_mutex_unlock(&info->mutex_dead);
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
