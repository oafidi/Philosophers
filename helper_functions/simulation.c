/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:41:43 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/18 23:14:23 by oafidi           ###   ########.fr       */
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
	return (count == dinner->nbr_philos);
}

void	*supervisor(void *arg)
{
	int				i;
	long			last_time;
	t_philosopher	*philo;
	t_dinning		*dinner;

	dinner = (t_dinning *)arg;
	while (1)
	{
		if (dinner->nbr_meals && have_eating(dinner))
			return (set_dead_flag(dinner, 1), NULL);
		i = 0;
		while (i < dinner->nbr_philos)
		{
			philo = &dinner->philos[i];
			pthread_mutex_lock(&dinner->meals);
			last_time = philo->last_meal;
			pthread_mutex_unlock(&dinner->meals);
			if (get_time() - last_time > dinner->time2die)
				return (print("died", i + 1, dinner), NULL);
			i++;
		}
		usleep(500);
	}
}

void one_philo(t_philosopher *philo)
{
	if (!get_dead_flag(philo->dinner))
	{
		pthread_mutex_lock(&philo->dinner->forks[philo->l_fork]);
		print("has taken a fork", philo->id, philo->dinner);
		pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
	}
}
void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->dinner->nbr_philos == 1)
		return (one_philo(philo), NULL);
	if (philo->id % 2 == 1)
		eat_action(philo);
	while (!get_dead_flag(philo->dinner))
	{
		sleep_action(philo);
		think_action(philo);
		eat_action(philo);
	}
	return (NULL);
}
