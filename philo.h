/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:42:00 by ablanco-          #+#    #+#             */
/*   Updated: 2024/01/06 19:46:08 by ablanco-         ###   ########.fr       */
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
	long	start; //añadir info a int start ;)
	//pthread_mutex_t		forks[200];
}	t_info;

typedef struct s_phylo
{
	int dni;
	int fork_r;
	int fork_l;
	pthread_t hilo;
	t_info *info;
}	t_phylo;

long	get_time();
int 	dif_time(int start, int now);
void	ft_sleep(long ms);
int 	ft_perror(char *str);
int		ft_atoi(const char *str);
void	*ft_bzero(void *s, size_t n);
void	ft_sleep(long ms);
int		parse(int argc, char **argv);
int		save_arg(char **argv, int argc, t_info *info);


#endif