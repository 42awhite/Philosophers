#include "philo.h"

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
	// if (!(philo->dni % 2))
	// 	usleep(500);
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
