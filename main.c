/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2024/01/31 20:55:14 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"


void	check_death(t_phylo *philo, t_info *info)
{
	long	t_since_eat = 0;
	int		idx = 0;
	//printf("hora desde la ultima vez que comió%ld\n", philo->t_last_eat);
	while (1)
	{
		//print_message("qué filo eres", &philo[idx]);
		if (idx == info->n_philo)
			idx = 0;
		t_since_eat = philo[idx].t_last_eat - info->start;
		//printf("DNI = %d, hora de la ultima comida = %ld, hora de start = %ld, diferencia = %ld\n", philo[idx].dni, philo[idx].t_last_eat, philo[idx].info->start, t_since_eat);
		if (t_since_eat >= info->t_die)
		{
			philo[idx].info->death = 1;
			printf("HA MUERTO %d\n", philo[idx].dni);
			return ;
		}
		idx++;
	}
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
		//print_message("has taken a fork", philo);
		philo->info->forks[philo->fork_l] = 1;
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_l]);
		//print_message("has taken a fork", philo);
		//Tiempo de comida
		philo->t_last_eat = get_time(philo->info);
		//print_message("is eating", philo);
		ft_sleep(philo->info->t_eat);
		
		//Dejar tenedores
		pthread_mutex_lock(&philo->info->mutex[philo->fork_r]);
		philo->info->forks[philo->fork_r] = 0;
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_r]);
		pthread_mutex_lock(&philo->info->mutex[philo->fork_l]);
		philo->info->forks[philo->fork_l] = 0;
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_l]);
		philo->think = 0;
	}
	else
	{
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_r]);
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_l]);
		philo->think = 1;
	}
}

//	CHECKEAR QUE SE PUEDAN MORIR EN MEDIO DEL FT_SLEEP
void nap(t_phylo *philo)
{
	print_message("is sleeping", philo);
	ft_sleep(philo->info->t_sleep);
	print_message("is thinking", philo);
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
		if (philo->think == 1)
		{
			//print_message("is thinking", philo);
			eat(philo);
		}
		else
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