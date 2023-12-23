/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:42:00 by ablanco-          #+#    #+#             */
/*   Updated: 2023/12/22 13:17:12 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
#include <pthread.h>

typedef struct s_info
{
	int	n_philo;
	int	forks[];
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

#endif