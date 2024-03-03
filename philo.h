/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:42:00 by ablanco-          #+#    #+#             */
/*   Updated: 2024/03/03 17:43:05 by ablanco-         ###   ########.fr       */
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
	long	t_die;
	long		t_eat; 
	long		t_sleep;
	int		n_meal; 
	int		*forks;
	long	start; 
	int 	death;
	int		n_end_eat;
	pthread_mutex_t *mutex_fork;
	pthread_mutex_t mutex_dead;
	pthread_mutex_t mutex_end_eat;
}	t_info;

typedef struct s_phylo
{
	int dni;
	int fork_r;
	int fork_l;
	int	n_i_eaten;
	long	t_last_eat;
	int		state;
	
	pthread_mutex_t mutex_time;
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
void	print_message(char *str, t_phylo *philo);
// Parseo
int		parse(int argc, char **argv);
int		save_arg(char **argv, int argc, t_info *info);
//Init
int		do_fork(t_info *info);
int		do_philos(t_phylo **philos, t_info *info);
//end
int	check_n_eats(t_phylo *philo);
void	check_death(t_phylo *philo, t_info *info);
int are_u_dead(t_phylo *philo);
//rutine
void	take_forks(t_phylo *philo);
int		eat(t_phylo *philo);
void nap(t_phylo *philo);
void *rutine(void *argv);
void	delayer(t_phylo *philo);



#endif