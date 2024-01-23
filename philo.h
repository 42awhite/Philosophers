/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:42:00 by ablanco-          #+#    #+#             */
/*   Updated: 2024/01/23 20:21:34 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_info
{
	int		n_philo;
	int		t_die;
	int		t_eat; 
	int		t_sleep;
	int		n_meal; 
	int		*forks;
	long	start; 
	//pthread_mutex_t		forks[200];
	pthread_mutex_t *mutex;
}	t_info;

typedef struct s_phylo
{
	int dni;
	int fork_r;
	int fork_l;

	
	t_info *info;
	pthread_t hilo;
}	t_phylo;

//Funciones de tiempo
long	get_time();
long 	dif_time(t_info *info);
void	ft_sleep(long ms);
//Utils
int 	ft_perror(char *str);
int		ft_atoi(const char *str);
void	*ft_bzero(void *s, size_t n);
// Parseo
int		parse(int argc, char **argv);
int		save_arg(char **argv, int argc, t_info *info);
//Init
void	do_fork(t_info *info);
int		do_philos(t_phylo **philos, t_info *info);


#endif