/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2024/01/16 19:23:46 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

pthread_mutex_t mutex;

void *write_hilo(void *argv)
{
	int i = 0;
	int c = 0;
	
	while (i < 2)
	{
	pthread_mutex_lock(&mutex);
	c++;
	printf("Hilo con dni = %d n aumenta c a = %d\n", *((int *)argv), c);
	sleep(3);
	pthread_mutex_unlock(&mutex);
	i++;
	}
	return NULL;
}

int main(int argc, char **argv)
{
	t_info info;
	t_phylo *philos;
	int idx = 0;
	
	if (parse(argc, argv) == -1)
		return(0);
	if (save_arg(argv, argc, &info) == -1)
		return (0);
	
	do_fork(&info);
	do_philos(&philos, &info);
	info.start = get_time();
	
	if (pthread_mutex_init(&mutex, NULL) != 0) 
	{
        fprintf(stderr, "Error al inicializar el mutex\n");
        return 1;
    }
	while (idx < info.n_philo)
	{
		printf("TU ERE %d\n", philos[idx].dni);
		if (pthread_create(&philos[idx].hilo, NULL, write_hilo, &philos[idx].dni) != 0) 
		{
			fprintf(stderr, "Error al crear el hilo\n");
			return 1;
		}
		idx++;
	}
	
	// Esperar a que el hilo termine (opcional)
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
	//printf("Start = %ld\n", info.start);
	//printf("dif = %d\n", dif_time(start, get_time()));
	//printf("n philos = %d\n", info.n_philo);
	//printf("n t_die = %d\n", info.t_die);
	//printf("n t_eat = %d\n", info.t_eat);
	//printf("n t_sleep = %d\n", info.t_sleep);
	//printf("n n_meal = %d\n", info.n_meal);
}

//CHECKEAR hacer free a: 
//los philos 
//los tenedores. 
//los mutex