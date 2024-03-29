/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:05:05 by ablanco-          #+#    #+#             */
/*   Updated: 2024/03/16 13:20:28 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	morido(t_phylo *philo)
{
	pthread_mutex_lock(&philo->info->mutex_end_eat);
	pthread_mutex_lock(&philo->info->mutex_dead);
	if (philo->info->n_end_eat == philo->info->n_philo
		|| philo->info->death == 1)
	{
		pthread_mutex_unlock(&philo->info->mutex_end_eat);
		pthread_mutex_unlock(&philo->info->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->mutex_dead);
	pthread_mutex_unlock(&philo->info->mutex_end_eat);
	return (0);
}

int	eat(t_phylo *philo)
{
	if (morido(philo) == 1)
		return (1);
	delayer(philo);
	pthread_mutex_lock(&philo->info->mutex_fork[philo->fork_r]);
	pthread_mutex_lock(&philo->info->mutex_fork[philo->fork_l]);
	if (morido(philo) == 0)
	{
		print_message("\033[0;33m has taken a fork \033[0m", philo);
		print_message("\033[0;33m has taken a fork \033[0m", philo);
		pthread_mutex_lock(&philo->mutex_time);
		philo->t_last_eat = get_time() - philo->info->start;
		pthread_mutex_unlock(&philo->mutex_time);
		print_message("\033[0;32m is eating \033[0m", philo);
		philo->n_i_eaten = philo->n_i_eaten + 1;
		ft_sleep(philo->info->t_eat);
		philo->state = 1;
	}
	pthread_mutex_unlock(&philo->info->mutex_fork[philo->fork_r]);
	pthread_mutex_unlock(&philo->info->mutex_fork[philo->fork_l]);
	if (morido(philo) == 1)
		return (1);
	return (0);
}

void	nap(t_phylo *philo)
{
	print_message("\033[0;36m is sleeping \033[0m", philo);
	ft_sleep(philo->info->t_sleep);
	pthread_mutex_lock(&philo->info->mutex_dead);
	if (philo->info->death == 1)
	{
		pthread_mutex_unlock(&philo->info->mutex_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->info->mutex_dead);
	print_message("\033[0;35m is thinking \033[0m", philo);
	philo->state = 0;
}

int	cant_think_alone(t_phylo *philo)
{
	if (philo->info->n_philo == 1)
	{
		ft_sleep(philo->info->t_die);
		return (1);
	}
	return (0);
}

void	*rutine(void *argv)
{
	t_phylo	*philo;
	int		end_eat;

	philo = (t_phylo *)argv;
	end_eat = 0;
	if (cant_think_alone(philo) == 1)
		return (NULL);
	if (philo->dni % 2)
		usleep(500);
	while (1)
	{
		if (philo->info->n_meal >= 0)
			end_eat = check_n_eats(philo);
		if (end_eat == 1)
			return (NULL);
		if (are_u_dead(philo) == 1)
			return (NULL);
		if (eat(philo) == 1)
			return (NULL);
		if (are_u_dead(philo) == 1)
			return (NULL);
		if (philo->state == 1)
			nap(philo);
	}
}
