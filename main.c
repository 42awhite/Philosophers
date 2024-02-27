/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2024/02/27 21:08:52 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

//DEBERES: 
//harcodear que se muera en x tiempo si el numero de philo es 1
//Liberar memoria e hilos
//Y la P formula

int	check_all_ok(int argc, char **argv, t_info *info, t_phylo **philos)
{
	if (parse(argc, argv) == -1)
		return(-1);
	if (save_arg(argv, argc, info) == -1)
		return(-1);
	if (do_fork(info) == -1)
		return(-1);
	if (do_philos(philos, info) == -1)
		return(-1);
	return (0);
}

int main(int argc, char **argv)
{
	t_info info;
	t_phylo *philos;
	void *single_philo;
	int idx = 0;
	
	if (check_all_ok(argc, argv, &info, &philos) == -1)
		return(0);
	//if (parse(argc, argv) == -1)
	//	return(0);
	//if (save_arg(argv, argc, &info) == -1)
	//	return(0);
	//do_fork(&info);
	//if (do_philos(&philos, &info) == -1)
	//	return(0);
	
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
//n_eats será = -1 si no se especifica en el argv
//State: 0 si aun no h an comido; 1 si han comido tienen que dormir;

//CHECKEAR hacer free a: 
//los philos 
//los tenedores. 
//los mutex