/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2024/01/25 21:52:12 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

//pthread_mutex_t mutex;

void	print_message(char *str, t_phylo *philo)
{
	//pthread_mutex_lock(&mutex);
	printf("%ld %d %s\n", dif_time(philo->info), philo->dni, str);
	//pthread_mutex_unlock(&mutex);
	
}

void *write_hilo(void *argv)
{
	int i = 0;
	// int c = 0;
	t_phylo *philos;

	philos = (t_phylo *)argv;
	
	//MIRAR POR QUÉ COMEN A LA VEZ 2 PHILOS
	if (philos->info->forks[philos->fork_r] == 0 && philos->info->forks[philos->fork_l] == 0)
	{
		//Coger tedenedores
		pthread_mutex_lock(&philos->info->mutex[philos->fork_r]);
		philos->info->forks[philos->fork_r] = 1;
		pthread_mutex_unlock(&philos->info->mutex[philos->fork_r]);
		print_message("has taken a fork\n", philos);
		pthread_mutex_lock(&philos->info->mutex[philos->fork_l]);
		philos->info->forks[philos->fork_l] = 1;
		pthread_mutex_unlock(&philos->info->mutex[philos->fork_l]);
		print_message("has taken a fork\n", philos);
		//Tiempo de comida
		usleep(philos->info->t_eat * 1000);
		print_message("is eating\n", philos);
		//Dejar tenedores
		pthread_mutex_lock(&philos->info->mutex[philos->fork_r]);
		philos->info->forks[philos->fork_r] = 0;
		pthread_mutex_unlock(&philos->info->mutex[philos->fork_r]);
		pthread_mutex_lock(&philos->info->mutex[philos->fork_l]);
		philos->info->forks[philos->fork_l] = 0;
		pthread_mutex_unlock(&philos->info->mutex[philos->fork_l]);		
	}
	
	//while (i < 10)
	//{
		//AYUDA DE V
		//printf("Soy el filósofo %d y voy a coger el fork %p\n", philos->dni, philos->info->mutex + (philos->dni % 2));
		//pthread_mutex_lock(philos->info->mutex + (philos->dni % 2));
		//printf("Soy el filósofo %d y he cogido el fork %p\n", philos->dni, philos->info->mutex + (philos->dni % 2));
		//printf("Soy el filósofo %d y voy a coger el fork %p\n", philos->dni, philos->info->mutex + ((philos->dni + 1 ) % 2));
		//pthread_mutex_lock(philos->info->mutex + ((philos->dni + 1 ) % 2));
		//printf("Soy el filósofo %d y he cogido el fork %p\n", philos->dni, philos->info->mutex + ((philos->dni + 1 ) % 2));
		//sleep(1);
		//printf("Soy el filósofo %d y voy a soltar los tenedores\n", philos->dni);
		//pthread_mutex_unlock(philos->info->mutex + ((philos->dni + 1 ) % 2));
		//pthread_mutex_unlock(philos->info->mutex + (philos->dni % 2));
		//i++;
		//sleep(1);

		// pthread_mutex_lock(&mutex);
		// c++;
		// //printf("\tFROM THREAD -> %p\n", philos);
		// //printf("Hilo con dni = %d n aumenta c a = %d\n", *((int *)argv), c);
		// printf("Hilo con dni = %d n aumenta c a = %d\n", philos->dni, c);
		// sleep(3);
		// pthread_mutex_unlock(&mutex);
		// i++;
	//}
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
	
	//BORRAR SI EL MUTEZ DE LA ESTRUCTURA FUNCIONA
	//if (pthread_mutex_init(&mutex, NULL) != 0) 
	//{
    //    fprintf(stderr, "Error al inicializar el mutex\n");
    //    return 1;
    //}
	
	//TRATANDO DE PASAR PHILOS A VOIS Y LUEGO VOLVER A PASARO A T_PHILOS
	while (idx < info.n_philo)
	{
		single_philo = (void *)&philos[idx];
	//	printf("TU ERE %d\n", philos[idx].dni);
		if (pthread_create(&philos[idx].hilo, NULL, write_hilo, single_philo) != 0) 
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