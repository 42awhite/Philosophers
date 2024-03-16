/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:33:14 by ablanco-          #+#    #+#             */
/*   Updated: 2024/03/16 12:38:59 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(long ms)
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

long	get_time(void)
{
	struct timeval	start_time;
	long			ms;

	gettimeofday(&start_time, NULL);
	ms = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	return (ms);
}

long	dif_time(t_info *info)
{
	long	now;

	now = get_time();
	return (now - info->start);
}

void	delayer(t_phylo *philo)
{
	unsigned int	time_left;

	time_left = philo->info->t_die
		- (dif_time(philo->info) - philo->t_last_eat);
	time_left /= 2;
	if (time_left > philo->info->t_die || time_left > 1000)
		return ;
	usleep(time_left);
}
