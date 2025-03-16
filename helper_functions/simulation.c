/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:41:43 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/16 07:16:56 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	get_dead_flag(t_dinning *dinner)
{
	int	dead;

	pthread_mutex_lock(&dinner->dead);
	dead = dinner->is_dead;
	pthread_mutex_unlock(&dinner->dead);
	return (dead);
}

void	set_dead_flag(t_dinning *dinner, int value)
{
	pthread_mutex_lock(&dinner->dead);
	dinner->is_dead = value;
	pthread_mutex_unlock(&dinner->dead);
}

static int	have_eating(t_dinning *dinner)
{
	int	i;
	int	count;
	int	meals_eaten;

	count = 0;
	i = 0;
	while (i < dinner->nbr_philos)
	{
		pthread_mutex_lock(&dinner->meals);
		meals_eaten = dinner->philos[i].meals_eaten;
		pthread_mutex_unlock(&dinner->meals);
		if (dinner->nbr_meals <= meals_eaten)
			count++;
		i++;
	}
	return (count == dinner->nbr_meals);
}

void	*supervisor(void *arg)
{
	int				i;
	long			last_time;
	t_philosopher	*philo;
	t_dinning		*dinner;

	//usleep(10000000);
	dinner = (t_dinning *)arg;
	while (1)
	{
		//printf("Dead Flag -->%d\n", get_dead_flag(dinner));
		if (dinner->nbr_meals && have_eating(dinner))
			return (set_dead_flag(dinner, 1), NULL);
		//printf("Dead Flag -->%d\n", get_dead_flag(dinner));
		i = 0;
		while (i < dinner->nbr_philos)
		{
			philo = &dinner->philos[i];
			pthread_mutex_lock(&dinner->meals);
			last_time = philo->last_meal;
			pthread_mutex_unlock(&dinner->meals);
			//printf("difference -->%ld\n",get_time() - last_time );
			if (get_time() - last_time > dinner->time2die)
			{
				print("died", i + 1, dinner);
				//printf("Dead Flag -->%d\n", get_dead_flag(dinner));
				return (set_dead_flag(dinner, 1), NULL);
			}

			usleep(500);
			i++;
		}
	}
}

void do_this(t_philosopher *philo)
{
	if (!get_dead_flag(philo->dinner))
	{
		pthread_mutex_lock(&philo->dinner->forks[philo->l_fork]);
		print("has taken a fork", philo->id, philo->dinner);
		//write(2, "Hello\n", 7);
		pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
	}
}
void	*routine(void *arg)
{
	t_philosopher	*philo;
//write(2, "Hello\n", 7);

	philo = (t_philosopher *)arg;
//printf("Dead Flag -->%d\n", get_dead_flag(philo->dinner));
	if (philo->dinner->nbr_philos == 1)
		return (do_this(philo), NULL);
	if (philo->id % 2 == 1)
		eat_action(philo);
	//write(2, "Hello\n", 7);
	//printf("Dead Flag -->%d\n", get_dead_flag(philo->dinner));
	while (!get_dead_flag(philo->dinner))
	{//printf("Dead Flag -->%d\n", get_dead_flag(philo->dinner));
		//write(2, "Hello\n", 7);
		sleep_action(philo);
		//printf("Dead Flag -->%d\n", get_dead_flag(philo->dinner));
		think_action(philo);
		//printf("Dead Flag -->%d\n", get_dead_flag(philo->dinner));
		eat_action(philo);
	}
	return (NULL);
}
