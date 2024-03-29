/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:21:46 by ablanco-          #+#    #+#             */
/*   Updated: 2024/03/16 13:12:13 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_eat(t_phylo *philo)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&philo->info->mutex_end_eat);
	if (philo->info->n_end_eat == philo->info->n_philo)
		flag = 1;
	pthread_mutex_unlock(&philo->info->mutex_end_eat);
	return (flag);
}

int	check_n_eats(t_phylo *philo)
{
	pthread_mutex_lock(&philo->info->mutex_end_eat);
	if (philo->n_i_eaten == philo->info->n_meal)
		philo->info->n_end_eat = philo->info->n_end_eat + 1;
	pthread_mutex_unlock(&philo->info->mutex_end_eat);
	if (end_eat(philo) == 1)
		return (1);
	return (0);
}

void	check_death(t_phylo *philo, t_info *info)
{
	int	idx;

	idx = 0;
	while (1)
	{
		if (idx == info->n_philo)
			idx = 0;
		if (end_eat(&philo[idx]) == 1)
			return ;
		pthread_mutex_lock(&philo[idx].mutex_time);
		if ((dif_time(info) - philo[idx].t_last_eat) >= info->t_die)
		{
			pthread_mutex_unlock(&philo[idx].mutex_time);
			pthread_mutex_lock(&info->mutex_dead);
			philo[idx].info->death = 1;
			pthread_mutex_unlock(&info->mutex_dead);
			print_message("\033[0;31m is dead \033[0m", &philo[idx]);
			return ;
		}
		pthread_mutex_unlock(&philo[idx].mutex_time);
		idx++;
		usleep(1000);
	}
}

int	are_u_dead(t_phylo *philo)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&philo->info->mutex_dead);
	if (philo->info->death == 1)
		flag = 1;
	pthread_mutex_unlock(&philo->info->mutex_dead);
	return (flag);
}
