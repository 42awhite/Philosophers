/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2024/03/11 20:01:50 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_phylo *philos, t_info *info)
{
	int	idx;

	idx = 0;
	while (idx < info->n_philo)
	{
		pthread_mutex_destroy(&philos[idx].mutex_time);
		pthread_mutex_destroy(&info->mutex_fork[idx]);
		idx++;
	}
	pthread_mutex_destroy(&info->mutex_dead);
	pthread_mutex_destroy(&info->mutex_end_eat);
	free(info->forks);
	free(info->mutex_fork);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_phylo	*philos;
	void	*single_philo;
	int		idx;

	idx = 0;
	if (check_all_ok(argc, argv, &info, &philos) == -1)
		return (0);
	info.start = get_time();
	while (info.n_philo > idx)
	{
		single_philo = (void *)&philos[idx];
		if (pthread_create(&philos[idx].hilo, NULL, rutine, single_philo) != 0)
			return (0);
		idx++;
	}
	check_death(philos, &info);
	idx = 0;
	while (idx < info.n_philo)
	{
		if (pthread_join(philos[idx].hilo, NULL) != 0)
			return (0);
		idx++;
	}
	free_philo(philos, &info);
}
