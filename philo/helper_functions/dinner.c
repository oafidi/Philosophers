/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:40:45 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/21 10:57:12 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	one_philo(t_philosopher *philo)
{
	if (!get_dead_flag(philo->dinner))
	{
		pthread_mutex_lock(&philo->dinner->forks[philo->l_fork]);
		print("has taken a fork", philo->id, philo->dinner);
		pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
	}
}

static void	init_philosopher(t_dinning *dinner)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	while (i < dinner->nbr_philos)
	{
		philo = &(dinner->philos[i]);
		philo->id = i + 1;
		pthread_mutex_lock(&dinner->meals);
		philo->last_meal = get_time();
		philo->meals_eaten = 0;
		pthread_mutex_unlock(&dinner->meals);
		philo->l_fork = i;
		philo->r_fork = (i + 1) % dinner->nbr_philos;
		philo->dinner = dinner;
		i++;
	}
}

static int	create_philosophers(t_dinning *dinner)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	while (i < dinner->nbr_philos)
	{
		philo = &(dinner->philos[i]);
		pthread_mutex_lock(&dinner->meals);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&dinner->meals);
		if (pthread_create(&(philo->tid), NULL, routine, philo))// kol philo ghaymchi ydir routine
		{
			set_dead_flag(dinner, 1);
			write(2, "Failed to create a philosopher thread !!\n", 42);
			return (i);
		}
		i++;
	}
	return (i);
}

static void	join_philosophers(t_dinning *dinner, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_join(dinner->philos[i].tid, NULL))
		{
			set_dead_flag(dinner, 1);
			write(2, "Failed to detach a philo thread !!\n", 36);
		}
		i++;
	}
}

int	init_dinner(t_dinning *dinner)
{
	int	count;

	if (!init_mutex(dinner))// initialisation dyal mutex
		return (0);
	dinner->start_time = get_time();//m3ach bda le3cha , dik get time khas nsaybouha
	set_dead_flag(dinner, 0);// tawa7ed mamat
	init_philosopher(dinner);// initialisation dyal philos
	if (pthread_create(&dinner->supervisor, NULL, supervisor, dinner))// kansayb supervisor
		return (write(2, "Failed to create supervisor thread !!\n", 39), 0);
	//count howa 3adad lphalasipha li tssaybo
	count = create_philosophers(dinner);
	if (pthread_join(dinner->supervisor, NULL))
	{
		set_dead_flag(dinner, 1);
		write(2, "Failed to detach supervisor thread !!\n", 39);
	}
	join_philosophers(dinner, count);
	return (1);
}
