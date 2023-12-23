/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:42:00 by ablanco-          #+#    #+#             */
/*   Updated: 2023/12/23 22:02:12 by ablanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_info
{
	long	n_philo;
	long	t_die;
	long	t_eat; 
	long	t_sleep;
	long	n_meal;
	int		forks[];
}	t_info;

typedef struct s_phylo
{
	int dni;
	int fork_r;
	int fork_l;
	t_info info;
}	t_phylo;

long get_time(void);
long dif_time(long start, long now);
void ft_sleep(long ms);
int ft_perror(char *str);

#endif