
#include "philo.h"

/*version mutex
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
*/

//Version int 
void do_fork(t_info *info)
{
	int idx;
	
	idx = 0;
	printf("entra con %d philos a hacer tenedores\n", info->n_philo);
	info->forks = (int *)malloc(info->n_philo * sizeof(int));
	while(info->n_philo > idx)
	{
		info->forks[idx] = 0;
	//	printf("fork n [%d] = %d\n", idx, info->forks[idx]); 
		idx ++;
	}
	
	//return (0);
	//printf("fork n [%d] = %d\n", idx, info->forks[idx+1]); 
}

void do_philos(t_phylo **philos, t_info *info)
{
	int idx;

	idx = 0;
	printf("n philos = %d\n", info->n_philo);
	*philos = (t_phylo *)malloc(info->n_philo * sizeof(t_phylo));
	while (idx < info->n_philo)
	{
		philos[idx]->dni = idx + 1;		
		philos[idx]->fork_l = idx;
		if (idx == (info->n_philo - 1))
			philos[idx]->fork_r = 0;
		else
			philos[idx]->fork_r = idx + 1;	
		printf("dni philos en pos %d = %d\n", idx, philos[idx]->dni);
		idx++;
	}
//	int n = 0;
//	printf("El philo con dni %d tiene fork l = %d y fork r %d\n", philos[n].dni, philos[n].fork_l, philos[n].fork_r);
	free(philos);
}
