#include "../philosophers.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	_usleep(long useconds)
{
	long	start;

	start = get_time();
	while (get_time() - start < useconds)
		usleep(500);
}
