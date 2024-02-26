/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2024/02/26 20:35:29 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

//DEBERES: 
//n_eats será = -1 si no se especifica en el argv
//POR QUE AHORA SE MUEREN ANTES DE TIEMPO, CHECKEAR
//State: 0 si aun no h an comido; 1 si han comido tienen que dormir;


void	take_forks(t_phylo *philo)
{
		pthread_mutex_lock(&philo->info->mutex_fork[philo->fork_r]);
		pthread_mutex_lock(&philo->info->mutex_fork[philo->fork_l]);
		if (philo->info->forks[philo->fork_r] == 0 && philo->info->forks[philo->fork_l] == 0)
		{
			//Coger tedenedores
			philo->info->forks[philo->fork_r] = 1;
			philo->info->forks[philo->fork_l] = 1;
			pthread_mutex_unlock(&philo->info->mutex_fork[philo->fork_r]);
			pthread_mutex_unlock(&philo->info->mutex_fork[philo->fork_l]);
			print_message("\033[0;33m has taken a fork \033[0m", philo);
			print_message("\033[0;33m has taken a fork \033[0m", philo);
			//Tiempo de comida
			pthread_mutex_lock(&philo->mutex_time);
			philo->t_last_eat = get_time(philo->info) - philo->info->start;
			pthread_mutex_unlock(&philo->mutex_time);
			print_message("\033[0;32m is eating \033[0m", philo);
			philo->n_i_eaten = philo->n_i_eaten + 1;
			
			ft_sleep(philo->info->t_eat);
			
			philo->state = 1;
			
			pthread_mutex_lock(&philo->info->mutex_fork[philo->fork_r]);
			pthread_mutex_lock(&philo->info->mutex_fork[philo->fork_l]);
			//Dejar tenedores
			philo->info->forks[philo->fork_r] = 0;
			philo->info->forks[philo->fork_l] = 0;
		}
		pthread_mutex_unlock(&philo->info->mutex_fork[philo->fork_r]);
		pthread_mutex_unlock(&philo->info->mutex_fork[philo->fork_l]);
}

void	eat(t_phylo *philo)
{
	while(1)
	{
		pthread_mutex_lock(&philo->info->mutex_end_eat);
		pthread_mutex_lock(&philo->info->mutex_dead);
		if (philo->info->n_end_eat == philo->info->n_philo || philo->info->death == 1)
		{
			pthread_mutex_unlock(&philo->info->mutex_end_eat);
			pthread_mutex_unlock(&philo->info->mutex_dead);
			return ;
		}
		pthread_mutex_unlock(&philo->info->mutex_dead);			
		pthread_mutex_unlock(&philo->info->mutex_end_eat);
		take_forks(philo);
		if (philo->state == 1)
			break;
	}
}


void nap(t_phylo *philo)
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

void *rutine(void *argv)
{
	t_phylo *philo;
	philo = (t_phylo *)argv;
	int end_eat;
	
	end_eat = 0;
//	if (!(philo->dni % 2))
//		usleep(50);
	while (1)
	{
		//chequea si todos han llegado al n_comidas
		if (philo->info->n_meal >= 0)
			end_eat = check_n_eats(philo);
		if (end_eat == 1)
			return NULL;
		if(are_u_dead(philo) == 1)
			return NULL;
		//Comer
		eat(philo);
		if(are_u_dead(philo) == 1)
			return NULL;
		//Dormir y pensar
		if (philo->state == 1)
			nap(philo);
	}
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
		if (pthread_create(&philos[idx].hilo, NULL, rutine, single_philo) != 0) 
		{
			fprintf(stderr, "Error al crear el hilo\n");
			return 1;
		}
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