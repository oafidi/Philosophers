#include "../philosophers.h"

//have eating
//supervisor

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 1)
	{
		print("is sleeping", philo->id, philo->dinner);
		precise_usleep(philo->dinner->time2sleep);
	}
	while (get_time() - philo->last_meal < philo->dinner->time2die)
	{
		pthread_mutex_lock(&philo->dinner->forks[philo->l_fork]);
		print("has taken a fork", philo->id, philo->dinner);
		pthread_mutex_lock(&philo->dinner->forks[philo->r_fork]);
		print("has taken a fork", philo->id, philo->dinner);
		print("is eating", philo->id, philo->dinner);
		philo->meals_eaten++;
		precise_usleep(philo->dinner->time2eat);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
		print("is thinking", philo->id, philo->dinner);
		print("is sleeping", philo->id, philo->dinner);
		precise_usleep(philo->dinner->time2sleep);
	}
	print("is dead", philo->id, philo->dinner);
	return (NULL);
}
