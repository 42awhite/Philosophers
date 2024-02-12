/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 21:06:40 by ablanco-          #+#    #+#             */
/*   Updated: 2024/02/12 16:05:06 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_perror(char *str)
{
	printf("%s\n", str);
	return(-1);
}

void	print_message(char *str, t_phylo *philo)
{
	//pthread_mutex_lock(&mutex);
	printf("%ldms %d %s\n", dif_time(philo->info), philo->dni, str);
	//pthread_mutex_unlock(&mutex);
}

int	ft_atoi(const char *str)
{
	int		c;
	int		neg;
	long	dest;

	c = 0;
	neg = 1;
	dest = 0;
	while ((str[c] == ' ') || (str[c] >= 9 && str[c] <= 13))
		c++;
	if (str[c] == '-' || str[c] == '+')
	{
		if (str[c] == '-')
		neg = neg * -1;
		c++;
	}
	while (str[c] >= '0' && str[c] <= '9')
		dest = (str[c++] - '0') + (dest * 10);
	if (dest > INT_MAX && neg == 1)
		return (-1);
	else if (dest < INT_MIN && neg == -1)
		return (-1);
	return (dest * neg);
}

void	*ft_bzero(void *s, size_t n)
{
	size_t	q;
	char	*str;

	str = s;
	q = 0;
	while (q < n)
	{
		str[q] = '\0';
		q++;
	}
	return (str);
}

