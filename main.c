/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2023/12/22 13:20:22 by pc               ###   ########.fr       */
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

void do_fork(t_info info)
{
	int idx;
	//int *fork;
	
	idx = 0;
	printf("entra con %d philos a hacer tenedores\n", info.n_philo);
	while(info.n_philo > idx)
	{
		info.forks[idx] = 0;
		printf("fork n [%d] = %d\n", idx, info.forks[idx]); 
		idx ++;
	}
}

int main(void)
{
	t_info info;
	long start;
	
	start = get_time();
	ft_sleep(5);
	printf("dif = %ld\n", dif_time(start, get_time()));
	info.n_philo = 5;
	printf("n philos = %d\n", info.n_philo);
	do_fork(info);
}
