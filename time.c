/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:33:14 by ablanco-          #+#    #+#             */
/*   Updated: 2024/01/04 17:26:49 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_sleep(long ms)
{
	long	start;
	long	finish;
	start = get_time();
	finish = start + ms;
	while (start < finish)
	{
		usleep(50);
		start = get_time();
	}
}

int get_time(void)
{
	struct timeval	start_time;
	int				ms;

	gettimeofday(&start_time, NULL);
	ms = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	return(ms);
}

int dif_time(int start, int now)
{
	return (now - start);
}
