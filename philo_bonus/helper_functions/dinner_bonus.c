/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:22:44 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/23 11:08:23 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static void	init_philosopher(t_dinning *dinner)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	while (i < dinner->nbr_philos)
	{
		philo = &(dinner->philos[i]);
		philo->flag = 1;
		philo->id = i + 1;
		sem_wait(dinner->meals);
		philo->meals_eaten = 0;
		sem_post(dinner->meals);
		philo->dinner = dinner;
		i++;
	}
}

int	init_dinner(t_dinning *dinner)
{
	if (!init_semaphores(dinner))
		return (0);
	dinner->start_time = get_time();
	init_philosopher(dinner);
	return (1);
}

int	create_philosophers(t_dinning *dinner)
{
	int				i;
	t_philosopher	*philo;
	int				j;

	j = 0;
	i = 0;
	while (i < dinner->nbr_philos)
	{
		philo = &(dinner->philos[i]);
		philo->pid = fork();
		if (philo->pid == -1)
		{
			write(2, "Failed to create a process !!\n", 31);
			while (j++ < i)
				sem_post(dinner->stop);
			return (i);
		}
		else if (philo->pid == 0)
			routine(philo);
		i++;
	}
	return (i);
}
