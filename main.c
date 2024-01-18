/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2024/01/18 21:17:37 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

pthread_mutex_t mutex;

void	print_message(char *str, t_phylo *philo, t_info *info)
{
	pthread_mutex_lock(&mutex);
	printf("%ld %d %s\n", dif_time(info), philo->dni, str);
	pthread_mutex_unlock(&mutex);
	
}

void *write_hilo(void *argv)
{
	int i = 0;
	int c = 0;
	t_phylo *philos;

	philos = (t_phylo *)argv;
	
	while (i < 2)
	{
		pthread_mutex_lock(&mutex);
		c++;
		//printf("Hilo con dni = %d n aumenta c a = %d\n", *((int *)argv), c);
		printf("Hilo con dni = %d n aumenta c a = %d\n", philos->dni, c);
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
	void *single_philo;
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
	
	//TRATANDO DE PASAR PHILOS A VOIS Y LUEGO VOLVER A PASARO A T_PHILOS
	while (idx < info.n_philo)
	{
		single_philo = (void *)&philos[idx];
	//	printf("TU ERE %d\n", philos[idx].dni);
		if (pthread_create(&philos[idx].hilo, NULL, write_hilo, &single_philo) != 0) 
		{
			fprintf(stderr, "Error al crear el hilo\n");
			return 1;
		}
		print_message("esta durmiendo", &philos[idx], &info);
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