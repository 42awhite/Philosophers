
#include "philo.h"

void do_fork(t_info *info)
{
	int idx;
	
	idx = 0;
	info->forks = (int *)malloc(info->n_philo * sizeof(int));
	while(info->n_philo > idx)
	{
		info->forks[idx] = 0;
		idx ++;
	}
}

int	do_philos(t_phylo **philos, t_info *info)
{
	int idx;

	idx = 0;
	printf("n philos = %d\n", info->n_philo);
	*philos = (t_phylo *)malloc(info->n_philo * sizeof(t_phylo));
	if (!*philos)
		ft_perror("Error, philos can't born");
	info->mutex_fork = (pthread_mutex_t *)malloc(info->n_philo * sizeof(pthread_mutex_t));
	if (!info->mutex_fork)
		ft_perror("Error malloc mutex");
	while (idx < info->n_philo)
	{
		//printf("\tFROM ALLOCATOR -> %p\n", (*philos) + idx);
		(*philos)[idx].dni = idx + 1;
		(*philos)[idx].t_last_eat = 0;
		(*philos)[idx].state = 0;
		(*philos)[idx].n_i_eaten = 0;
		(*philos)[idx].fork_l = idx;
		if (pthread_mutex_init(&(*philos)[idx].mutex_time, NULL))
			return(ft_perror("mutex_time error"));
		if (idx == (info->n_philo - 1))
			(*philos)[idx].fork_r = 0;
		else
			(*philos)[idx].fork_r = idx + 1;	
		(*philos)[idx].info = info;
		if (pthread_mutex_init(info->mutex_fork + idx, NULL))
			return(ft_perror("Mutex init error"));
		printf("dni philos en pos %d = %d\n", idx, (*philos)[idx].dni);
		idx++;
	}
	return(0);
//	int n = 0;
//	printf("El philo con dni %d tiene fork l = %d y fork r %d\n", philos[n].dni, philos[n].fork_l, philos[n].fork_r);
	//free(philos);
}
