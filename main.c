/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2024/01/02 21:24:28 by ablanco-         ###   ########.fr       */
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

int do_fork(t_info *info)
{
	int idx;
	//int *fork;
	
	idx = 0;
	printf("entra con %d philos a hacer tenedores\n", info->n_philo);
	while(info->n_philo > idx)
	{
		//info->forks[idx] = 0;
		//printf("fork n [%d] = %d\n", idx, info->forks[idx]); 
		if (pthread_mutex_init(&info->forks[idx], NULL) != 0)
			return (-1);
		idx ++;
	}
	return (0);
	//printf("fork n [%d] = %d\n", idx, info->forks[idx+1]); 
}

int parse(int argc, char **argv)
{
	int idx;
	int idx_str;

	idx = 1;
	if (argc <= 4 || argc > 6)
		return(ft_perror("n de arg incorrecto"));
	while (idx < argc)
	{
		idx_str = 0;
		while (argv[idx][idx_str])
		{
			if (argv[idx][idx_str] <= '0' || argv[idx][idx_str] > '9')
				return(ft_perror("invalid argument"));
			idx_str++;
		}
		idx++;
	}
	return(0);
}
int		save_arg(char **argv, int argc, t_info *info)
{
	info->n_philo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	if (info->n_philo == -1 || info->t_die == -1 || info->t_eat == -1 || info->t_sleep == -1)
		return (-1);
	if (argc == 6)
	{
		info->n_meal = ft_atoi(argv[5]);
		if (info->n_meal == -1)
			return (-1);
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_info info;
	long start;
	int	error;
	printf("size %ld\n", sizeof(pthread_mutex_t));
	if (parse(argc, argv) == -1)
		return(0);
	error = save_arg(argv, argc, &info);
	if (error == -1)
		return (0);
	
	start = get_time();
	ft_sleep(5);
	printf("dif = %d\n", dif_time(start, get_time()));
	printf("n philos = %d\n", info.n_philo);
	printf("n t_die = %d\n", info.t_die);
	printf("n t_eat = %d\n", info.t_eat);
	printf("n t_sleep = %d\n", info.t_sleep);
	printf("n n_meal = %d\n", info.n_meal);
	
	do_fork(&info);

}
