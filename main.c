//f time_stamp
//f time diff
//Estructuras

#include "philo.h"

long get_time(void)
{
	struct timeval start_time;
	long ms;

	gettimeofday(&start_time, NULL);
	ms = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	//printf("seg = %ld microseg = %d \n", start_time.tv_sec, start_time.tv_usec);
	//printf("miliseg = %ld\n", ms);
	return(ms);
}
void ft_sleep(long ms)
{
	long	start;
	long	finish;
	start = get_time();
	finish = start + ms;
	while (start < finish)
	{
		usleep(50);
		start = get_time();
	}
	
}

long dif_time(long start, long now)
{
	return (now - start);
}

int main(void)
{
	long start;

	start = get_time();
	ft_sleep(2000);
	printf("dif = %ld\n", dif_time(start, get_time()));

}
