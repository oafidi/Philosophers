#include "../philosophers.h"

static void	init_philosopher(t_philosopher *philo, t_dinning *dinner, int i)
{
	philo->id = i + 1;
	philo->last_meal = get_time();
	philo->meals_eaten = 0;
	philo->l_fork = i;
	philo->r_fork = (i + 1) % dinner->nbr_philos;
	philo->dinner = dinner;
}

int	init_dinner(t_dinning *dinner)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	dinner->start_time = get_time();
	if (!init_mutex(dinner))
		return (0);
	philo = &(dinner->philos[i]);
	while (i <  dinner->nbr_philos)
	{
		init_philosopher(philo, dinner, i);
		if (pthread_create(&(philo->tid), NULL, routine, philo))
			write(2, "Failed to create a philosopher thread !!\n", 42);
		else
		{
			if (pthread_detach(philo->tid))
				write(2, "Failed to detach a philosopher thread !!\n", 42);
		}
		i++;
	}
	return (1);
}
