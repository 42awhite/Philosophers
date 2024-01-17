

#include "philo.h"

int parse(int argc, char **argv)
{
	int idx;
	int idx_str;

	idx = 1;
	if (argc <= 4 || argc > 6)
		return(ft_perror("n de arg incorrecto"));
	while (idx < argc)
	{
		idx_str = 0;
		while (argv[idx][idx_str])
		{
			if (argv[idx][idx_str] < '0' || argv[idx][idx_str] > '9')
				return(ft_perror("invalid argument"));
			idx_str++;
		}
		idx++;
	}
	return(0);
}

int		save_arg(char **argv, int argc, t_info *info)
{
	info->n_philo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	if (info->n_philo == -1 || info->t_die == -1 || info->t_eat == -1 || info->t_sleep == -1)
		return(ft_perror("atoi error"));
	if (info->n_philo > 200)
		return(ft_perror("no caben tantos filósofos en la mesa"));
	info->n_meal = -1;
	if (argc == 6)
	{
		info->n_meal = ft_atoi(argv[5]);
		if (info->n_meal == -1)
			return(ft_perror("atoi n_meal error"));
	}
	return (1);
}
