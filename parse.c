/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:00:50 by ablanco-          #+#    #+#             */
/*   Updated: 2024/03/16 13:14:34 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_ok(int argc, char **argv, t_info *info, t_phylo **philos)
{
	if (parse(argc, argv) == -1)
		return (-1);
	if (save_arg(argv, argc, info) == -1)
		return (-1);
	if (do_philos(philos, info) == -1)
		return (-1);
	return (0);
}

int	parse(int argc, char **argv)
{
	int	idx;
	int	idx_str;

	idx = 1;
	if (argc <= 4 || argc > 6)
		return (ft_perror("n de arg incorrecto"));
	while (idx < argc)
	{
		idx_str = 0;
		while (argv[idx][idx_str])
		{
			if (argv[idx][idx_str] < '0' || argv[idx][idx_str] > '9')
				return (ft_perror("invalid argument"));
			idx_str++;
		}
		idx++;
	}
	return (0);
}

int	save_arg(char **argv, int argc, t_info *info)
{
	info->n_philo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	info->n_end_eat = 0;
	info->death = 0;
	if (pthread_mutex_init(&info->mutex_dead, NULL))
		ft_perror("mutex_dead error");
	if (pthread_mutex_init(&info->mutex_end_eat, NULL))
		ft_perror("mutex_end_eat error");
	if (info->n_philo == -1 || info->t_die == -1 || info->t_eat == -1
		|| info->t_sleep == -1)
		return (ft_perror("atoi error"));
	if (info->n_philo > 200)
		return (ft_perror("no caben tantos filósofos en la mesa"));
	if (argc == 6)
	{
		info->n_meal = ft_atoi(argv[5]);
		if (info->n_meal == -1)
			return (ft_perror("atoi n_meal error"));
	}
	else
		info->n_meal = -1;
	return (1);
}
