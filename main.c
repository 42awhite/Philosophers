/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:41:44 by ablanco-          #+#    #+#             */
/*   Updated: 2024/01/30 22:14:20 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void    ft_putnbr_fd(int n, int fd)
{
        char    number;

        if (n == -2147483648)
        {
                write(fd, "-2147483648", 11);
                return ;
        }
        if (n < 0)
        {
                write(fd, "-", 1);
                n *= -1;
        }
        if (n <= 9)
        {
                number = n + '0';
                write(fd, &number, 1);
        }
        if (n >= 10)
        {
                ft_putnbr_fd(n / 10, fd);
                ft_putnbr_fd(n % 10, fd);
        }
}

void	check_death(t_phylo *philo, t_info *info)
{
	long	t_since_eat = 0;
	int		idx = 0;
	//printf("hora desde la ultima vez que comió%ld\n", philo->t_last_eat);
	while (idx < 50)
	{
		print_message("qué filo eres", &philo[idx]);
		t_since_eat = philo[idx].t_last_eat - info->start;
		printf("hora de la ultima comida = %ld, hora de start = %ld, diferencia = %ld\n", philo->t_last_eat, philo->info->start, t_since_eat);
		if (t_since_eat >= info->t_die)
		{
			philo->info->death = 1;
			printf("HA MUERTO %d\n", philo->info->death);
			return ;
		}
		if (idx == info->n_philo - 1)
			idx = 0;
		else
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
		//print_message("has taken a fork\n", philo);
		philo->info->forks[philo->fork_l] = 1;
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_l]);
		//print_message("has taken a fork\n", philo);
		//Tiempo de comida
		philo->t_last_eat = get_time(philo->info);
		//print_message("is eating\n", philo);
		ft_sleep(philo->info->t_eat);
		//Dejar tenedores
		pthread_mutex_lock(&philo->info->mutex[philo->fork_r]);
		philo->info->forks[philo->fork_r] = 0;
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_r]);
		pthread_mutex_lock(&philo->info->mutex[philo->fork_l]);
		philo->info->forks[philo->fork_l] = 0;
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_l]);		
	}
	else
	{
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_r]);
		pthread_mutex_unlock(&philo->info->mutex[philo->fork_l]);
	}
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