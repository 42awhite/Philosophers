/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:32:31 by ablanco-          #+#    #+#             */
/*   Updated: 2024/03/04 20:59:54 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_fork(t_info *info)
{
	int	idx;

	idx = 0;
	info->forks = (int *)malloc(info->n_philo * sizeof(int));
	if (!info->forks)
		return (ft_perror("Error, the blacksmith did not forge the forks"));
	while (info->n_philo > idx)
	{
		info->forks[idx] = 0;
		idx ++;
	}
	return (0);
}

int	malloc_philo(t_phylo **philos, t_info *info)
{
	*philos = (t_phylo *)malloc(info->n_philo * sizeof(t_phylo));
	if (!*philos)
		return (ft_perror("Error, philos can't born"));
	info->mutex_fork = (pthread_mutex_t *)malloc(info->n_philo
			* sizeof(pthread_mutex_t));
	if (!info->mutex_fork)
		return (ft_perror("Error malloc mutex"));
	return (0);
}

int	do_philos(t_phylo **philos, t_info *info)
{
	int	idx;

	if (malloc_philo(philos, info) == -1)
		return (-1);
	idx = 0;
	while (idx < info->n_philo)
	{
		(*philos)[idx].dni = idx + 1;
		(*philos)[idx].t_last_eat = 0;
		(*philos)[idx].state = 0;
		(*philos)[idx].n_i_eaten = 0;
		(*philos)[idx].fork_l = idx;
		if (pthread_mutex_init(&(*philos)[idx].mutex_time, NULL))
			return (ft_perror("mutex_time error"));
		if (idx == (info->n_philo - 1))
			(*philos)[idx].fork_r = 0;
		else
			(*philos)[idx].fork_r = idx + 1;
		(*philos)[idx].info = info;
		if (pthread_mutex_init(info->mutex_fork + idx, NULL))
			return (ft_perror("Mutex init error"));
		idx++;
	}
	return (0);
}
