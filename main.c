/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2023/12/23 22:03:16 by ablanco-         ###   ########.fr       */
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
	printf("entra con %ld philos a hacer tenedores\n", info.n_philo);
	while(info.n_philo > idx)
	{
		info.forks[idx] = 0;
		printf("fork n [%d] = %d\n", idx, info.forks[idx]); 
		idx ++;
	}
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

int main(int argc, char **argv)
{
	t_info info;
	long start;
	
	if (parse(argc, argv) == -1)
		return(0);
	start = get_time();
	ft_sleep(5);
	printf("dif = %ld\n", dif_time(start, get_time()));
	info.n_philo = 5;
	printf("n philos = %ld\n", info.n_philo);
	do_fork(info);
}
