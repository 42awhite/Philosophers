/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2024/01/26 18:44:22 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	print_message(char *str, t_phylo *philo)
{
	//pthread_mutex_lock(&mutex);
	printf("%ld %d %s\n", dif_time(philo->info), philo->dni, str);
	//pthread_mutex_unlock(&mutex);
}

void	eat(t_phylo *philo)
{
	pthread_mutex_lock(&philo->info->mutex[philo->fork_r]);
	pthread_mutex_lock(&philo->info->mutex[philo->fork_l]);
	if (philo->info->forks[philo->fork_r] == 0 && philo->info->forks[philo->fork_l] == 0)
	{
		//Coger tedenedores
		philo->info->forks[philo->fork_r] = 1;
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_r]);
		print_message("has taken a fork\n", philo);
		philo->info->forks[philo->fork_l] = 1;
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_l]);
		print_message("has taken a fork\n", philo);
		//Tiempo de comida
		philo->t_last_eat = 0;
		usleep(philo->info->t_eat * 1000);
		print_message("is eating\n", philo);
		//Dejar tenedores
		pthread_mutex_lock(&philo->info->mutex[philo->fork_r]);
		philo->info->forks[philo->fork_r] = 0;
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_r]);
		pthread_mutex_lock(&philo->info->mutex[philo->fork_l]);
		philo->info->forks[philo->fork_l] = 0;
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_l]);		
	}
	else
	{
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_r]);
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_l]);
	}
}

void *rutine(void *argv)
{
	int i = 0;
	// int c = 0;
	t_phylo *philo;

	philo = (t_phylo *)argv;
	eat(philo);
	
	return NULL;
}

int main(int argc, char **argv)
{
	t_info info;
	t_phylo *philos;
	void *single_philo;
	int idx = 0;
	
	if (parse(argc, argv) == -1)
		return(0);
	if (save_arg(argv, argc, &info) == -1)
		return(0);
	do_fork(&info);
	if (do_philos(&philos, &info) == -1)
		return(0);
	
	info.start = get_time();
	
	while (idx < info.n_philo)
	{
		single_philo = (void *)&philos[idx];
	//	printf("TU ERE %d\n", philos[idx].dni);
		if (pthread_create(&philos[idx].hilo, NULL, rutine, single_philo) != 0) 
		{
			fprintf(stderr, "Error al crear el hilo\n");
			return 1;
		}
		///print_message("esta durmiendo", &philos[idx], &info);
		idx++;
	}
	
	// Esperar a que el hilo termine
	idx = 0;
	while (idx < info.n_philo)
	{
    	if (pthread_join(philos[idx].hilo, NULL) != 0) 
		{
    		fprintf(stderr, "Error al esperar al hilo\n");
    		return 1;
		}
		idx++;
	}
}

//CHECKEAR hacer free a: 
//los philos 
//los tenedores. 
//los mutex