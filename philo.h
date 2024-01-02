/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanco- <ablanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:42:00 by ablanco-          #+#    #+#             */
/*   Updated: 2024/01/02 21:25:50 by ablanco-         ###   ########.fr       */
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
	pthread_mutex_t		forks[256];
}	t_info;

typedef struct s_phylo
{
	int dni;
	int fork_r;
	int fork_l;
	t_info info;
}	t_phylo;

int get_time(void);
int dif_time(int start, int now);
void ft_sleep(long ms);
int ft_perror(char *str);
int	ft_atoi(const char *str);

#endif