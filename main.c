/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2024/01/04 17:38:02 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

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
			return(ft_perror("fork error"));
		idx ++;
	}
	return (0);
	//printf("fork n [%d] = %d\n", idx, info->forks[idx+1]); 
}


int main(int argc, char **argv)
{
	t_info info;
	//long start;
	
	if (parse(argc, argv) == -1)
		return(0);
	if (save_arg(argv, argc, &info) == -1)
		return (0);
	
	do_fork(&info);
	
	//start = get_time();
	//ft_sleep(5);
	
	//printf("dif = %d\n", dif_time(start, get_time()));
	//printf("n philos = %d\n", info.n_philo);
	//printf("n t_die = %d\n", info.t_die);
	//printf("n t_eat = %d\n", info.t_eat);
	//printf("n t_sleep = %d\n", info.t_sleep);
	//printf("n n_meal = %d\n", info.n_meal);
	
}
