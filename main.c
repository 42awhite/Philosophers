/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2024/02/12 15:59:58 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"


void	check_death(t_phylo *philo, t_info *info)
{
	//long	t_since_eat = 0;
	int		idx = 0;
	//printf("hora desde la ultima vez que comió%ld\n", philo->t_last_eat);
	while (1)
	{
		//print_message("qué filo eres", &philo[idx]);
		if (idx == info->n_philo)
			idx = 0;
		//printf("DNI = %d, hora de la ultima comida = %ld, hora de start = %ld, t muerte = %ld\n", philo[idx].dni, philo[idx].t_last_eat, philo[idx].info->start, info->t_die);
		if ((dif_time(info) - philo[idx].t_last_eat) >= info->t_die)
		{
			philo[idx].info->death = 1;
			print_message("\033[0;31m is dead \033[0m", &philo[idx]);
			return ;
		}
		usleep(1000);
		idx++;
	}
}

void	eat(t_phylo *philo)
{
	while(1)
	{
		pthread_mutex_lock(&philo->info->mutex[philo->fork_r]);
		pthread_mutex_lock(&philo->info->mutex[philo->fork_l]);
		if (philo->info->forks[philo->fork_r] == 0 && philo->info->forks[philo->fork_l] == 0)
		{
			//Coger tedenedores
			philo->info->forks[philo->fork_r] = 1;
			philo->info->forks[philo->fork_l] = 1;
			pthread_mutex_unlock(&philo->info->mutex[philo->fork_r]);
			pthread_mutex_unlock(&philo->info->mutex[philo->fork_l]);
			print_message("\033[0;33m has taken a fork \033[0m", philo);
			print_message("\033[0;33m has taken a fork \033[0m", philo);
			//Tiempo de comida
			philo->t_last_eat = get_time(philo->info) - philo->info->start;
			print_message("\033[0;32m is eating \033[0m", philo);
			//printf("\033[0;31m%4ldms %d is eating / %ld\n\033[0m", dif_time(philo->info), philo->dni, philo->t_last_eat);
			ft_sleep(philo->info->t_eat);
			philo->think = 0;

			pthread_mutex_lock(&philo->info->mutex[philo->fork_r]);
			pthread_mutex_lock(&philo->info->mutex[philo->fork_l]);
			//Dejar tenedores
			philo->info->forks[philo->fork_r] = 0;
			philo->info->forks[philo->fork_l] = 0;
		}
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_r]);
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_l]);
		if (philo->think == 0)
			break;
	}
}

//	CHECKEAR QUE SE PUEDAN MORIR EN MEDIO DEL FT_SLEEP
void nap(t_phylo *philo)
{
	print_message("\033[0;36m is sleeping \033[0m", philo);
	ft_sleep(philo->info->t_sleep);
	print_message("\033[0;35m is thinking \033[0m", philo);
	philo->think = 1;
}

void *rutine(void *argv)
{
	//int i = 0;
	t_phylo *philo;
	philo = (t_phylo *)argv;
	while (1)
	{
		if (philo->info->death == 1)
			return NULL;
		eat(philo);
		if (philo->info->death == 1)
			return NULL;
		nap(philo);
	}
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
	
	while (info.n_philo > idx)
	{
		single_philo = (void *)&philos[idx];
		//printf("Hemos hecho bien la meurte %d\n", philos[idx].info->death);
	//	printf("TU ERE %d\n", philos[idx].dni);
		if (pthread_create(&philos[idx].hilo, NULL, rutine, single_philo) != 0) 
		{
			fprintf(stderr, "Error al crear el hilo\n");
			return 1;
		}
		///print_message("esta durmiendo", &philos[idx], &info);
		idx++;
	}
	check_death(philos, &info);
	
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

//n_philos	t_to_die	t_to_eat	t_to_sleep

//CHECKEAR hacer free a: 
//los philos 
//los tenedores. 
//los mutex