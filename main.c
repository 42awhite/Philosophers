/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2024/01/06 19:49:03 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

void do_philos(t_phylo *philos, t_info *info)
{
	int idx;

	idx = 0;
	printf("n philos = %d\n", info->n_philo);
	philos = (t_phylo *)malloc(info->n_philo * sizeof(t_phylo));
	while (idx < info->n_philo)
	{
		philos[idx].dni = idx + 1;		
		philos[idx].fork_l = idx;
		if (idx == (info->n_philo - 1))
			philos[idx].fork_r = 0;
		else
			philos[idx].fork_r = idx + 1;	
	//	printf("dni philos en pos %d = %d\n", idx, philos[idx].dni);
		idx++;
	}
//	int n = 0;
//	printf("El philo con dni %d tiene fork l = %d y fork r %d\n", philos[n].dni, philos[n].fork_l, philos[n].fork_r);
	free(philos);
}

int main(int argc, char **argv)
{
	t_info info;
	t_phylo philos;
	
	if (parse(argc, argv) == -1)
		return(0);
	if (save_arg(argv, argc, &info) == -1)
		return (0);
	
	do_fork(&info);
	do_philos(&philos, &info);
	info.start = get_time();
	printf("Start = %ld\n", info.start);
	//ft_sleep(5);
	
	//printf("dif = %d\n", dif_time(start, get_time()));
	//printf("n philos = %d\n", info.n_philo);
	//printf("n t_die = %d\n", info.t_die);
	//printf("n t_eat = %d\n", info.t_eat);
	//printf("n t_sleep = %d\n", info.t_sleep);
	//printf("n n_meal = %d\n", info.n_meal);
}
//CHECKEAR hacer free a los philos y a los tenedores. 